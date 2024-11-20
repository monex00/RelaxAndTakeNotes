#include <iostream>
#include <limits>
#include <iomanip>
#include <omp.h>

using namespace std;

/**
 * @file omp_pi.cpp
 * @brief A program to compute the value of Pi using numerical integration and OpenMP for parallelization.
 *
 * This program calculates the value of Pi using the midpoint rule for numerical integration.
 * The computation is parallelized using OpenMP to improve performance on multi-core systems.
 *
 * Usage:
 *   ./omp_pi <num_steps>
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments. The second argument should be the number of steps for the integration.
 *
 * @return Returns 0 on success, and -1 if the number of command-line arguments is incorrect.
 *
 * The program performs the following steps:
 * 1. Parses the number of steps from the command-line argument.
 * 2. Initializes variables for the integration.
 * 3. Starts the timer using `omp_get_wtime()`.
 * 4. Uses an OpenMP parallel for loop to compute the sum of the areas of the rectangles.
 * 5. Calculates the final value of Pi.
 * 6. Stops the timer and prints the elapsed time.
 * 7. Prints the computed value of Pi with high precision.
 * 8. Prints the known value of Pi to compare.
 * 9. Prints the elapsed time in milliseconds.
 */
int main(int argc, char * argv[]) {
  if(argc != 2) {
     std::cout << "Usage is: " << argv[0] << " num_steps\n";
     return(-1);
  }

  uint64_t num_steps = std::stol(argv[1]);
  long double   x = 0.0;
  long double  pi = 0.0;
  long double sum = 0.0;
  long double step= 1.0/num_steps;
  
  double start = omp_get_wtime();

#pragma omp parallel for private(x) reduction(+:sum)
  for (uint64_t k=0; k < num_steps; ++k) {
	  x = (k + 0.5) * step; // x is the midpoint of the interval (center of the rectangle -> k is the left side, k+1 is the right side)
	  sum += 4.0/(1.0 + x*x); // function to integrate rappresenting the area of the rectangle (width = step, height = 4/(1+x^2)) 
  }
  pi = step * sum;

  double elapsed = omp_get_wtime() - start;
  
  std::cout << "Pi = " << std::setprecision(std::numeric_limits<long double>::digits10 +1) << pi << "\n";
  std::cout << "Pi = 3.141592653589793238 (first 18 decimal digits)\n";
  std::printf("Time %f (ms)\n", elapsed*1000.0);
  return(0);
}

