#include <cstdio>
#include <string>
#if defined(_OPENMP)
#include <omp.h>
#endif

/**
 * @file omp_hello2.cpp
 * @brief A simple OpenMP program to demonstrate parallel execution.
 *
 * This program prints a message from each thread in a parallel region.
 * The number of threads can be specified as a command-line argument.
 * If no argument is provided, the program defaults to using one thread.
 *
 * @details
 * The program defines a lambda function `F` that prints a message
 * indicating the thread number and the total number of threads.
 * The lambda function uses OpenMP functions `omp_get_thread_num` and
 * `omp_get_num_threads` to retrieve the thread information.
 * The parallel region is created using the `#pragma omp parallel` directive,
 * and the number of threads is specified by the `num_threads` clause.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 *             The first argument (if provided) specifies the number of threads.
 *
 * @return int Exit status of the program.
 */
int main(int argc, char *argv[]) {
	
  auto F=[]() {
    int i=0;
    int n=1;
#if defined(_OPENMP)    
    i = omp_get_thread_num();
    n = omp_get_num_threads();
#endif    
    std::printf("Hello from thread %d of %d\n", i, n);
  };
  
  int nth=(argc>1)?std::stol(argv[1]):1;
  #pragma omp parallel num_threads(nth)
  F();
}

