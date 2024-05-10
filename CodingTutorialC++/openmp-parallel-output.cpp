//
// Created by weiguang on 9/05/24.
//
#include <omp.h>
#include <fstream>
#include <sstream>

int main() {
    int N = omp_get_max_threads();
    int data[1000];  // Assuming you have 1000 data points

    // Initialize the data array
    for(int i = 0; i < 1000; i++) {
        data[i] = i * i;  // Just an example, replace with your actual data
    }

    int chunk_size = 1000 / N;  // Size of each chunk of data

    // Write data to files in parallel
    #pragma omp parallel num_threads(N)
    {
        int thread_id = omp_get_thread_num();

        // Create a unique filename for each thread
        std::stringstream ss;
        ss << "output" << thread_id << ".txt";

        // Open the file and write to it
        std::ofstream file(ss.str());

        // Calculate the start and end indices for this thread's chunk of data
        int start = thread_id * chunk_size;
        int end = start + chunk_size;

        // If this is the last thread, make sure it processes all remaining data
        if(thread_id == N - 1) {
            end = 1000;
        }

        for(int i = start; i < end; i++) {
            file << "Data: " << data[i] << std::endl;
        }

        // Close the file
        file.close();
    }

    return 0;
}