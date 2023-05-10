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
#define N          ((uint64_t)1<<11)
#ifndef _OPENMP
#define _OPENMP
#endif

// prototypes
double  function    (double);
double  calculation (uint64_t, double);

//=================================================================
// main()
//=================================================================
int main(void)
{
  double   *a, *b;
  uint64_t  i,j;
  double    tstart, tend;
  int       nthreads;


  // dynamically generate one-dimensional array
  a = (double *) calloc(N, sizeof(double));
  b = (double *) calloc(N, sizeof(double));

#ifdef _OPENMP
#pragma omp parallel default(none) private(nthreads) shared(stderr)
  {
    if (omp_get_thread_num() == 0) {
      nthreads = omp_get_num_threads();
      fprintf(stderr,"nthreads=%d, N=%ld\n",nthreads,N);
    }
  }

#endif // _OPENMP

  tstart = omp_get_wtime();

  // fill all array elements
#ifdef _OPENMP
#pragma omp parallel for private(i,j,a) shared(b) //default(none) 
  // note: the loop starts at 0!!
  for(i=0; i<N; i++) {
    a[i] = function(i-1);
    //a[i]=function(a[i-1]);
//#pragma omp parallel for 
    for(j=0; j<N; j++) {
      b[j] = calculation(i,a[i]); // note: STARTVALUE will be replaced with a number by the pre-processor
    }
  }
#else // _OPENMP
  a[0] = STARTVALUE;
  for(i=1; i<N; i++) {
    a[i] = 1.01*a[i-1];
  }
#endif // _OPENMP
  
  tend = (omp_get_wtime() - tstart); //s
  fprintf(stderr,"the loop took %lf sec. (wall-clock time)\n", tend);
//for (i=0;i<N;i++)
//  printf("a=%lf\t", a[i]);
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

