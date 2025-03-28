#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <thread>
#include <chrono>

// 1. Array Out of Bounds
void arrayOutOfBounds() {
    int arr[5];
    try {
        arr[10] = 42;  // Segfault: Accessing beyond array bounds
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 2. Null Pointer Dereference
void nullPointer() {
    int* ptr = nullptr;
    try {
        *ptr = 42;  // Segfault: Dereferencing null pointer
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 3. Double Free
void doubleFree() {
    int* ptr = new int;
    try {
        delete ptr;
        delete ptr;  // Segfault: Double free
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 4. Stack Overflow
void recursiveFunction(int depth) {
    if (depth > 0) {
        int large[100000];
        recursiveFunction(depth - 1);
    }
}

void stackOverflow() {
    try {
        recursiveFunction(1000);  // Segfault: Stack overflow
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 5. Invalid Memory Access
void invalidMemoryAccess() {
    int* ptr = new int;
    try {
        delete ptr;
        *ptr = 42;  // Segfault: Accessing freed memory
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 6. Buffer Overflow
void bufferOverflow() {
    char buffer[10];
    try {
        strcpy(buffer, "This is too long");  // Segfault: Buffer overflow
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 7. Memory Management
void memoryManagement() {
    try {
        while (true) {
            new int[1000000];  // Eventually leads to segfault
        }
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 8. Race Condition
void raceCondition() {
    std::vector<int> shared;
    try {
        std::thread t1([&] {
            shared[0] = 42;  // Potential segfault: Race condition
        });
        std::thread t2([&] {
            shared[0] = 84;  // Potential segfault: Race condition
        });
        
        t1.join();
        t2.join();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 9. Invalid Function Pointer
void functionPointer() {
    void (*func)(void) = nullptr;
    try {
        func();  // Segfault: Calling null function pointer
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 10. System Resource Limits
void resourceLimits() {
    int fds[100000];  // Segfault: Exceeding file descriptor limit
}

int main() {
    std::cout << "Segmentation Fault Examples:" << std::endl;
    std::cout << "1. Array Out of Bounds" << std::endl;
    std::cout << "2. Null Pointer Dereference" << std::endl;
    std::cout << "3. Double Free" << std::endl;
    std::cout << "4. Stack Overflow" << std::endl;
    std::cout << "5. Invalid Memory Access" << std::endl;
    std::cout << "6. Buffer Overflow" << std::endl;
    std::cout << "7. Memory Management" << std::endl;
    std::cout << "8. Race Condition" << std::endl;
    std::cout << "9. Invalid Function Pointer" << std::endl;
    std::cout << "10. System Resource Limits" << std::endl;

    int choice;
    std::cout << "\nEnter the number of the example you want to run (0 to exit): ";
    std::cin >> choice;

    while (choice != 0) {
        switch (choice) {
            case 1: arrayOutOfBounds(); break;
            case 2: nullPointer(); break;
            case 3: doubleFree(); break;
            case 4: stackOverflow(); break;
            case 5: invalidMemoryAccess(); break;
            case 6: bufferOverflow(); break;
            case 7: memoryManagement(); break;
            case 8: raceCondition(); break;
            case 9: functionPointer(); break;
            case 10: resourceLimits(); break;
            default: std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << "\nEnter the number of the example you want to run (0 to exit): ";
        std::cin >> choice;
    }

    return 0;
}