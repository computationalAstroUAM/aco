//
// Created by weiguang on 9/05/24.
//
#include <omp.h>
#include <iostream>
#include <vector>

// Sequential tasks
void sequentialTasks() {
    int arr[10];
    arr[0] = 1;
    int brr[10];
    brr[0] = 1;

//#pragma omp parallel sections
    for(int i = 1; i < 10; i++) {
//#pragma omp parallel sections  // any difference?
//        #pragma omp section
        arr[i] = arr[i-1] * 2; // Each iteration depends on the previous one
//        #pragma omp section
        brr[i] = brr[i-1] * 3;
    }

    for(int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Shared resource access
void sharedResourceAccess() {
    std::vector<int> sharedVector;

//    #pragma omp parallel for
    for(int i = 0; i < 100; i++) {
        sharedVector.push_back(i); // Race condition here
    }

    std::cout << "Vector size: " << sharedVector.size() << std::endl;
}

// Recursion
int fibonacci(int n) {
    if(n <= 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2); // Recursive calls
    }
}

void testFibonacci() {
    std::cout << "Fibonacci(10): " << fibonacci(10) << std::endl;
}

// Complex dependencies
void complexDependencies() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> results(numbers.size());

    for(int i = 1; i < numbers.size() - 1; i++) {
        results[i] = numbers[i-1] * numbers[i+1]; // Each operation depends on the previous and next number
    }

    for(int i = 0; i < results.size(); i++) {
        std::cout << results[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Sequential tasks example:\n";
    sequentialTasks();

    std::cout << "\nShared resource access example:\n";
    sharedResourceAccess();

    std::cout << "\nRecursion example:\n";
    testFibonacci();

    std::cout << "\nComplex dependencies example:\n";
    complexDependencies();

    return 0;
}
