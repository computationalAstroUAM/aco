// Exercise 5: Parallel Sum Reduction
#include <mpi.h>
#include <iostream>

// Demonstrates summing values across all processes using MPI_Reduce
int main5(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_val = rank + 1;  // Each process uses its rank + 1 as a local value
    int global_sum;

    MPI_Reduce(&local_val, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);  // Reduce by summing all local values to root

    if (rank == 0) {
        std::cout << "Total sum is: " << global_sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}
