//
// Created by weiguang on 18/04/24.
//
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <vector>
#include <fstream>
#include <omp.h>
#include <iostream>

#include "define.h"

int write_output(std::vector<double> &c_real, std::vector<double> &c_img, std::vector<int> &converged, int NPOINTS_PER_DIM_REAL, int NPOINTS_PER_DIM_IMG)
{
  std::ofstream fpout;
//	std::cout<<C_REAL_MAX;
  // open output file
  //==================
  fpout.open("mandelbrot.dat");
  // error handling in subroutine: return(0) upon failure
  if( !fpout.is_open() ) {
    std::cout << __func__ << ": could not open output file mandelbrot.dat\nRETURNING\n";
    return(0);
   }

  // write results to file
  //=======================
#pragma omp parallel for default(none) shared(c_img, c_real, converged, fpout, NPOINTS_PER_DIM_REAL, NPOINTS_PER_DIM_IMG)
  for(int i=0; i<NPOINTS_PER_DIM_REAL; i++) {
    for(int j=0; j<NPOINTS_PER_DIM_IMG; j++) {

      // only write converged points to file
//      if(converged[index(i,j,NPOINTS_PER_DIM_IMG)] == NMAX_ITER)
      {
#pragma omp critical
        {
          fpout << c_real[i] << " " << c_img[j] << " " << converged[index(i,j,NPOINTS_PER_DIM_IMG)] << "\n";
        }
      }
    }
  }

  // close the file again
  //======================
  fpout.close();

  // return(1) upon success
  return(1);
}
