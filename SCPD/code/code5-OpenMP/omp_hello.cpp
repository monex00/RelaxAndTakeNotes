#include <cstdio>

#include <omp.h>

/**
 * @brief Entry point of the program.
 * 
 * This function uses OpenMP to create a parallel region where multiple threads
 * are spawned. Each thread prints a message indicating its thread number and 
 * the total number of threads.
 * 
 * @return int Exit status of the program.
 */
int main() {
  #pragma omp parallel
  {  // <- spawning of threads
	  int i = omp_get_thread_num();
	  int n = omp_get_num_threads();
	  std::printf("Hello from thread %d of %d\n", i, n);
  }  // <- joining of threads
}

