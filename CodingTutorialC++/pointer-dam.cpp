//
// Created by weiguang on 7/04/24.
/*In this code, we try to allocate a large amount of memory. If the allocation fails, a std::bad_alloc exception
 * is caught and an error message is printed. The requested size of the memory is also printed.
 * If the allocation is successful, the memory is deallocated using delete[].*/
//
#include <iostream>
#include <new>

int main() {
    long long int size = 1e18; // A large size that may exceed the physical memory

    char* myarray = nullptr;
    try {
        myarray = new char[size]; // Try to allocate memory
    } catch (std::bad_alloc& ba) {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        std::cerr << "Memory allocation failed. Requested size was " << size << '\n';
    }

    delete[] myarray; // Deallocate the array from the heap
    // Note delete and delete[] are used to deallocate memory that was previously allocated with new and new[], respectively
    return 0;
}