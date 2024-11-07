/* ///////////////////////////////////////////////////////////////////// */
/*!
 \file
 \brief Solve Laplace eq. on 2D domain in serial/parallel.

 Solve the two-dimensional Laplace equation with Dirichlet
 boundary conditions on a 2D Cartesian domain.

 The function DomainDecomposition() is used to decompose the
 computational domain into equally-sized sub-domains.

 The function BoundaryConditions() is used to assign both
 physical and inter-processor boundary conditions.

 The function WriteSolution() writes binary data to disk
 (fully parallel I/O is used in the parallel version).

 Documented in https://dx.doi.org/10.1016/j.jpdc.2021.05.017

 For the serial version, compile with

 > gcc laplace2D.c

 For the parallel version, compile with

 > mpicc -DPARALLEL laplace2D.c  (or turn #define PARALLEL to 1)


 \author Andrea Mignone (mignone@to.infn.it), Valentina Cesare (valentina.cesare@inaf.it), Gianluca Mittone (gianluca.mittone@edu.unito.it), Marco Aldinucci (marco.aldinucci@unito.it)
 \date   March 19, 2020
 */
/* ///////////////////////////////////////////////////////////////////// */

#include "tools.h"
#include <math.h>
#include "tools.h"
#include <sys/time.h>

// #define PARALLEL
#define NGHOST   1
#define NDIM     2

#ifdef PARALLEL
#include <mpi.h>
MPI_Comm MPI_COMM_CART;
#endif

typedef struct MPI_Decomp_{
    int nprocs[NDIM];     /*  Number of processors in each dimension */
    int periods[NDIM];    /*  Periodicity flag in each dimension     */
    int coords[NDIM];     /*  Cartesian coordinate in the MPI topology */
    int gsize[NDIM];      /*  Global domain size (no ghosts)  */
    int lsize[NDIM];      /*  Local domain size (no ghosts)   */
    int start[NDIM];      /*  Local start index in each dimension           */
    int procL[NDIM];      /*  Rank of left-lying  process in each direction */
    int procR[NDIM];      /*  Rank of right-lying process in each direction */
    int rank;             /*  Local process rank */
    int size;             /*  Communicator size  */
} MPI_Decomp;



void BoundaryConditions(double **, double *, double *, int, int, MPI_Decomp *, int, int);
void DomainDecomposition(MPI_Decomp *, int, int);
void WriteSolution (double **, int, int, MPI_Decomp *, int, int);

int main(int argc, char ** argv)
{
//    Time taken: start
    struct timeval start, end;
    double time_taken;
    gettimeofday(&start, NULL);

    if (argc<3) {printf("Usage: laplace2D nx ny\n"); return 0;}
    int NX_GLOB = (int) strtol(argv[1], NULL, 10);
    int NY_GLOB = (int) strtol(argv[2], NULL, 10);
    int    nx_tot, nx, i, ibeg, iend;
    int    ny_tot, ny, j, jbeg, jend;
    int    k, rank=0, size=1;
    double xbeg = 0.0, xend = 1.0;
    double ybeg = 0.0, yend = 1.0;
    double dx = (xend - xbeg)/(NX_GLOB + 1);
    double dy = (yend - ybeg)/(NY_GLOB + 1);
    double *xg, *yg, *x, *y, **phi, **phi0;
    double err, tol;
    MPI_Decomp  mpi_decomp;
    int procL[NDIM] = {-1,-1};
    int procR[NDIM] = {-1,-1};

    /* --------------------------------------------------------
     0. Initialize the MPI execution environment
     -------------------------------------------------------- */

#ifdef PARALLEL
    MPI_Datatype row_type, col_type;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
//    size = (int) strtol(argv[3], NULL, 10);

    DomainDecomposition(&mpi_decomp, NX_GLOB, NY_GLOB);
    nx = mpi_decomp.lsize[0];
    ny = mpi_decomp.lsize[1];
#else
    mpi_decomp.gsize[0] = mpi_decomp.lsize[0] = nx = NX_GLOB;
    mpi_decomp.gsize[1] = mpi_decomp.lsize[1] = ny = NY_GLOB;
    mpi_decomp.procL[0] = mpi_decomp.procL[1] = -1;
    mpi_decomp.procR[0] = mpi_decomp.procR[1] = -1;
#endif

    /* --------------------------------------------------------
     1. Set local grid indices
     -------------------------------------------------------- */

    ibeg   = NGHOST;
    iend   = ibeg + nx - 1;
    nx     = iend - ibeg + 1;
    nx_tot = nx + 2*NGHOST;

    jbeg   = NGHOST;
    jend   = jbeg + ny - 1;
    ny     = jend - jbeg + 1;
    ny_tot = ny + 2*NGHOST;

    /* --------------------------------------------------------
     2. Generate global and local grids
     -------------------------------------------------------- */

    xg = (double *) malloc ( (NX_GLOB+2*NGHOST)*sizeof(double));
    yg = (double *) malloc ( (NY_GLOB+2*NGHOST)*sizeof(double));
    for (i = 0; i < (NX_GLOB+2*NGHOST); i++) xg[i] = xbeg + (i-ibeg+1)*dx;
    for (j = 0; j < (NY_GLOB+2*NGHOST); j++) yg[j] = ybeg + (j-jbeg+1)*dy;
#ifdef PARALLEL
    x = xg + mpi_decomp.start[0];
    y = yg + mpi_decomp.start[1];
#else
    x = xg;
    y = yg;
#endif

    /* --------------------------------------------------------
     3. Allocate memory on local processor and
     assign initial conditions.
     -------------------------------------------------------- */

    phi  = Allocate_2DdblArray(ny_tot, nx_tot);
    phi0 = Allocate_2DdblArray(ny_tot, nx_tot);

    for (j = jbeg; j <= jend; j++){
        for (i = ibeg; i <= iend; i++){
            phi0[j][i] = 0.0;
        }}

#ifdef PARALLEL
    MPI_Type_contiguous (nx_tot, MPI_DOUBLE, &row_type);
    MPI_Type_vector     (ny_tot, 1, nx_tot, MPI_DOUBLE, &col_type);
    MPI_Type_commit (&row_type);
    MPI_Type_commit (&col_type);
#endif

    /* --------------------------------------------------------
     4. Main iteration cycle
     -------------------------------------------------------- */

    tol = 1.e-5;
    err = 1.0;
    k   = 0;
    while  (err > tol){

        /* -- 4a. Set boundary conditions first -- */

        BoundaryConditions(phi0, x, y, nx, ny, &mpi_decomp, NX_GLOB, NY_GLOB);

        /* -- 4b. Jacobi's method and residual (interior points) -- */

        err = 0.0;
        for (j = jbeg; j <= jend; j++){
            for (i = ibeg; i <= iend; i++){
                phi[j][i] = 0.25*(  phi0[j][i-1] + phi0[j][i+1]
                                    + phi0[j-1][i] + phi0[j+1][i] );

                err += dx*dy*fabs(phi[j][i] - phi0[j][i]);
            }}

        for (j = jbeg; j <= jend; j++){
            for (i = ibeg; i <= iend; i++){
                phi0[j][i] = phi[j][i];
            }}

#ifdef PARALLEL
        double err_glob;
        MPI_Allreduce (&err, &err_glob, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        err = err_glob;
#endif

        if (rank == 0){
            printf ("k = %d; err = %8.3e\n",k, err);
        }
        k++;
    }

    WriteSolution (phi, nx, ny, &mpi_decomp, NX_GLOB, NY_GLOB);

#ifdef PARALLEL
    MPI_Finalize();
#endif
    
    
    
    
//    Time taken: end
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                                start.tv_usec)) * 1e-6;
    if (rank == 0) {
        printf("NX_GLOB x NY_GLOB = %d x %d\n", NX_GLOB, NY_GLOB);
        printf("# processors = %d\n", size);
        printf("Time = %lf\n", time_taken);
    }
    
    return 0;
}

#ifdef PARALLEL
/* ********************************************************************* */
void DomainDecomposition(MPI_Decomp *mpi_decomp, int NX_GLOB, int NY_GLOB)
/*
 *
 *********************************************************************** */
{
    int dim, i;
    int rank, size;
    int *coords  = mpi_decomp->coords;
    int *gsize   = mpi_decomp->gsize;
    int *lsize   = mpi_decomp->lsize;
    int *nprocs  = mpi_decomp->nprocs;
    int *periods = mpi_decomp->periods;
    int *procL   = mpi_decomp->procL;
    int *procR   = mpi_decomp->procR;
    int *start   = mpi_decomp->start;
    int new_coords[NDIM];

    /* --------------------------------------------------------
     1. Get rank & size
     -------------------------------------------------------- */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    mpi_decomp->rank = rank;
    mpi_decomp->size = size;

    /* --------------------------------------------------------
     2. Obtain number of processor along each dimension.
     Use maximally squared decomp.
     -------------------------------------------------------- */

    nprocs[0] = (int)sqrt(size);
    nprocs[1] = size/nprocs[0];
    if (nprocs[0]*nprocs[1] != size){
        if (rank == 0) printf ("! Cannot decompose\n");
        MPI_Finalize();
        exit(1);
    }
    if (rank == 0){
        printf ("Decomposition achieved with %d X %d procs\n",nprocs[0],nprocs[1]);
    }

    periods[0] = 0;
    periods[1] = 0;

    /* --------------------------------------------------------
     3. Create Cartesian topology
     -------------------------------------------------------- */

    MPI_Cart_create(MPI_COMM_WORLD, NDIM, nprocs, periods,
                    0, &MPI_COMM_CART);
    MPI_Cart_get(MPI_COMM_CART, NDIM, nprocs, periods, coords);

    /* --------------------------------------------------------
     4. Fill structure members
     -------------------------------------------------------- */

    gsize[0] = NX_GLOB;
    gsize[1] = NY_GLOB;
    lsize[0] = NX_GLOB/nprocs[0];
    lsize[1] = NY_GLOB/nprocs[1];
    start[0] = coords[0]*lsize[0];
    start[1] = coords[1]*lsize[1];

    /* --------------------------------------------------------
     5. Determine ranks of neighbour processors
     -------------------------------------------------------- */

    for (dim = 0; dim < NDIM; dim++) {
        for (i = 0; i < NDIM; i++) new_coords[i] = coords[i];

        new_coords[dim] = coords[dim] + 1;
        if (new_coords[dim] < nprocs[dim]) {
            MPI_Cart_rank ( MPI_COMM_CART, new_coords, &(procR[dim]) );
        } else {
            procR[dim] = MPI_PROC_NULL;
        }

        new_coords[dim] = coords[dim] - 1;
        if (new_coords[dim] >= 0) {
            MPI_Cart_rank ( MPI_COMM_CART, new_coords, &(procL[dim]) );
        } else {
            procL[dim] = MPI_PROC_NULL;
        }
    }

    /* --------------------------------------------------------
     6. Print processor information.
     (Use MPI_Bcast() to print in sequence)
     -------------------------------------------------------- */

    int proc, go;
    for (proc = 0; proc < size; proc++){
        go = proc;
        MPI_Bcast(&go, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank == go) {
            printf ("[Rank %d]\n",rank);
            printf ("  coords = [%d, %d], lsize = [%d, %d]\n",
                    coords[0], coords[1], lsize[0], lsize[1]);
            for (dim = 0; dim < NDIM; dim++){
                printf ("  (procL, procR)[%d] = %d, %d\n", dim, procL[dim], procR[dim]);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    return;
}
#endif

/* ********************************************************************* */
void BoundaryConditions(double **phi, double *x, double *y,
                        int nx, int ny, MPI_Decomp *mpi_decomp, int NX_GLOB, int NY_GLOB)
/*
 *********************************************************************** */
{
    int i,j;
    int ibeg   = NGHOST;
    int iend   = ibeg + nx - 1;

    int jbeg   = NGHOST;
    int jend   = jbeg + ny - 1;

    int *procL = mpi_decomp->procL;
    int *procR = mpi_decomp->procR;
#ifdef PARALLEL
    int rank = mpi_decomp->rank;
    int size = mpi_decomp->size;
    double send_buf[4][NX_GLOB + 2 * NGHOST];  /*The dimension 4 = 2*NDIM, where NDIM = 2 in this case*/
    double recv_buf[4][NX_GLOB + 2 * NGHOST];  /*The dimension 4 = 2*NDIM, where NDIM = 2 in this case*/

    /*  Used for testing
     for (j = 0; j <= jend+1; j++){
     for (i = 0; i <= iend+1; i++){
     phi[j][i] = -1;
     }}

     for (j = jbeg; j <= jend; j++){
     for (i = ibeg; i <= iend; i++){
     phi[j][i] = rank;
     }}
     */

    for (j = jbeg; j <= jend; j++) send_buf[0][j] = phi[j][ibeg];
    for (j = jbeg; j <= jend; j++) send_buf[1][j] = phi[j][iend];
    for (i = ibeg; i <= iend; i++) send_buf[2][i] = phi[jbeg][i];
    for (i = ibeg; i <= iend; i++) send_buf[3][i] = phi[jend][i];

    MPI_Neighbor_alltoall(send_buf, NX_GLOB + 2 * NGHOST, MPI_DOUBLE, recv_buf, NX_GLOB + 2 * NGHOST, MPI_DOUBLE,
                          MPI_COMM_CART);

    for (j = jbeg; j <= jend; j++) phi[j][ibeg - 1] = recv_buf[0][j];
    for (j = jbeg; j <= jend; j++) phi[j][iend + 1] = recv_buf[1][j];
    for (i = ibeg; i <= iend; i++) phi[jbeg - 1][i] = recv_buf[2][i];
    for (i = ibeg; i <= iend; i++) phi[jend + 1][i] = recv_buf[3][i];
#endif

    /* -- Left -- */

    if (procL[0] < 0){
        i = ibeg-1;
        for (j = jbeg; j <= jend; j++) phi[j][i] = 1.0-y[j];
    }

    /* -- Right -- */

    if (procR[0] < 0){
        i = iend+1;
        for (j = jbeg; j <= jend; j++) phi[j][i] = y[j]*y[j];
    }

    /* -- Bottom -- */

    if (procL[1] < 0){
        j = jbeg-1;
        for (i = ibeg; i <= iend; i++) phi[j][i] = 1.0-x[i];
    }

    /* -- Top -- */

    if (procR[1] < 0){
        j = jend+1;
        for (i = ibeg; i <= iend; i++) phi[j][i] = x[i];
    }

    return;

#ifdef PARALLEL
    // Print
    MPI_Barrier(MPI_COMM_WORLD);
    int go, proc;
    for (proc = 0; proc < size; proc++){
        go = proc;
        MPI_Bcast(&go, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == go) {
            printf ("Boundary [Rank %d]\n",rank);
            for (j = jend+1; j >= 0; j--){
                for (i = 0; i <= iend+1; i++){
                    printf ("%6.2f  ", phi[j][i]);
                }
                printf ("\n");
            }
        }
    }

    MPI_Finalize();
    exit(0);
#endif
}

/* ********************************************************************* */
void WriteSolution (double **phi, int nx, int ny, MPI_Decomp *md, int NX_GLOB, int NY_GLOB)
/*
 *********************************************************************** */
{
    int i,j;
    int ibeg   = NGHOST;
    int iend   = ibeg + nx - 1;

    int jbeg   = NGHOST;
    int jend   = jbeg + ny - 1;

    static int nfile = 0;
//    static int nfile = 1;
//    static int nfile = 2;
//    static int nfile = 3;
//    static int nfile = 4;
//    static int nfile = 5;
//    static int nfile = 6;
//    static int nfile = 7;
//    static int nfile = 8;
//    static int nfile = 9;
    char fname[32];

    //sprintf (fname,"laplace2D_Parallel_N_%02d.bin",nfile);
    //sprintf (fname,"laplace2D_Parallel_N_128_128_%02d.bin",nfile);
    sprintf (fname,"laplace2D_Parallel_N_128_%02d.bin",nfile);

    /*
     for (j = jbeg-1; j <= jend+1; j++) for (i = ibeg-1; i <= iend+1; i++) {
     phi[j][i] = -1;
     }
     for (j = jbeg; j <= jend; j++) for (i = ibeg; i <= iend; i++) {
     phi[j][i] = md->rank;
     }
     */
#ifdef PARALLEL
    MPI_File fh;
    MPI_Datatype type_local, type_domain;
    int amode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
    int gsize[2], lsize[2], start[2];

    /* --------------------------------------------------------
     1. Create a local array type without the ghost zones
     This datatype will be passed to MPI_File_write()
     -------------------------------------------------------- */

    gsize[0] = md->lsize[0] + 2*NGHOST;
    gsize[1] = md->lsize[1] + 2*NGHOST;

    lsize[0] = md->lsize[0];
    lsize[1] = md->lsize[1];

    start[0] = NGHOST;
    start[1] = NGHOST;

    MPI_Type_create_subarray (NDIM, gsize, lsize, start,
                              MPI_ORDER_FORTRAN, MPI_DOUBLE, &type_local);
    MPI_Type_commit (&type_local);

    /* --------------------------------------------------------
     2. Create the subarry in the global domain.
     This datatype is used to set the file view.
     -------------------------------------------------------- */

    gsize[0] = NX_GLOB;
    gsize[1] = NY_GLOB;

    lsize[0] = md->lsize[0];
    lsize[1] = md->lsize[1];

    start[0] = lsize[0]*md->coords[0];  // equal to md->start[0]
    start[1] = lsize[1]*md->coords[1];  // equal to md->start[1]

    MPI_Type_create_subarray (NDIM, gsize, lsize, start,
                              MPI_ORDER_FORTRAN, MPI_DOUBLE, &type_domain);
    MPI_Type_commit (&type_domain);

    /* --------------------------------------------------------
     3. Write to disk
     -------------------------------------------------------- */

    MPI_File_delete(fname, MPI_INFO_NULL);
    MPI_File_open(MPI_COMM_CART, fname, amode, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_DOUBLE, type_domain, "native", MPI_INFO_NULL);
    MPI_File_write_all(fh, phi[0], 1, type_local, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    MPI_Type_free (&type_local);
    MPI_Type_free (&type_domain);
#else
    FILE *fp;
    printf ("> Writing %s\n",fname);
    fp = fopen(fname, "wb");

    for (j = jbeg; j <= jend; j++){
        fwrite (phi[j] + ibeg, sizeof(double), nx, fp);
    }

    fclose(fp);
#endif

    nfile++;
}
