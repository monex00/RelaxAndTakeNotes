/*
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

/*
SCPD 2023-24 code examples
Marco Aldinucci, University of Torino
31/03/2024

MPI hello world
> mpicxx -o hello_world_mpi hello_word_mpi.cxx
> mpirun -n 4 ./hello_world_mpi

*/

#include "mpi.h"
#include <stdio.h>
#include <iostream>

int main (int argc, char *argv[]){
// Initialize MPI
MPI_Init(&argc,&argv);

// Get the number of processes
int numP; 
MPI_Comm_size(MPI_COMM_WORLD,&numP);
// Get processor name
char processor_name[MPI_MAX_PROCESSOR_NAME];
int namelen;
MPI_Get_processor_name(processor_name,&namelen);
// Get the ID of the process
int myId;
MPI_Comm_rank(MPI_COMM_WORLD,&myId);

// Every process prints Hello
std::cout << "Process on " << processor_name << " Id " << myId << " of " << numP << ": Hello, world!" << std::endl;

// Terminate MPI
MPI_Finalize();
return 0;
}