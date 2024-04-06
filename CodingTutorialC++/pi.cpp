//
// Created by weiguang on 6/04/24.
//
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <omp.h>
#include <ctime>
#include <iomanip>

#define INFTY ((uint64_t)1<<30)

int main(int argc, char **argv)
{
  uint64_t k;
  double pi;
  time_t tstart, tend;
  int    nthreads_to_be_used;

  if(argc != 2) {
    std::cerr << "usage: ./pi NTHREADS\nABORTING\n";
    return 1;
  }

  nthreads_to_be_used = std::atoi(argv[1]);
  std::cerr << "using " << nthreads_to_be_used << " threads for execution\n";
  omp_set_num_threads(nthreads_to_be_used);

#pragma omp parallel shared(std::cerr) default(none)
  {
    // all private by construction
    int nthreads, ncpus, ithread, omp_num_threads;

    // who am I?
    ithread = omp_get_thread_num();

    /* only one thread (==0) does this */
    if (ithread == 0)
    {
      ncpus       = omp_get_num_procs();
      nthreads    = omp_get_num_threads();
      std::cerr << "ncpus=" << ncpus << " nthreads=" << nthreads << "\n";
    }
  }

  pi = 0.0;

  tstart = time(NULL);
#pragma omp parallel for default(none) private(k) reduction(+:pi) schedule(static)
  for(k=0; k<INFTY; k++) {
    pi += std::pow(-1.0/3.0, (double)k) / (2.*(double)k+1.);
  }
  tend = time(NULL);

  pi *= std::sqrt(12);
  std::cerr << "pi = " << std::fixed << std::setprecision(12) << pi << " (time=" << std::difftime(tend,tstart) << " [sec])\n";

  return 0;
}