//
// Created by weiguang on 10/04/24.
//
/*In this code, we first allocate memory for x number of 2D arrays. Then for each 2D array, we allocate memory for y
 * number of 1D arrays. Finally, for each 1D array, we allocate memory for z number of integers.
 *
 * When deallocating, we must deallocate in the reverse order of allocation. First, we deallocate each 1D array, then
 * each 2D array, and finally the 3D array itself.*/
#include <iostream>

//
int main() {
    // Dimensions of the 3D array
    int x = 10;
    int y = 20;
    int z = 30;

    // Allocate memory
    int*** array = new int**[x];
    for(int i = 0; i < x; ++i) {
        array[i] = new int*[y];
        for(int j = 0; j < y; ++j) {
            array[i][j] = new int[z];
        }
    }

    // Use the array
    array[0][0][0]=1;
    array[1][2][3]=2;
    std::cout << ***array << std::endl; // Outputs: 1
    std::cout  << "array[1][2][3] =" << *(*(*(array+1)+2)+3)<< std::endl; // Outputs: 2
    std::cout  << "array[1][2][3] =" << ***(array+1*y*z+2*z+3)<< std::endl; // Outputs: 2

    // Deallocate memory
    for(int i = 0; i < x; ++i) {
        for(int j = 0; j < y; ++j) {
            delete[] array[i][j];
        }
        delete[] array[i];
    }
    delete[] array;

    return 0;
}