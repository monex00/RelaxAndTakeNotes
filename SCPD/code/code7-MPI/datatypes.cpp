// Author: Marco Aldinucci
// Date: 22 May 2012
// Es. datatypes, for PDS-physics class 2012

#include "mpi.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAG 0


static inline const double diffmsec(const struct timeval & a, 
                                    const struct timeval & b) {
  long sec  = (a.tv_sec  - b.tv_sec);
  long usec = (a.tv_usec - b.tv_usec);
    
  if(usec < 0) {
    --sec;
    usec += 1000000;
  }
  return ((double)(sec*1000)+ (double)usec/1000.0);
}

int main( int argc, char **argv )
{
  int myid,numprocs,namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  double t0,t1;
  struct timeval wt1,wt0;
  // MPI_Wtime cannot be called here
  gettimeofday(&wt0,NULL);
  MPI_Init(&argc,&argv );
  t0 = MPI_Wtime();
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
  MPI_Get_processor_name(processor_name,&namelen);

  MPI_Status status;

  // Type Contiguous + MPI_BYTE
  typedef struct {
    int x; int y; int z; 
  } point_t;
  std::cout << "Size of point_t " << sizeof(point_t) << "\n";
  point_t point,point_raw;
  MPI_Datatype ptype;
  MPI_Type_contiguous(3,MPI_INT,&ptype);
  MPI_Type_commit(&ptype);
  MPI_Aint extent,lb;
  MPI_Type_get_extent(ptype,&lb, &extent);
  std::cout << "Extent of ptype MPI_Datatype " << sizeof(point_t) << "\n";
  if (myid==0) {
    point.x=0; point.y=1; point.z=2;
    memcpy(&point_raw,&point,sizeof(point_t));
    // Type Contiguous send
    MPI_Send(&point,1,ptype,1,TAG,MPI_COMM_WORLD);
    // Raw untyped send
    MPI_Send(&point_raw,sizeof(point_raw),MPI_BYTE,1,TAG,MPI_COMM_WORLD);
  } else if (myid==1) {
    MPI_Recv(&point,1,ptype,0,TAG,MPI_COMM_WORLD,&status);
    std::cout << "Received point " << point.x << "," 
	      << point.y << "," <<  point.z << "\n";
    MPI_Recv(&point_raw,sizeof(point_t),MPI_BYTE,0,TAG,MPI_COMM_WORLD,&status);
    std::cout << "Received point MPI_BYTE " << point_raw.x << "," 
	      << point_raw.y << "," <<  point_raw.z << "\n";
  }
  // Type struct

  typedef struct {
    int num;
    float x;
    double *data;
  } hstruct_t;
  
  hstruct_t a;
  // Dynamically allocate a vector of double data[4], it will not be contigous 
  // in memory with x 
  a.data= (double*) malloc(sizeof(double)*4);

  int blocklengths[3]={1,1,4};
  MPI_Datatype types[3]={MPI_INT, MPI_FLOAT, MPI_DOUBLE};
  MPI_Aint displacements[3];
  MPI_Datatype restype;
  MPI_Aint intex, floatex, doubleex, intlb, floatlb, doublelb;
  MPI_Type_get_extent(MPI_INT, &intlb, &intex);
  std::cerr << "MPI_INT LB " << intlb << " EXTENT " <<  intex << std::endl;
  MPI_Type_get_extent(MPI_FLOAT, &floatlb, &floatex);
  std::cerr << "MPI_FLOAT LB " << floatlb << " EXTENT " <<  floatex << std::endl;
  MPI_Type_get_extent(MPI_DOUBLE, &doublelb, &doubleex);
  std::cerr << "MPI_DOUBLE LB " << doublelb << " EXTENT " <<  doubleex << std::endl; 
  displacements[0] = intlb; 
  displacements[1] = floatlb + intex;
  displacements[2] = (((MPI_Aint) a.data) - ((MPI_Aint) &a));
  MPI_Type_create_struct(3, blocklengths, displacements, types, &restype);
  MPI_Type_commit(&restype);
  
  if (myid==0) {
    a.num=6; a.x=3.14; for(int i=0;i<4;++i) a.data[i]=(double) i;
    MPI_Send(&a,1,restype,1,TAG,MPI_COMM_WORLD);
  } else if (myid==1) {
    MPI_Recv(&a,1,restype,0,TAG,MPI_COMM_WORLD,&status); 
    printf("P:%d my a is %d %f %lf %lf %lf %lf\n",
	   myid,a.num,a.x,a.data[0],a.data[1],a.data[2],a.data[3]);
  }
  t1 = MPI_Wtime();
  MPI_Finalize();
  gettimeofday(&wt1,NULL);  
  std::cout << "Total time (MPI) " << myid << " is " << t1-t0 << "\n";
  std::cout << "Total time (gtd) " << myid << " is " << 
    diffmsec(wt1,wt0)/1000 << "\n";
  if ((((diffmsec(wt1,wt0)/1000)-t1+t0)) > ((diffmsec(wt1,wt0)/1000)/50))
    std::cout << "Why the two measurements are sensibly different?\n";
  return 0;
}
