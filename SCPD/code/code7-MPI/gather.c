#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define N 4

int main(int argc, char **argv) {
  
  int data[N];/*data to be gathered from processes*/
  int *buf,myrank,grp_size;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* find rank */
  MPI_Comm_size(MPI_COMM_WORLD, &grp_size); /*find group size*/
  printf("Chi sono %d quanti siamo %d\n", myrank, grp_size);
  
  // Init data
  for (int i = 0; i<N; i++)  data[i]=i+myrank*N;
  
  printf("[I'm %d] ", myrank);
  for (int j = 0; j < N;j++)
    printf("%d ",data[j]);
  printf("\n");
  
  if (myrank == 0) {
    buf = (int *) malloc(grp_size*N*sizeof (int)); // allocate memory
  }
  
  MPI_Gather(data,N,MPI_INT,buf,N,MPI_INT,0,MPI_COMM_WORLD) ;
  
  if (myrank == 0) {
    printf("N Proc %d\n", grp_size);
    for (int j = 0; j < grp_size * N;j++)
      printf("%d ",buf[j]);
    printf("\n");
  }
  
  MPI_Finalize();
  return 0;
}

