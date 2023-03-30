//==================================================================
// galaxyGC
//
// the aim of this exercise is to show how to work with nested structure arrays 
//
//==================================================================
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>

#include "utility.h"
#include "my.h"

//--------------------------------------------------------------
// TYPEDEFS OF STRUCTURES
//--------------------------------------------------------------
struct my_globular_cluster {
  float x,y,z;
  double m;
};
typedef struct my_globular_cluster gc_t;

struct my_galaxy {
  float x,y,z;
  double m;
  double d[15];
  int   nGC;
  gc_t  *GC;
};
typedef struct my_galaxy galaxy_t;

//--------------------------------------------------------------
// allocate memory for galaxy structure (incl. memory for GCs)
//--------------------------------------------------------------
galaxy_t* allocate_memory_for_galaxies(long N)
{
  galaxy_t *G;
  long i, j;
  int  nGC;
  long iseed=-123456;

  G = (galaxy_t *)calloc(N, sizeof(galaxy_t));

  for(i=0; i<N; i++) {
    nGC = (int)(ran3(&iseed)*10.0);

    G[i].GC = (gc_t *)calloc(nGC, sizeof(gc_t));
    G[i].nGC = nGC;
    
    for(j=0; j<nGC; j++) {
      G[i].GC[j].m = ran3(&iseed);
    }
    
  }

  return(G);
}

//--------------------------------------------------------------
// MAIN
//--------------------------------------------------------------
void main()
{

  long N=10,i,j;
  galaxy_t *G;

  G = allocate_memory_for_galaxies(N);
  
  for(i=0; i<N; i++) {
    fprintf(stderr,"%ld\n",G[i].nGC);
    for(j=0; j<G[i].nGC; j++) {
      fprintf(stderr,"galaxy %ld , GC %ld, mGC=%lf\n",i,j, G[i].GC[j].m );
    }
  }

  for(i=0; i<N; i++) {
    free(G[i].GC);
  }
  free(G);
  
}
