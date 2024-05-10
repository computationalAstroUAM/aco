//
// Created by weiguang on 10/05/24.
//
#include <iostream>

int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Attempt to access the array out of its bounds
    for (int i = 0; i <= 10; i++) {
        arr[i] += i;
        std::cout << arr[i] << std::endl;  // This will cause a segmentation fault when i == 10
    }

    return 0;
}