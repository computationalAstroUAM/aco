# ACO_practice

This project is written in C++ and includes the following files:

## Source Files

### [`overflow.cpp`](./overflow.cpp)

This file contains a program that demonstrates integer and floating point overflow and underflow. It also demonstrates the precision error that can occur with floating point numbers.

### [`MainArgs.cpp`](./MainArgs.cpp)

This file contains a program that prints the name of the program and all the arguments passed to it.

### [`openmp-example.cpp`](./openmp-example.cpp)

This file contains a program that uses OpenMP to calculate the sum of numbers from 1 to 1e5. It sets the number of threads to the number of processors available, and each thread calculates a portion of the sum.

### [`pi.cpp`](./pi.cpp)

This file contains a program that calculates the value of pi using the Leibniz formula for π. The program uses OpenMP for parallel computation, allowing it to calculate pi to a high degree of precision in a shorter amount of time. The number of threads used for the computation can be specified as a command-line argument when running the program.
To build and run `pi.cpp`, use the make command followed by the name of the file (without the .cpp extension), and then run the resulting executable with the number of threads as an argument:

### [`pointer-dam.cpp`](./pointer-dam.cpp)

This file contains a program that demonstrates the use of pointers and memory management in C++. It includes examples of pointer arithmetic, dynamic memory allocation, and memory leaks.

### [`pointer-dam3D.cpp`](./pointer-dam3D.cpp)

This file extends the concepts demonstrated in `pointer-dam.cpp` to three dimensions. It includes examples of working with 3D arrays and pointers, including dynamic memory allocation for 3D arrays.

### [`IO.cpp`](./IO.cpp)

This file contains a program that demonstrates how to write and read array data to and from a text file and a binary file in C++. It includes examples of using the `fstream` library for file I/O operations.

### [`pointer-update-parameter.cpp`](./pointer-update-parameter.cpp)

This file contains a program that demonstrates how to use pointers to change the value of a parameter inside a function. It includes examples of passing pointers to functions and updating the value they point to.

### [`class.cpp`](./class.cpp)

This file contains a program that demonstrates the use of classes and objects in C++. It includes examples of defining classes, creating objects, and accessing class members.

### [`structure.cpp`](./structure.cpp)

This file contains a program that demonstrates the use of structures in C++. It includes examples of defining structures, creating structure variables, and accessing structure members.

### [different_arrays.cpp](./different_arrays.cpp)

This file contains a program that demonstrates the use of different types of arrays in C++. It includes examples of C++ default array, std::array, dynamically allocated array and std::vector.

### [vector.cpp](./vector.cpp)

This file contains a program that demonstrates the use of std::vector in C++. It includes examples of creating vectors, adding elements to vectors, accessing vector elements, and different vector built-in functions.

### [Sort_index.cpp](./Sort_index.cpp)

This file contains a program that demonstrates how to sort an array and get the index of the sorted array in C++. It includes examples of using std::sort and std::vector.

```bash
make pi
./pi 4 This will build `pi.cpp` and run the resulting `pi` executable with 4 threads.
```

## Build Files

### [`Makefile`](./Makefile)

This file is used to build the project. It includes targets for building the entire project, as well as individual targets for `overflow.cpp` and `MainArgs.cpp`. The `clean` target is used to remove the built executables and object files.

### [`CMakeLists.txt`](./CMakeLists.txt)

This file is used by CMake to generate a build system for the project. It specifies the minimum required version of CMake, the name of the project, the C++ standard to use, and the source files to compile.

## How to Build

To build the entire project, use the `make` command:

```bash
make
```

To build individual files, use the make command followed by the name of the file (without the .cpp extension):
```bash
make overflow
make MainArgs
make openmp-example
make pi
make pointer-dam
make pointer-dam3D
make pointer-update-parameter
make IO
make class
make structure
```

To clean up the built files, use the make clean command:
```bash
make clean
```