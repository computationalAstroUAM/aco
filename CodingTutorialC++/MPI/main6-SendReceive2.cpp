// Demonstrates ring communication: send to next and receive from previous
int main6(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_val = rank;  // Each process sends its rank
    int recv_val;
    int next = (rank + 1) % size;  // Compute rank of next process in ring
    int prev = (rank - 1 + size) % size;  // Compute rank of previous process, handling wrap-around

    MPI_Sendrecv(&send_val, 1, MPI_INT, next, 0,  // Send to next
                 &recv_val, 1, MPI_INT, prev, 0,  // Receive from previous
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Use same communicator and tag, ignore status

    std::cout << "Process " << rank << " received " << recv_val << " from process " << prev << std::endl;

    MPI_Finalize();
    return 0;
}