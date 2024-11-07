#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define N 4
#define ROOT 0

int main(int argc, char **argv) {
  
  int *data;
  int *inbuf,*outbuf,myrank,grp_size;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* find rank */
  MPI_Comm_size(MPI_COMM_WORLD, &grp_size); /*find group size*/
  
  if (myrank == ROOT) {
    inbuf = (int *) malloc(grp_size*N*sizeof (int)); // initial input
    outbuf = (int *) malloc(grp_size*N*sizeof (int)); // final output
    for (int i = 0; i<N*grp_size; i++) inbuf[i]=i;
  }
  data = (int *) malloc(N*sizeof (int)); // local array 
  
  // Init data
 
  // tcomm
  MPI_Scatter(inbuf,N,MPI_INT,data,N,MPI_INT,ROOT,MPI_COMM_WORLD);
  // Tcomp parallelo init
  for (int j = 0; j < N;j++)
    data[j]=2*data[j];
  /* 
     printf("[I'm %d] ", myrank);
     for (int j = 0; j < N;j++)
     printf("%d ",data[j]);
     printf("-->\n");
  */
  // Tcomp parallelo end
  //tcomm

  MPI_Gather(data,N,MPI_INT,outbuf,N,MPI_INT,ROOT,MPI_COMM_WORLD) ;
  
  if (myrank == ROOT) {
    printf("N Proc %d\n", grp_size);
    for (int j = 0; j < grp_size * N;j++)
      printf("%d ",outbuf[j]);
    printf("\n");
    }
  
  MPI_Finalize();
  return 0;
}
