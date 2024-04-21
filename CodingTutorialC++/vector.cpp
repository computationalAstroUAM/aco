//
// Created by weiguang on 21/04/24.
//
#include <iostream>
#include <vector>

int main() {
    // Create a vector
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Print the vector
    std::cout << "Vector: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Size of the vector
    std::cout << "Size: " << vec.size() << "\n";

    // Capacity of the vector
    std::cout << "Capacity: " << vec.capacity() << "\n";

    // vector size and Max size of the vector
    std::cout << "Size: " << vec.size() << "  Max Size: " << vec.max_size() << "\n";

    // vector begin and end
    // begin is an iterator to the first element, end is an iterator to the last element
    // iterator is a pointer to the element in the vector, but not the same as pointer, you can not print this out directly
    std::cout << "Begin: " << &(*vec.begin()) << "  End: " << &(*vec.end()) << "\n";
    // is vec.begin() the same as &vec[0] or vec?
    // is vec.end() the same as &vec[vec.size()] or vec+vec.size()?
    std::cout << "Begin: " << &vec[0] << "  End: " << &vec[0]+vec.size() << "\n";

    // vector front and back
    std::cout << "Front: " << vec.front() << "  Back: " << vec.back() << "\n";
    // is vec.front() the same as vec[0]? and vec.back() the same as vec[vec.size()-1]?
    std::cout << "Front: " << vec[0] << "  Back: " << vec[vec.size()-1] << "\n";

    // Resize the vector
    vec.resize(7, 0);
    std::cout << "Resized Vector: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Check if the vector is empty
    std::cout << "Is Empty: " << (vec.empty() ? "Yes" : "No") << "\n";

    // Insert an element at the beginning
    vec.insert(vec.begin(), 0);
    std::cout << "After Insertion: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Erase the first element
    vec.erase(vec.begin());
    std::cout << "After Erasure: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Push an element at the end
    vec.push_back(6);
    std::cout << "After Push Back: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Pop the last element
    vec.pop_back();
    std::cout << "After Pop Back: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Clear the vector
    vec.clear();
    std::cout << "After Clear: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Shrink the vector
    vec.shrink_to_fit();
    std::cout << "After Shrink: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // in last two examples, the vector is empty, so the output is empty
    // But what about its size? How much memory does it occupy?
    // Try it out by yourself to see the difference between the two examples

    return 0;
}