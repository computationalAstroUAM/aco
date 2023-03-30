//===========================================================================================
// test06
//
// the aim of this exercise is to compare serial and parallel code for recursion
//
// additional aims:
//  - use #define/#ifdef to bifurcate code (_OPENMP)
//
//  - schedule(dynamic) vs. schedule(static):
//    (all compiled with -O0):
//        a) serial       =>   55 sec. (use via setenv OMP_NUM_THREADS 1)
//        b) static       =>   25 sec.
//        c) dynamic      =>   16 sec.
//
//===========================================================================================
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

// constants
#define STARTVALUE 1.1
#define N          ((uint64_t)1<<17)

// prototypes
double  function    (double);
double  calculation (uint64_t, double);

//=================================================================
// main()
//=================================================================
int main(void)
{
  double   *a;
  uint64_t  i;
  time_t    tstart, tend;
  int       nthreads;
  
  
  // dynamically generate one-dimensional array
  a = (double *) calloc(N, sizeof(double));
  
#ifdef _OPENMP
#pragma omp parallel default(none) private(nthreads) shared(stderr)
  {
    if (omp_get_thread_num() == 0) {
      nthreads = omp_get_num_threads();
      fprintf(stderr,"nthreads=%d\n",nthreads);
    }
  }
#endif // _OPENMP
  
  tstart = time(NULL);
  
  // fill all array elements
#ifdef _OPENMP
#pragma omp parallel for private(i) shared(a) default(none) schedule(static)
  // note: the loop starts at 0!!
  for(i=0; i<N; i++) {
    a[i] = calculation(i,STARTVALUE); // note: STARTVALUE will be replaced with a number by the pre-processor
  }
#else // _OPENMP
  a[0] = STARTVALUE;
  for(i=1; i<N; i++) {
    a[i] = 1.01*a[i-1];
  }
#endif // _OPENMP
  
  
  tend = time(NULL);
  fprintf(stderr,"the loop took %lf sec. (wall-clock time)\n",difftime(tend,tstart));
  
  // do not forget to free the allocated memory
  free(a);
  
  return(1);
}

//=================================================================
// function that hides all the calculation to be done in parallel
//=================================================================
double calculation(uint64_t i, double b)
{
  uint64_t j;
  
  for(j=0; j<i; j++) {
    b = function(b);
  }
  return(b);
}

//=================================================================
// function()
//=================================================================
double function(double x)
{
  // simply make value 1% larger
  return(1.01*x);
}
