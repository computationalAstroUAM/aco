// Exercise 3: Broadcast
#include <mpi.h>
#include <iostream>

// Demonstrates broadcasting a value from root process to all other processes
int main3(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size, number;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get this process's rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    if (rank == 0) {
        number = 100;  // Root initializes the number
    }
    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Broadcast one integer from root (rank 0) to all processes
    std::cout << "Process " << rank << " received number: " << number << std::endl;

    MPI_Finalize();
    return 0;
}