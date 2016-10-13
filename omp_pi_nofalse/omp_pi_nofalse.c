/**
 * This program demonstrates the use of OpenMP and an approach 
 * that avoids false sharing. 
 *  
 * The code is from Tim Matteson's presentation "A 'Hands-on' 
 * Introduction to OpenMP*" 
 * http://openmp.org/mp-documents/omp-hands-on-SC08.pdf 
 *  
 * !!!Warning: this program doesn't work. It hangs whenever 
 * NUM_THREADS is > 1. 
 */

#include <cstdio>
#include "omp.h"

#define NUM_THREADS 4

int main()
{ 
    static long num_steps = 100000; 
    double step;
    double pi;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    printf("Before the parallel section...\n");
    #pragma omp parallel
    {
        int i, id, nthrds, nthreads; 
        double x, sum;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        //if (id == 0) nthreads = nthrds;
        //nthrds = omp_get_num_threads();
        printf("Before the for loop...\n");
        for (i = id, sum = 0.0; i < num_steps; i = i + nthreads) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        printf("After the for loop...\n");
        #pragma omp critical
        pi += sum * step;

    }
    printf("#threads=%d, pi=%.15f\n", NUM_THREADS, pi);
    return (0);
}
