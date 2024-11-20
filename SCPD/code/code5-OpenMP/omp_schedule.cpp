#include <cstdio>
#include <thread>
#include <vector>
#include <random>
#include <omp.h>


/**
 * @file omp_schedule.cpp
 * @brief Demonstrates the use of OpenMP for parallel for loops with dynamic scheduling.
 * 
 * This program creates a specified number of threads and iterates over a loop in parallel.
 * Each thread processes a subset of iterations and stores the results in a vector.
 * The scheduling of iterations is controlled by OpenMP's runtime scheduling.
 * 
 * The program also simulates some work by making each thread sleep for a random duration.
 * 
 * @details
 * - The `random` function generates a random integer between the specified min and max values.
 * - The `main` function initializes the number of threads and iterations, and creates a vector to store the results.
 * - The parallel for loop is executed with OpenMP, where each thread processes a subset of iterations.
 * - The results are printed, showing which iterations were processed by each thread.
 * 
 * @note
 * - The number of threads and iterations can be adjusted by changing the `nthreads` and `niter` variables.
 * - The scheduling type can be controlled by setting the `OMP_SCHEDULE` environment variable.
 * 
 * @example
 * To run the program with dynamic scheduling, set the environment variable:
 * @code
 * export OMP_SCHEDULE="dynamic"
 * ./omp_schedule
 * @endcode
 * 
 * @see https://www.openmp.org/specifications/ for more information on OpenMP.
 */

auto random(const int &min, const int &max) {
	// better to have different per-thread seeds....
	thread_local std::mt19937   
		generator(std::hash<std::thread::id>()(std::this_thread::get_id()));
	std::uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}


int main() {
	int nthreads=5;
	int niter=16;
	std::vector<std::vector<int>> iter(nthreads);
	
#pragma omp parallel for schedule(runtime) num_threads(nthreads) 
	for(int i=0;i<niter;++i) {
		iter[omp_get_thread_num()].push_back(i);
		// do something
		std::this_thread::sleep_for(std::chrono::milliseconds(random(0,100))); 		
	}

	for(int i=0;i<nthreads;++i) {
		std::printf("%d: ", i);
		for(unsigned long j=0;j<iter[i].size();++j)
			std::printf("%d ", iter[i][j]);
		std::printf("\n");
	}

}
