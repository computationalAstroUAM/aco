#include <mpi.h>
#include <iostream>

// Demonstrates basic MPI initialization and rank/size querying
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize the MPI environment. Must be called before any other MPI functions.

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Determine the rank (ID) of the current process within MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes in the communicator

    std::cout << "Hello from process " << rank << " out of " << size << std::endl;

    MPI_Finalize();  // Clean up the MPI environment. Must be the last MPI call.
    return 0;
}