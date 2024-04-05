//
// Created by weiguang on 5/04/24.
//
#include <omp.h>
#include <iostream>

int main() {
    std::cout << "omp_get_num_procs = " <<  omp_get_num_procs() << std::endl;
    // Set the number of threads to the number of processors
//    omp_set_num_threads(omp_get_num_procs());

    omp_set_num_threads(4);
#pragma omp parallel
    {
        std::cout << "Total threads used: " << omp_get_num_threads() << std::endl;
    }
//    std::cout << "Total threads used: " << omp_get_num_threads() << std::endl;
    double sum = 0.0;
    int start = 1.0;
    int end = 1e5;

    // Start time
    double start_time = omp_get_wtime();

//    #pragma omp parallel
//    {
//        int ID = omp_get_thread_num();
//
//        for (int i = start; i <= end; i++) {
//            sum += i;
//        }
//
//        std::cout << "Thread " << ID << " completed.\n";
//    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    // End time
    double end_time = omp_get_wtime();

    // Calculate CPU time
    double cpu_time = end_time - start_time;

    std::cout << "The sum from " << start << " to " << end << " is " << sum << std::endl;
    std::cout << "CPU time: " << cpu_time << " seconds" << std::endl;

    return 0;
}