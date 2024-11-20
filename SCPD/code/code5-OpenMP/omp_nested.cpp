#include <cstdio>
#include <omp.h>

// execute with OMP_NESTED=true ./omp_nested

/**
 * @file omp_nested.cpp
 * @brief Demonstrates nested parallelism using OpenMP.
 *
 * This program creates nested parallel regions using OpenMP. It prints messages
 * from different levels of parallel regions to show the thread hierarchy.
 *
 * Usage:
 * Set the environment variable OMP_NESTED to true before running the program:
 * OMP_NESTED=true ./omp_nested
 *
 * The program creates three levels of parallel regions:
 * - Level 0: Creates 3 threads.
 * - Level 1: Each thread from Level 0 creates 2 threads.
 * - Level 2: Each thread from Level 1 creates 1 thread.
 *
 * Each thread prints its level, parent thread number, and its own thread number.
 *
 * @note Ensure that your OpenMP implementation supports nested parallelism.
 */
int main() {

#pragma omp parallel num_threads(3)
    {
		std::printf("Level 0 - (). Hi from thread %d of %d\n",
					omp_get_thread_num(),
					omp_get_num_threads());       
        int parent = omp_get_thread_num();
#pragma omp parallel num_threads(2)
        {
			std::printf("Level 1 - (%d). Hi from thread %d of %d\n",
						parent,
						omp_get_thread_num(), omp_get_num_threads());       
            int parent = omp_get_thread_num();
#pragma omp parallel num_threads(1)
            {
				std::printf("Level 2 - (%d). Hi from thread %d of %d\n",
							parent,
							omp_get_thread_num(), omp_get_num_threads());
            }
        }
    }
    return 0;
}
