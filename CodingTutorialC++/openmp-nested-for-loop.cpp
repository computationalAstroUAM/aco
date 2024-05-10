//
// Created by weiguang on 9/05/24.
//
#include <omp.h>
#include <iostream>

int main() {
    int N = 1000;
    int M = 10;
    int matrix[N][M];

//    #pragma omp parallel for collapse(2)
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
//        #pragma omp parallel for
        for(int j = 0; j < M; j++) {
            matrix[i][j] = i * j;
        }
    }

    return 0;
}