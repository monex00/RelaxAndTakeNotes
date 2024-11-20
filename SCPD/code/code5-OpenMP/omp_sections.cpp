#include <cstdio>
#include <omp.h>

/**
 * @file omp_sections.cpp
 * @brief Demonstrates the use of OpenMP sections for parallel execution.
 *
 * This program initializes two arrays `a` and `b` with values, then uses OpenMP
 * to perform parallel computations on these arrays. The computations are divided
 * into sections, where each section is executed by a different thread.
 *
 * The program performs the following steps:
 * 1. Initializes arrays `a` and `b` with values.
 * 2. Uses OpenMP sections to compute arrays `c` and `d` in parallel:
 *    - Section 1: Computes `c[i] = a[i] + b[i]`
 *    - Section 2: Computes `d[i] = a[i] * b[i]`
 * 3. Computes the reduction sum `r` of the differences between `d[i]` and `c[i]`.
 *
 * The program uses 4 threads for parallel execution.
 *
 * @note The `nowait` clause is used to avoid an implicit barrier at the end of the sections.
 *       An implicit barrier is present at the end of the parallel region.
 *
 * @return 0 on success.
 */

int main(void) {
	const int N=128;
    float  a[N], b[N], c[N], d[N];

#pragma omp parallel for num_threads(4)	
    for (int i=0; i < N; i++) {
		a[i] = i * 1.0;
		b[i] = i * 3.14; 
    }
#pragma omp parallel num_threads(4)
    {
#pragma omp sections nowait
	{
#pragma omp section
		{
			std::printf("Thread %d executing sec1\n", omp_get_thread_num());
			for (int i=0; i < N; ++i)
				c[i] = a[i] + b[i];
		}
#pragma omp section
		{
			std::printf("Thread %d executing sec2\n", omp_get_thread_num());
			for (int i=0; i < N; ++i)
				d[i] = a[i] * b[i];
		}
	}  // <- no barrier here
}  // <- implicit barrier here
	
	float  r=0.0;
#pragma omp parallel for reduction(+ : r)	
	for (int i=0; i < N; ++i)
		r += d[i] - c[i];
	
	std::printf("%f\n", r);
}


