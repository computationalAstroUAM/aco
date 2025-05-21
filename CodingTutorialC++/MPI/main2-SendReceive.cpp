// Exercise 2: Send and Receive
#include <mpi.h>
#include <iostream>

// Demonstrates basic point-to-point communication using MPI_Send and MPI_Recv
int main2(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize MPI environment

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the current process's rank

    int number;
    if (rank == 0) {
        number = 42;  // Initialize number to send
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);  // Send one integer to process with rank 1 using tag 0
        MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Receive modified value back from process 1
        std::cout << "Process 0 received back " << number << std::endl;
    } else if (rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Receive data from process 0
        number *= 2;  // Modify the received number
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);  // Send it back to process 0
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}