
#include <cstdio>
#include <omp.h>


/**
 * @file omp_scope2.cpp
 * @brief Demonstrates the use of OpenMP parallel for loop with lastprivate clause.
 *
 * This program creates a parallel region with 8 threads and iterates over a loop
 * from 0 to 15. Each thread prints its thread number and the value of the loop
 * variable. The lastprivate clause ensures that the variable 'i' retains the value
 * of the last iteration after the parallel region.
 *
 * @details
 * - The `#pragma omp parallel for` directive is used to parallelize the for loop.
 * - The `lastprivate(i)` clause ensures that the variable 'i' is updated with the
 *   value of the last iteration of the loop.
 * - The `num_threads(8)` clause specifies that 8 threads should be used for the
 *   parallel region.
 * - The `omp_get_thread_num()` function returns the thread number of the calling
 *   thread.
 * - The final value of 'i' after the parallel region is printed.
 *
 * @note
 * - The output order of the print statements may vary due to the parallel execution.
 * - The final value of 'i' will be 15, as it is the last value assigned in the loop.
 */

 
int main() {

	int i;

#pragma omp parallel for lastprivate(i) num_threads(8) 
	for(int j=0;j<16; ++j) 	{
		i=j;
		std::printf("Hi %d i=%d\n",omp_get_thread_num(), i);
	}
	std::printf("Final value: i=%d\n", i);

}

