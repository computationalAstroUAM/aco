//===========================================================================================
// test08
//
// the aim of this exercise is to understand the concept of structure arrays
//
// the exercise also shows:
//   - typedef
//   - passing of structure pointer to function
//===========================================================================================
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "utility.h"   // needed for ran3()
#include "my.h"

// structure definition outside of any function
struct my_data {
  float m;
  float x[3];
  float v[3];
};

// shortcut for structure declaration
typedef struct my_data particle_t;  // typedef (WHAT_YOU_WANT_TO_AVOID) (SHORTCUT)

// prototypes
int functionx(particle_t *); // more details about structure pointers in "test09"

//==========================================================
// main
//==========================================================
int main(int argc, char **argv)
{
  // use typedef to declare P
  particle_t *P;
  particle_t  u; //={0,0,0,0,0,0,0}; // this is how we could fill a structure, too
  int         i=0, N;
  long    iseed;
  
  // deal with command line
  if(argc != 2) {
    fprintf(stderr,"usage: %s N\n",argv[0]);
    exit(-1);
  }
  N = atoi(argv[1]);
  
  // array of structures
  P = (particle_t *) my_calloc(N, sizeof(particle_t));

  //===========================================
  // using standard operator '.'
  //===========================================
  iseed=-123456;
  for(i=0; i<N; i++) { // can this loop be parallelized?
    P[i].m    = ran3(&iseed);
    P[i].x[0] = (float)i;
    P[i].x[1] = (float)(2*i);
    P[i].x[2] = (float)(4*i);
    P[i].v[0] = (float)sqrt((double)i);
    P[i].v[1] = (float)sqrt((double)i);
    P[i].v[2] = (float)sqrt((double)i);
  }
  for(i=0; i<N; i++) {
    fprintf(stderr,"%f %f %f\n",P[i].m,P[i].x[0],P[i].v[0]);
  }
  fprintf(stderr,"\n");
  
  //===========================================
  // using special operator '->' with structure pointer
  //===========================================
  iseed=-123456;
  for(i=0; i<N; i++) {
    (P+i)->m    = ran3(&iseed);
    (P+i)->x[0] = (float)i;
    (P+i)->x[1] = (float)(2*i);
    (P+i)->x[2] = (float)(4*i);
    (P+i)->v[0] = (float)sqrt((double)i);
    (P+i)->v[1] = (float)sqrt((double)i);
    (P+i)->v[2] = (float)sqrt((double)i);
  }
  for(i=0; i<N; i++) {
    fprintf(stderr,"%f %f %f\n",P[i].m,P[i].x[0],P[i].v[0]);
  }
  fprintf(stderr,"\n");
  
  //===========================================
  // let a function fill the values for us...
  //===========================================
#pragma omp parallel for default(none) private(i) shared(N,P) schedule(dynamic)
  for(i=0; i<N; i++) {
    functionx(P+i);
  }





  
  for(i=0; i<N; i++) {
    fprintf(stderr,"%f %f %f\n",P[i].m,P[i].x[0],P[i].v[0]);
  }
  
  // do not forget to free the allocated memory
  free(P);

  return(1);
}

//==========================================================
// function
//==========================================================
int functionx(particle_t *s)
{
  s->x[0]   = (float)(1);
  s->x[1]   = (float)(2);
  s->x[2]   = (float)(4);
  s->v[0]   = (float)sqrt((double)5);
  s->v[1]   = (float)sqrt((double)7);
  s->v[2]   = (float)sqrt((double)9);

  fprintf(stderr,"%s: %f\n",__func__,s->x[1]);
  
  return(1);
}
