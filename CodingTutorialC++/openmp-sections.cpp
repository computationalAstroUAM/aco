//
// Created by weiguang on 9/05/24.
//
#include <omp.h>
#include <iostream>

void task1() {
    std::cout << "Task 1 executed by thread " << omp_get_thread_num() << std::endl;
}

void task2() {
    std::cout << "Task 2 executed by thread " << omp_get_thread_num() << std::endl;
}

void task3() {
    std::cout << "Task 3 executed by thread " << omp_get_thread_num() << std::endl;
}

void task4() {
    std::cout << "Task 4 executed by thread " << omp_get_thread_num() << std::endl;
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            task1();
        }

        #pragma omp section
        {
            task2();
        }

        #pragma omp section
        {
            task3();
        }

        #pragma omp section
        {
            task4();
        }
    }

    return 0;
}