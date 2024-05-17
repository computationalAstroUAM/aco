//
// Created by weiguang on 16/05/24.
//
#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    // Initialize the MPI execution environment
    /* MPI_Init(int *argc, char ***argv)
     * argc: A pointer to the number of arguments in argv
     * argv: A pointer to the array of arguments
    This function initializes the MPI execution environment.
    All MPI programs must call this function before making any other MPI calls.
    Here it's called with NULL arguments, which means that it doesn't take any command line arguments into consideration.
    */
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    // MPI_Comm_size returns the total number of MPI processes in the specified communicator
    /* MPI_Comm_size(MPI_Comm comm, int *size)
     * comm: The communicator whose size is to be returned.
     * size: A pointer to the variable in which the size of the communicator will be stored
     * MPI_COMM_WORLD: This is a predefined constant in MPI representing a communicator
     * that includes all the MPI processes that were started when the MPI program was launched.
    */
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    // MPI_Comm_rank returns the rank of the calling MPI process within the specified communicator
    /* MPI_Comm_rank(MPI_Comm comm, int *rank)
     * comm: The communicator in which the rank is to be returned.
     * rank: A pointer to the variable in which the rank of the calling process will be stored
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int array_size = 1000;
    std::vector<int> numbers(array_size);

    // Initialize the array with numbers from 1 to 1000
    if (world_rank == 0) {
        for (int i = 0; i < array_size; i++) {
            numbers[i] = i + 1;
        }
    }

    // Distribute the array to all processes
    // MPI_Bcast broadcasts a message from the process with rank "root" to all other processes in the communicator
    /* MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
     * buffer: The buffer containing the data to be broadcasted
     * count: The number of elements in the buffer
     * datatype: The datatype of the elements in the buffer
     * root: The rank of the process that broadcasts the message
     * comm: The communicator in which the message is broadcasted
    */
    MPI_Bcast(numbers.data(), array_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates a partial sum
    int local_sum = 0;
    for (int i = world_rank; i < array_size; i += world_size) {
        local_sum += numbers[i];
    }

    // Gather all partial sums to the root process
    int total_sum;
    // MPI_Reduce reduces values on all processes to a single value
    /* MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
     * sendbuf: The buffer containing the data to be reduced
     * recvbuf: The buffer in which the reduced data will be stored (only used by the root process)
     * count: The number of elements in the buffer
     * datatype: The datatype of the elements in the buffer
     * op: The operation to be applied during the reduction (e.g., MPI_SUM, MPI_MAX, MPI_MIN)
     * root: The rank of the process that receives the reduced data
     * comm: The communicator in which the reduction is performed
    */
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // The root process prints the total sum
    if (world_rank == 0) {
        std::cout << "Total sum: " << total_sum << std::endl;
    }

    // Terminate the MPI execution environment
    MPI_Finalize();
    return 0;
}