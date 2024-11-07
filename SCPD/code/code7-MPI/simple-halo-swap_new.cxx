#include "mpi.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cmath>


#define N 6
using namespace std;

int main( int argc, char **argv ) {
  int myid,numprocs,namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  double t0,t1;
  // int K = 5; // number of iterations
  int K = 2; // number of iterations
  // MPI_Wtime cannot be called here
  MPI_Init(&argc,&argv );
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
  MPI_Get_processor_name(processor_name,&namelen);

  srandomdev();
  // srandom(time(NULL));
//   srandom(42);


  if (argc == 2)
    K = atoi(argv[1]); // number of iterations
  // ----
  if ((N%numprocs!=0) || (N<2)) {
    cout << "N should be multiple of nprocs\n";
    MPI_Finalize();
    return 0;
  }	
  float * fullmatrix = NULL;
  int psize = ((N*N)/numprocs);
  float * before = new float[psize+2*N]; /* add two rows for 1D halo */
  float * after = new float[psize+2*N]; /* add two rows for 1D halo */
  // not yet double buffering 
  // --- init data in P0
  if (myid==0) {
    fullmatrix = new float[N*N];
    //cout << "[" << myid << "] sending " << psize << " elems\n"; 
    for (int i=0;i<N*N;++i) 
      fullmatrix[i] = 1; 
    
    float (*b)[N] = (float (*)[N]) fullmatrix;
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j)
	      cout << b[i][j] << "\t";
      cout << "\n";
    }
    cout << " -------- initial ----------\n";
  }
  // Scattering fullmatrix to processes
  MPI_Scatter(fullmatrix,psize,MPI_FLOAT,&before[N],psize,MPI_FLOAT,0,MPI_COMM_WORLD);

  // MPI_Barrier(MPI_COMM_WORLD);
  // if(myid==1){
  //   cout<<"stampa---------------------------------\n";
  //   for (int i=0;i<N/numprocs+2;++i) {
  //     for (int j=0;j<N;++j)
  //       cout << before[i*N+j] << "\t";
  //     cout << "\n";
  //   }
  //   cout<<"stampa---------------------------------\n";

  // }

  if(myid==0) delete(fullmatrix);
  MPI_Status status;
  for (int r=0; r<K;++r) { // main loop 
    //cout << "[" << myid << "] Turn " << r << "\n";
    // Exchange halo
    // send slice up - receive slice from up
    if (myid != 0) { // S->N, S<-N
      // Here a deadlock may occour - alternate odd and even 
      MPI_Send(&before[N],N,MPI_FLOAT,myid-1,0,MPI_COMM_WORLD);
      MPI_Recv(&before[0],N,MPI_FLOAT,myid-1,0,MPI_COMM_WORLD,&status);
    }
    // send slice down - receive slice from down
    if (myid !=numprocs-1) { //
      MPI_Send(&before[psize ],N,MPI_FLOAT,myid+1,0,MPI_COMM_WORLD);	
      MPI_Recv(&before[psize+N],N,MPI_FLOAT,myid+1,0,MPI_COMM_WORLD,&status);
    }
    // Ghost cells filled
    // Do computation on partitions
    float  (*before_m)[N] = (float (*)[N]) &before[N];
    float  (*after_m)[N] = (float (*)[N]) &after[N];
    // corners
    /*
      stringstream ss;
      ss << myid << ": ";
      for (int i=0; i < psize/N; ++i) {
        for (int j=0; j < N; ++j) {
          ss << before_m[i][j] 
        }
      }
    */
    for (int i=0; i < psize/N ; ++i) {
      // middle left and right
      if (!((myid==0) && (i==0)) && !((myid==numprocs-1) && (i==(psize/N)))) {
          after_m[i][0] =   
            0.6*before_m[i][0]+
            0.08*before_m[i][1]+
            0.08*before_m[i-1][0]+
            0.08*before_m[i-1][1]+
            0.08*before_m[i+1][0]+
            0.08*before_m[i+1][1];
          //cerr << "updating1 " << i << " 0\n";
          
          after_m[i][N-1] =  
            0.6*before_m[i][N-1]+
            0.08*before_m[i][N-2]+
            0.08*before_m[i-1][N-1]+
            0.08*before_m[i-1][N-2]+
            0.08*before_m[i+1][N-1]+
            0.08*before_m[i+1][N-2];
          
          //cerr << "updating2 " << i << " " << N-1 << "\n";
          
          for (int j=1; j<(N-1); ++j) {
            after_m[i][j] = 
              0.6*before_m[i][j]+
              0.05*before_m[i][j-1]+
              0.05*before_m[i][j+1]+
              0.05*before_m[i-1][j]+
              0.05*before_m[i-1][j-1]+
              0.05*before_m[i-1][j+1]+
              0.05*before_m[i+1][j]+
              0.05*before_m[i+1][j-1]+
              0.05*before_m[i+1][j+1];
            //cerr << "updating3 " << i << " " << j << "\n";
        	}
      }
      
      if ((myid==0) && (i==0)) { // top

        after_m[i][0] =   // top left
          0.6*before_m[i][0]+
          0.13*before_m[i][1]+
          0.13*before_m[i+1][0]+
          0.13*before_m[i+1][1];
        //cerr << "updating4 " << i << " " << 0 << "\n";
        
        after_m[i][N-1] =  // top right
          0.6*before_m[i][N-1]+
          0.13*before_m[i][N-2]+
          0.13*before_m[i+1][N-1]+
          0.13*before_m[i+1][N-2];
        //cerr << "updating5 " << i << " " << N-1 << "\n";
        
        for (int j=1; j<N-1; ++j) {
          after_m[i][j] = 
            0.6*before_m[i][j]+
            0.08*before_m[i][j-1]+
            0.08*before_m[i][j+1]+
            0.08*before_m[i+1][j]+
            0.08*before_m[i+1][j-1]+
            0.08*before_m[i+1][j+1];
          //cerr << "updating6 " << i << " " << j << "\n";
        }
      }
      
      if ((myid==numprocs-1) && (i==((psize/N)-1))){ // bottom prima (i==(psize/N)

        after_m[i][0] =   // bottom left
          0.6*before_m[i][0]+
          0.13*before_m[i][1]+
          0.13*before_m[i-1][0]+
          0.13*before_m[i-1][1];
        //cerr << "updating7 " << i << " " << 0 << "\n";
        
        after_m[i][N-1] =  // bottom right
          0.6*before_m[i][N-1]+
          0.13*before_m[i][N-2]+
          0.13*before_m[i-1][N-1]+
          0.13*before_m[i-1][N-2];
        //cerr << "updating8 " << i << " " << N-1 << "\n";
        
        for (int j=1; j<N-1; ++j) {
          after_m[i][j] = 
            0.6*before_m[i][j]+
            0.08*before_m[i][j-1]+
            0.08*before_m[i][j+1]+
            0.08*before_m[i-1][j]+
            0.08*before_m[i-1][j-1]+
            0.08*before_m[i-1][j+1];
          //cerr << "updating9 " << i << " " << j << "\n";
        }
	
      }
      
    }
    // Logically the step is now over 
    // Here logically a barrier - it no really needed as Halo swap with blocking 
    // primitives acts as 
    // a process-to-process rendevous implementing a weaker form of barrier 
    // (a la Vanneschi)
    // swap buffers
    float * tmp = after;
    after = before;
    before = tmp;
  }
  //cout << myid <<" completed.\n";
  // ---
  // Now gather
  
  cout.flush();
  if (myid == 0)
    fullmatrix = new float[N*N];
    MPI_Gather(&before[N],psize,MPI_FLOAT,fullmatrix,psize,MPI_FLOAT,0,MPI_COMM_WORLD);
  if (myid == 0) {
    float (*b)[N] = (float (*)[N]) fullmatrix;
    cout << "--------- final -------------------\n";
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j)
	      cout << setprecision(4) << b[i][j] << "\t";
      cout << "\n";
    }
    delete(fullmatrix);
  }
  MPI_Finalize();
  return 0;
}
