cmake_minimum_required(VERSION 3.28)
project(Kapler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kapler main.cpp
        orbit.h
        orbit.cpp)
