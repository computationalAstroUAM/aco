//
// Created by weiguang on 21/04/24.
//
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

// Sort an array and return the indices
std::vector<size_t> sortWithIndex(int* begin, int* end) {
    size_t size = end - begin;
    std::vector<size_t> indices(size);
    std::iota(indices.begin(), indices.end(), 0);

    // using structure for comparison function
    struct Compare {
        int* values;
        Compare(int* v) : values(v) {}
        bool operator()(size_t a, size_t b) const {
            return values[a] < values[b];
        }
    };
    std::sort(indices.begin(), indices.end(), Compare(begin));

    // using lambda function
//    std::sort(indices.begin(), indices.end(),
//       [begin](size_t a, size_t b) { return begin[a] < begin[b]; });

    return indices;
}

int main() {
    // Regular array
    int arr[] = {5, 2, 3, 1, 4};
    auto indices = sortWithIndex(arr, arr + 5); // does the array being sorted?
    std::cout << "Indices for sorted regular array: ";
    for (auto i : indices) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // std::array
    std::array<int, 5> stdArr = {5, 2, 3, 1, 4};
    indices = sortWithIndex(stdArr.data(), stdArr.data() + stdArr.size());
    std::cout << "Indices for sorted std::array: ";
    for (auto i : indices) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Dynamically allocated array
    int* dynArr = new int[5]{5, 2, 3, 1, 4};
    indices = sortWithIndex(dynArr, dynArr + 5);
    std::cout << "Indices for sorted dynamically allocated array: ";
    for (auto i : indices) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    delete[] dynArr;

    // Vector
    std::vector<int> vec = {5, 2, 3, 1, 4};
    indices = sortWithIndex(vec.data(), vec.data() + vec.size());
    std::cout << "Indices for sorted vector: ";
    for (auto i : indices) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}