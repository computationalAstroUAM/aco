//===========================================================================================
// test12
//
// the aim of this exercise is to understand how to use stdlib's qsort()
//
// additional aims:
//  - how to get int64_t from the command line
//
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

// structures
struct my_struct {
  int32_t   i;
  float     m;
  float     r[3];
  float     v[3];
};

// typedefs
typedef struct my_struct particle_t;

// prototypes
int compar_P_by_mass(const void *, const void *);
float give_me_the_mass(const void *);

//==========================================================
// main
//==========================================================
int main(int argc, char **argv)
{
  long        iseed;
  int64_t     N, i;
  particle_t *P;
  
  // deal with command line
  if(argc != 3) {
    fprintf(stderr,"usage:   %s N iseed\nAborting\n",argv[0]);
    exit(-1);
  }
  // this will break as soon as argv[1] stores an integer larger than 32-bits!
  //N     = (int64_t) atoi(argv[1]);
  //iseed = (int64_t) atoi(argv[2]);
  
  sscanf(argv[1],"%"SCNi64,&N);
  sscanf(argv[2],"%"SCNi64,&iseed);
  

  // create array of N particles
  P = (particle_t *) my_calloc(N, sizeof(particle_t));
  
  // fill structure with something
  for(i=0; i<N; i++) {
    P[i].m = pow(10., 10.0 + ran3(&iseed)*5.0); // random masses between [1e10,1e15]
    // leave the rest of P[] at zero as we do not care about it
  }
  
  // sort P[] by P[].m
  qsort(P, N, sizeof(particle_t), compar_P_by_mass);
  
  // this is also possible: (make sure N is large enough)
  //qsort(P+5, N-10, sizeof(particle_t), compar_P_by_mass);
  
  
  for(i=0; i<N; i++) {
    fprintf(stderr,"%"PRIi64" %g\n",i,P[i].m);
  }

  // do not forget to free allocated memory
  free(P);
  
  return(1);
}


//==========================================================
// compar_P_by_mass
//==========================================================
int compar_P_by_mass(const void *p1, const void *p2)
{
  float m1, m2;
  
  m1 = give_me_the_mass(p1);
  m2 = give_me_the_mass(p2);
  
  if(m1 > m2) {
    return(-1);
  }
  else if(m2 > m1) {
    return(1);
  }
  else {
    return(0);
  }
}

float give_me_the_mass(const void *p)
{
  float m;
  
  //m = (*((particle_t *)p)).m;
  m = ((particle_t *)p)->m;
  
  return(m);
}
