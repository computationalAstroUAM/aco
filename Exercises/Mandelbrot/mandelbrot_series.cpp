//
// Created by weiguang on 18/04/24.
//
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <cmath>
#include <complex>

#include "define.h"

int mandelbrot_series(double c_real, double c_img)
{
  bool diverged;
  int n;
  std::complex<double> c, z;    // C++ knows complex numbers

  // initial the first starting values
  //===================================
  c = std::complex<double>(c_real, c_img);
  z = c;

  // generate the next element until convergence or divergence
  //===========================================================
  diverged = false;
  n        = 0;
  while(!diverged && n<NMAX_ITER) {

    // use the Mandelbrot recursion formula to calculate the next element
    z = z*z + c;

    // increment iteration counter
    n = n + 1;

    // has the series diverged?
    if(std::abs(z) > 4) {
      diverged = true;
    }
  }

  // return the number of iterations:
  //   if n == NMAX_ITER the series has not diverged
  //   if n <  NMAX_ITER the series diverged and n indicates how fast it diverged
  return(n);
}
