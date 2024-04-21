#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <omp.h>
#include <cmath>
#ifdef HIGH_TIME_PRECISION
#include <chrono>
#else
#include <ctime>
#endif
#include <vector>
#include <iostream>
#include <iomanip>

// some useful definitions
#include "define.h"

// include the prototypes
#include "functions.h"

int main(int argc, char **argv)
{
    int NPOINTS_PER_DIM_REAL,NPOINTS_PER_DIM_IMG;
    int omp_num_threads;
#ifdef HIGH_TIME_PRECISION
    std::chrono::time_point<std::chrono::system_clock> tstart, tend;
#else
    time_t  tstart, tend;
#endif

    // get number of points per dimension from command line
    //======================================================
    if(argc != 4) {
        std::cout << "usage: " << argv[0] << " POINTS_PER_DIM_REAL NPOINTS_PER_DIM_IMG omp_num_threads" << std::endl;
        exit(0);
    }
    NPOINTS_PER_DIM_REAL = std::atoi(argv[1]);
    NPOINTS_PER_DIM_IMG  = std::atoi(argv[2]);
    omp_num_threads      = std::atoi(argv[3]);


    // parallel environment
    //======================
    omp_set_num_threads(omp_num_threads);
#pragma omp parallel default(none) shared(std::cout)
    {
        // who am I?
        int ithread = omp_get_thread_num();
#pragma omp critical
        {
            std::cout << "ithread=" << ithread << "\n";
        }

        /* only one thread (==0) does this */
        if (ithread == 0)
        {
            int ncpus       = omp_get_num_procs();
            int nthreads    = omp_get_num_threads();
#pragma omp critical
            {
                std::cout << "ncpus=" << ncpus << " nthreads=" << nthreads << "\n";
            }
        }
    }

    // arrays holding complex numbers and converged status
    //=====================================================
    std::vector<int> converged(NPOINTS_PER_DIM_REAL*NPOINTS_PER_DIM_IMG);
    std::vector<double> c_real(NPOINTS_PER_DIM_REAL);
    std::vector<double> c_img(NPOINTS_PER_DIM_IMG);

    //=======================================================
    // fill arrays with values
    //=======================================================
#pragma omp parallel for
    for(int i=0; i<NPOINTS_PER_DIM_REAL; i++) {
        c_real[i] = (C_REAL_MAX-C_REAL_MIN)*(double)i/(double)(NPOINTS_PER_DIM_REAL-1) + C_REAL_MIN;
    }
#pragma omp parallel for
    for(int i=0; i<NPOINTS_PER_DIM_IMG; i++) {
        c_img[i]  = (C_IMG_MAX -C_IMG_MIN) *(double)i/(double)(NPOINTS_PER_DIM_IMG-1)  + C_IMG_MIN;
    }


    //=======================================================
    // check convergence/divergence for each of these points
    //=======================================================
#ifdef HIGH_TIME_PRECISION
    tstart = std::chrono::system_clock::now();
#else
    tstart = time(NULL);
#endif
#pragma omp parallel for schedule(dynamic)
    for(int i=0; i<NPOINTS_PER_DIM_REAL; i++) {
        for(int j=0; j<NPOINTS_PER_DIM_IMG; j++) {
            converged[index(i,j,NPOINTS_PER_DIM_IMG)] = mandelbrot_series(c_real[i],c_img[j]);
        }
    }
#ifdef HIGH_TIME_PRECISION
    tend = std::chrono::system_clock::now();
    std::cout << std::fixed << std::setprecision(10) << "the Mandelbrot loop took " << std::chrono::duration<double>(tend-tstart).count() << " sec. (wall-clock time)\n";
#else
    tend = time(NULL);
    std::cout << std::fixed << std::setprecision(10) << "the Mandelbrot loop took " << difftime(tend,tstart) << " sec. (wall-clock time)\n";
#endif

    //=======================================================
    // write output file
    //=======================================================
#ifdef HIGH_TIME_PRECISION
    tstart = std::chrono::system_clock::now();
#else
    tstart = time(NULL);
#endif
    if(write_output(c_real, c_img, converged, NPOINTS_PER_DIM_REAL, NPOINTS_PER_DIM_IMG) == 0) {
        std::cout << "Could not write output file\nABORTING\n";
        exit(0);
    }
#ifdef HIGH_TIME_PRECISION
    tend = std::chrono::system_clock::now();
    std::cout << std::fixed << std::setprecision(10) << "the writing of the output file took " << std::chrono::duration<double>(tend-tstart).count() << " sec. (wall-clock time)\n";
#else
    tend = time(NULL);
    std::cout << std::fixed << std::setprecision(10) << "the writing of the output file took " << difftime(tend,tstart) << " sec. (wall-clock time)\n";
#endif
    return 1;
}