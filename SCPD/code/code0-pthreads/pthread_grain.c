/* 
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

/*
SCPD 2023-24 code examples
Marco Aldinucci, University of Torino
31/03/2024

Reduce with + an array[n]
Study how the computational grain can be used to optimize speedup - play with variables n and grain.
Mutual exclusion is used to reduce partial sums.
Notice that pthreads arguments are allocated on the heap.
*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

double diffmsec(struct timeval *a, struct timeval *b) {
    long sec  = (a->tv_sec  - b->tv_sec);
    long usec = (a->tv_usec - b->tv_usec);

    if(usec < 0) {
        --sec;
        usec += 1000000;
    }
    return ((double)(sec*1000)+ (double)usec/1000.0);
}

void *partial_sum(void *);
pthread_mutex_t mutex_sum = PTHREAD_MUTEX_INITIALIZER;

typedef struct arg_struct {
    long *a;
    long nelems;
    long *tsum;
    double *ttime;
} args_t;

int main() {
  pthread_t *thread_id;
  long n=1000000;
  long grain=30; // grain operation per thread
  long nthreads;
  long *a;
  long total_sum = 0;
  struct timeval t0,t1,t2;
  double sum_time =0.0;

  // Compute the number of threads in function of the grain
  nthreads =  (n + grain - 1) / grain;
  printf ("Using %ld threads for %ld elements\n", nthreads, n); 

  // Allocate heap data
  a = (long *) malloc(sizeof(long)*n);
  for (long i=0; i< n; i++) a[i]=i;
  // Allocate thread_ids
  thread_id = (pthread_t *) malloc(sizeof(thread_id)*nthreads);
  gettimeofday(&t0,NULL);
  for(long i=0; i < nthreads; i++) {
    args_t * arg = (args_t *) malloc(sizeof(args_t));
    arg->a = &(a[i*grain]);
    arg->nelems = MIN(grain,(n-(i*grain)));
    arg->tsum = &total_sum;
    arg->ttime = &sum_time;
    pthread_create( &thread_id[i], NULL, partial_sum, arg );
  }
  gettimeofday(&t1,NULL);

  for(long j=0; j < nthreads; j++) {
    pthread_join( thread_id[j], NULL); 
  }
  gettimeofday(&t2,NULL);
  
  /* Now that all threads are complete I can print the final result.     */
  /* Without the join I could be printing a value before all the threads */
  /* have been completed.                                                */

  printf("The total sum is: %ld\n", total_sum);
  printf("Pthread create region time (ms): %lf\n",diffmsec(&t1,&t0));
  printf("Total time (ms): %lf\n",diffmsec(&t2,&t0));
  printf("Partial summing time over multiple cores (ms): %lf\n",sum_time); 
  return (0);
}

// The thread function
void *partial_sum(void *targ) {
  args_t * arg = (args_t *) targ;
  long psum = 0;
  double ptime;
  struct timeval t0,t1;
  gettimeofday(&t0,NULL);
  for (long i=0; i < arg->nelems; i++)
    psum+=arg->a[i];
  gettimeofday(&t1,NULL);
  ptime = diffmsec(&t1,&t0);
  //printf("Thread number %ld, nelements %ld psum %ld time %lf\n", (long int) pthread_self(), arg->nelems, psum, ptime);
  // tsum is a  variable on the stack of the main thread subject to data race
  pthread_mutex_lock( &mutex_sum );
  *(arg->tsum) += psum; 
  *arg->ttime += ptime; 
  pthread_mutex_unlock( &mutex_sum );
  free (targ);
  return NULL;
}
