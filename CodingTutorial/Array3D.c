//===========================================================================================
// test05
//
// the aim of this exercise is to dynamically allocte multi-dimensional arrays
//
// the exercise also shows:
//  - Cache misses
//  - inline timing of code (time(), difftime(), ...)
//  - improved usage of #define
//  - DEFINEFLAGS: #ifdef/#else/#end to fork code
//
//           **** fall back to -O0 optimisation to see the stack overflow *****
//           **** fall back to -O2 optimisation for 'BAD' timing          *****
//
// note: b[i][j][k] is mere pointer arithmetic whereas a[index(i,j,k)] involves mutiplications
//===========================================================================================
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include "my.h"

// constants
#define N          ((uint64_t)500)
#define M          ((uint64_t)600)
#define L          ((uint64_t)700)
//#define N        ((uint64_t)10)
//#define M        ((uint64_t)20)
//#define L        ((uint64_t)30)

// shortcuts and prototypes
#define index(i,j,k) ((i)*(M)*(L) + (j)*(L) + (k))  // k runs fastest
//#define BAD

int main(void)
{
  double    *a;              // dynamic 1D array to be accessed like 3D array
  double  ***b;              // dynamic 3D array
  double     c[N][M][L];     // static  3D array
  uint64_t   i,j,k;
  time_t     tstart, tend;

  // checkpoint time
  tstart = time(NULL);
  
  //=======================================================================
  // 1. simply use previously declared 3D array
  //=======================================================================
#ifdef BAD
  fprintf(stderr,"BAD\n");
  for (k=0; k<L; k++){
    for(j=0; j<M; j++) {
      for (i=0; i<N; i++) {
#else // GOOD
  for (i=0; i<N; i++) {
    for(j=0; j<M; j++) {
      for (k=0; k<L; k++){
#endif
        c[i][j][k] = pow((double)(i*j*k),1.5);
      }
    }
  }
  fprintf(stderr,"successfully generated and filled c[][][]\n");

  //=======================================================================
  // 2. generate one-dimensional array to be accessed like 3D array
  //=======================================================================
  a = (double *) my_calloc(N*M*L, sizeof(double));

#ifdef BAD
  for (k=0; k<L; k++){
    for(j=0; j<M; j++) {
      for (i=0; i<N; i++) {
#else // GOOD
  for (i=0; i<N; i++) {
    for(j=0; j<M; j++) {
      for (k=0; k<L; k++){
#endif
        a[index(i,j,k)] = pow((double)(i*j*k),1.5);
      }
    }
  }
  fprintf(stderr,"successfully generated and filled a[]\n");

  //=======================================================================
  // 3. generate array to be accessed like 3D array
  //=======================================================================
  b = (double ***) my_calloc(N, sizeof(double **)); // note: this is a memory overhead!
  for(i=0; i<N; i++) {
    b[i] = (double **) my_calloc(M, sizeof(double *));
    for(j=0; j<M; j++) {
      b[i][j] = (double *) my_calloc(L, sizeof(double));
    }
  }
#ifdef BAD
  for (k=0; k<L; k++){
    for(j=0; j<M; j++) {
      for (i=0; i<N; i++) {
#else // GOOD
  for (i=0; i<N; i++) {
    for(j=0; j<M; j++) {
      for (k=0; k<L; k++){
#endif
        b[i][j][k] = pow((double)(i*j*k),1.5);
      }
    }
  }
  fprintf(stderr,"successfully generated and filled b[][][]\n");

  // checkpoint time
  tend = time(NULL);
  fprintf(stderr,"elapsed time: %3.1lf [sec]\n",difftime(tend,tstart));

  //=======================================================================
  // check sizes of c[][][] against a[] against b[][][]
  //=======================================================================
  fprintf(stderr,"sizeof(c)=%ld (%lf MB)\n",sizeof(c),sizeof(c)/1024./1024.);
  fprintf(stderr,"sizeof(a)=%ld (%lf MB)\n",N*M*L*sizeof(double),N*M*L*sizeof(double)/1024./1024.);
  fprintf(stderr,"sizeof(b)=%ld (%lf MB)\n",(N*sizeof(double **)+N*M*sizeof(double *)+N*M*L*sizeof(double)),(N*sizeof(double **)+N*M*sizeof(double *)+N*M*L*sizeof(double))/1024./1024.);
        
  //=======================================================================
  // do not forget to free all the allocated memory
  //=======================================================================
  // obvious
  free(a);

  // careful here: *every* calloc() has to have a corresponding free()!
  for(i=0; i<N; i++) {
    for(j=0; j<M; j++) {
      free(b[i][j]);
    }
    free(b[i]);
  }
  free(b);
  
  return(1);
}
