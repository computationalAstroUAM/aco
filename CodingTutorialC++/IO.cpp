//
// Created by weiguang on 10/04/24.
//
#include <iostream>
#include <fstream>
#include <string>
using std::string;

// Function to write and read array data to and from a text file
void writeArrayToFile(int* array, int size, string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for(int i = 0; i < size; ++i) {
            file << array[i] << ' ';
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

void readArrayFromFile(int* array, int size, string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for(int i = 0; i < size; ++i) {
            file >> array[i];
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }
}

// Function to write and read array data to and from a binary file
void writeArrayToBinaryFile(int* array, int size, string filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(array), sizeof(int) * size);
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

void readArrayFromBinaryFile(int* array, int size, string filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(array), sizeof(int) * size);
        file.close();
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }
}

int main() {
    int array1D[5] = {1, 2, 3, 4, 5};

    // Write and read array data to and from a text file
    string fn = "output.txt";
    writeArrayToFile(array1D, 5, fn);
    readArrayFromFile(array1D, 5, fn);

    // Write and read array data to and from a binary file
    fn = "output.bin";
    writeArrayToBinaryFile(array1D, 5, fn);
    readArrayFromBinaryFile(array1D, 5, fn);

    return 0;
}