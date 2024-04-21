//
// Created by weiguang on 21/04/24.
//
#include <iostream>
#include <array>
#include <vector>

// this is function for C++ array out of scope test
void test_array_out_of_scope() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Array out of scope: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "at the memory location: " << arr << "\n";
} // end of function for C++ array out of scope

int main() {
    // Array
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // test array out of scope
    test_array_out_of_scope();
    int* arr2 = new int[100000000];
    test_array_out_of_scope(); // run twice to see if the memory location is the same
    delete[] arr2;

    // std::array
    std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
    std::cout << "std::array: ";
    for (int i = 0; i < std_arr.size(); i++) {
        std::cout << std_arr[i] << " ";
    }
    std::cout << "\n";

    // Dynamically allocated array
    int* dyn_arr = new int[5];
    for (int i = 0; i < 5; i++) {
        dyn_arr[i] = i + 1;
    }
    std::cout << "Dynamically allocated array: ";
    for (int i = 0; i < 5; i++) {
        std::cout << dyn_arr[i] << " ";
    }
    std::cout << "\n";
    delete[] dyn_arr; // Don't forget to delete the allocated memory

    // Vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Vector: ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    // Demonstrating vector resizing
    vec.resize(7, 0); // Resize to 7 elements, fill new elements with 0
    std::cout << "Resized vector: ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    // Demonstrating vector insertion
    vec.insert(vec.begin() + 2, 99); // Insert 99 at position 2
    std::cout << "Vector after insertion: ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    // Demonstrating vector erasure
    vec.erase(vec.begin() + 2); // Erase element at position 2
    std::cout << "Vector after erasure: ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    return 0;
}