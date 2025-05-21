// Exercise 4: Scatter and Gather
#include <mpi.h>
#include <iostream>

// Demonstrates distributing an array to processes and gathering modified results
int main4(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 4;
    int data[N] = {1, 2, 3, 4};  // Array to be scattered (used only on root)
    int recv;

    MPI_Scatter(data, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Send one int to each process from root
    recv *= 2;  // Modify received data (e.g., doubling it)
    MPI_Gather(&recv, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Gather modified data back to root

    if (rank == 0) {
        std::cout << "Gathered data: ";
        for (int i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}