cmake_minimum_required(VERSION 3.27)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 11)

add_executable(Mandelbrot main.cpp
        define.h
        functions.h
        write_output.cpp
        mandelbrot_series.cpp)
