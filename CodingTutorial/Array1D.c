//===========================================================================================
// test04
//
// the aim of this exercise is to demonstrate the difference between dynamic and static
//                                                                   memory allocation
// this exercise also shows:
//  - the usage of #define
//  - usage of my_*() functions
//===========================================================================================
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "my.h"

//#define M  1073741824  // = 1<<30 -> leads to a segmentation fault
#define M    72349827  // this actually already leads to a seg-fault
//#define M 7

int main(int argc, char **argv)
{
  int     i, N;
  double  b[M];   //  static generation of array (will fail for large M)
  double *a;      // dynamic generation of array (of size N, from command line)
  
  
  // we need at least argc=2
  if(argc!=2) {
    fprintf(stderr,"usage: %s N\nAborting\n",argv[0]);
    exit(-1); }

  // get number of elements for array a[] from command line
  N = (int) atoi(argv[1]);

  // allocate memory
  a = (double *) my_calloc(N, sizeof(double));

  // 1. access directly like 1D array
  for(i=0; i<M; i++) {
    b[i] = 2*sqrt(i); }
  for(i=0; i<N; i++) {
    a[i] = 2*sqrt(i); }

  for(i=0; i<M; i++) {
    fprintf(stderr,"i=%d b=%lf\n",i,b[i]); }
  fprintf(stderr,"\n");
  for(i=0; i<N; i++) {
    fprintf(stderr,"i=%d a=%lf\n",i,a[i]); }
  fprintf(stderr,"\n\n");

  // 2. access like pointer
  for(i=0; i<M; i++) {
    *(b+i) = 2*sqrt(i); }
  for(i=0; i<N; i++) {
    *(a+i) = 2*sqrt(i); }

  for(i=0; i<M; i++) {
    fprintf(stderr,"i=%d b=%lf\n",i,*(b+i)); }
  fprintf(stderr,"\n");
  for(i=0; i<N; i++) {
    fprintf(stderr,"i=%d a=%lf\n",i,*(a+i)); }
  
  // do not forget to free the allocated memory
  free(a);
  return(1);
}
