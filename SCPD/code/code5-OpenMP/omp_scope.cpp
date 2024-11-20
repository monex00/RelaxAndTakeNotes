#include <cstdio>
#include <omp.h>

/**
 * @file omp_scope.cpp
 * @brief Demonstrates the use of OpenMP scope clauses: private, shared, and firstprivate.
 *
 * This program initializes four integer variables and then creates a parallel region with 8 threads.
 * The variables are modified within the parallel region to show the effects of different OpenMP scope clauses.
 *
 * Variables:
 * - a: Private to each thread, not initialized within the parallel region.
 * - b: Shared among all threads, non-atomic increment.
 * - c: Private to each thread, initialized with the value from the master thread.
 * - d: Shared among all threads, non-atomic increment.
 *
 * The program prints the values of the variables from each thread and the final values after the parallel region.
 *
 * @warning The variable 'a' is not initialized within the parallel region, which may cause a compiler warning.
 * @note The increments of 'b' and 'd' are not atomic, which may lead to race conditions.
 */

int main() {

	int a=0;
	int b=1;
	int c=2;
	int d=3;

#pragma omp parallel num_threads(8) private(a) shared(b) firstprivate(c)
	{
		a++;  // not initialized! Warning from compiler (-Wall)
		b++;  // this is not atomic
		c++;  // local copies initialized 
		d++;  // this is shared by default, non atomic increment
		std::printf("Hi %d a=%d, b=%d, c=%d, d=%d\n",
					omp_get_thread_num(), a,b,c,d);
	}
	std::printf("Final values: a=%d b=%d c=%d d=%d\n", a, b, c, d);

}

