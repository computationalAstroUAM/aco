//
// Created by weiguang on 5/04/24.
//
#include <omp.h>
#include <iostream>

int main() {
    // Set the number of threads to the number of processors
    omp_set_num_threads(omp_get_num_procs());

    double sum = 0.0;
    double start = 1.0;
    double end = 1e5;

    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        #pragma omp for reduction(+:sum)
        for (int i = start; i <= end; i++) {
            sum += i;
        }
        std::cout << "Thread " << ID << " completed.\n";
    }

    std::cout << "The sum from " << start << " to " << end << " is " << sum << std::endl;
    std::cout << "Total threads used: " << omp_get_num_threads() << std::endl;

    return 0;
}