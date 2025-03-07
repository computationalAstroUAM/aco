cmake_minimum_required(VERSION 3.27)
project(ACO_practice)

set(CMAKE_CXX_STANDARD 11)

add_executable(ACO_practice overflow.cpp
        MainArgs.cpp
        openmp-example.cpp
        pi.cpp
        pointer-dam.cpp
        pointer-update-parameter.cpp
        pointer-dam3D.cpp
        IO.cpp
        class.cpp
        structure.cpp
        different_arrays.cpp
        vector.cpp
        Sort_index.cpp
        openmp-no-parallel.cpp
        openmp-sections.cpp
        openmp-nested-for-loop.cpp
        openmp-parallel-output.cpp
        problemtic_program_for_gdb.cpp
        mpi_example.cpp
)
