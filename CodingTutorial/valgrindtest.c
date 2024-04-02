//=======================================================================
// test15
//
// the aim of this exercise is to understand how to use valgrind to find memory leaks
//
// - your own source code needs to be compiled with -g
// - run code under valgrind:
//     valgrind --leak-check=full --track-origins=yes  --dsymutil=yes  ./code
//
//     -> search (cryptic) output for 'definitely lost', 'Invalid read', 'Invalid write'
//
// download valgrind from here: http://valgrind.org
// configure using the following options:
// ./configure --prefix=/Where/You/Want/The/Installation --enable-only64bit
//
// Note that valgrind is already installed systemwide on castor.ft.uam.es
// to which ACO students have access via the practicas account...
//
//=======================================================================

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utility.h"

// structure definition outside of any function
typedef struct my_data {
  float m;
  float *x;
  float *v;
} particle_t;

#define NPART 7
#define NDIM  3

int main(void)
{
  // use typedef to declare P
  particle_t *P;
  int i, j;
  long iseed=-123456;

  // array of structures
  P = (particle_t *) calloc(NPART, sizeof(particle_t));

  // using standard operator '.'
  for(i=0; i<NPART; i++) {
    P[i].m    = ran3(&iseed);
    
    P[i].x    = (float *) calloc(NDIM, sizeof(float));
    P[i].v    = (float *) calloc(NDIM, sizeof(float));

    for(j=0; j<NDIM; j++) {
      P[i].x[j] = (float)i/((float)(j+1));
      P[i].v[j] = (float)sqrt((double)j)*(float)i;
    }
  }
  
  for(i=0; i<NPART; i++) {
    fprintf(stderr,"%f %f %f\n",P[i].m,P[i].x[0],P[i].v[0]);
  }
  fprintf(stderr,"\n");

  // we need to free everything that has been alloc'ed
  for(i=0; i<NPART; i++) {
    free(P[i].x);
    free(P[i].v);
  }
  free(P);
  
  
  return(1);
}
