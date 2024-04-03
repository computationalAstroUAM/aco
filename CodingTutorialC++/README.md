# ACO_practice

This project is written in C++ and includes the following files:

## Source Files

### [`overflow.cpp`](./overflow.cpp)

This file contains a program that demonstrates integer and floating point overflow and underflow. It also demonstrates the precision error that can occur with floating point numbers.

### [`MainArgs.cpp`](./MainArgs.cpp)

This file contains a program that prints the name of the program and all the arguments passed to it.

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
```

To clean up the built files, use the make clean command:
```bash
make clean
```