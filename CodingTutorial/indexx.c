//===========================================================================================
// test11
//
// the aim of this exercise is to understand how to use indexx()
//===========================================================================================

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "utility.h"
#include "my.h"

// prototypes
int qsortcmpdouble(const void*, const void*);

int main(int argc, char **argv)
{
  long    N, i, iseed;
  double *x;
  long   *idx;
  
  if (argc != 3) {
    fprintf(stderr,"usage: ./indexx N iseed\nABORTING\n");
    exit(0);
  }
  
  N     = (long) atoi(argv[1]);
  iseed = (long) atoi(argv[2]);
  
  x = (double *) my_calloc(N, sizeof(double));
  
  for(i=0; i<N; i++) {
    x[i] = ran3(&iseed);
    //fprintf(stderr,"%ld %lf\n",i,x[i]);
  }
  
  //====================================
  // indexx sorting
  //====================================
  idx = (long *) my_calloc(N, sizeof(long));
  
  indexx(N, x-1, idx-1);  // indexx() sorts in ascending order

  // to not forget that idx[] stores the indices [1,N] you could have a loop correcting the values...
  for(i=0; i<N; i++) {
    idx[i] = idx[i]-1;
  }
  
  for(i=0; i<N; i++) {
    fprintf(stderr,"%ld %lf\n", i, x[idx[i]]);
  }

  // this is how you could access x[] in reverse order
  for(i=0; i<N; i++) {
    fprintf(stderr,"%ld %lf\n", i, x[idx[(N-1)-i]]);
  }
  free(idx);
  
  //====================================
  // inplace sorting
  //====================================
  qsort((void *)x+2, N-1, sizeof(double), qsortcmpdouble);
  
  fprintf(stderr,"\n");
  for(i=0; i<N; i++) {
    fprintf(stderr,"%ld %lf\n", i, x[i]);
  }

  free(x);
  
  return(1);
}

int qsortcmpdouble(const void *p1, const void *p2)
{
  double x1, x2;
  
  x1 = *((double *)p1);
  x2 = *((double *)p2);
  
  if (x1>x2)
    return(1);
  else if (x2>x1)
    return(-1);
  else
    return(0);

}

