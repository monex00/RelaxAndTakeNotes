#include <cstdio>
#include <string>
#include <thread>
#include <chrono>
#include <omp.h>

/**
 * @file omp_hello3.cpp
 * @brief A simple OpenMP program that demonstrates parallel execution with a specified number of threads.
 * 
 * This program prints a "Hello from thread" message from each thread and measures the execution time.
 * The number of threads can be specified as a command-line argument. If the number of threads is 
 * greater than or equal to 5, the parallel region is executed with the specified number of threads.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments. The first argument (argv[1]) specifies the number of threads.
 * 
 * @return int Exit status of the program.
 */

int main(int argc, char *argv[]) {
	using namespace std::chrono_literals;


	auto F=[](int i) {
		std::this_thread::sleep_for(100ms);
		std::printf("Hello from thread %d\n", i);
	};
	int nth=(argc>1)?std::stol(argv[1]):1;

	double start=omp_get_wtime();
	
    #pragma omp parallel if (nth>=5) num_threads(nth)
	F(omp_get_thread_num());
	
	double stop=omp_get_wtime();

	std::printf("Time %.2f (ms)\n", (stop-start)*1000.0);
}

