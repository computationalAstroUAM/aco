#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

float acceleration(float *, float *, int, int);

int main()
{
  float *x, *v, *m, *ank;
  float  t, dt;
  int    i, I, k, n, N;
  FILE  *fp;

  // set number of omp threads
  omp_set_num_threads(4);
  
  // choice of numerical parameters (note, do not change: they are manually tuned to give reasonable results)
  N  = 13;   // number of particles (odd number, please)
  I  = 250;  // number of integration steps
  dt = 1e-4; // time interval
  
  x   = (float *)calloc(N, sizeof(float));
  v   = (float *)calloc(N, sizeof(float));
  m   = (float *)calloc(N, sizeof(float));
  ank = (float *)calloc(N, sizeof(float));
  
  // initialisation
  for(n=0; n<N; n++) {
    x[n] = (float)n/((float)N-1.0);
    m[n] = 1.0;
  }
  // make central mass more massive to attract the rest
  n    =(int)(N/2.0+1.0)-1;
  m[n] = 1.5;
  
  // write initial configuration into a file
  fp = fopen("posI.txt","w");
  for(n=0; n<N; n++) {
    fprintf(fp,"%f 0\n",x[n]);
  }
  fclose(fp);

  // time integration
  for(i=0; i<I; i++) {
    
    // get acceleration for each particle
#pragma omp parallel for default(none) private(n,k) shared(x,m,ank,N) schedule(static)
    for(n=0; n<N; n++) {
      ank[n] = 0.0;
      for(k=0; k<N; k++) {
        if(n != k) {
          ank[n] += -1.0*((m[k]))/((x[n]-x[k])*(x[n]-x[k])) * ((x[n]-x[k])/fabs((x[n]-x[k])));
        }
      }
    }

    // get acceleration using a function call
#pragma omp parallel for default(none) private(n) shared(x,m,ank,N) schedule(static)
    for(n=0; n<N; n++) {
      ank[n] = acceleration(x,m,n,N);
    }
    
    // integrate equations-of-motion (Euler method)
#pragma omp parallel for default(none) private(n) shared(x,v,ank,dt,N) schedule(static)
    for(n=0; n<N; n++) {
      x[n] = x[n] +   v[n]*dt;
      v[n] = v[n] + ank[n]*dt;
    }

  } // for(time integration)

  // write final configuration into a file
  fp = fopen("posF.txt","w");
  for(n=0; n<N; n++) {
    fprintf(fp,"%f 0\n",x[n]);
  }
  fclose(fp);

  return(1);
}

// calculates the acceleration on particle #n coming from all other particles
float acceleration(float *x, float *m, int n, int N)
{
  int   k;
  float ank;
  
  ank = 0.0;
  for(k=0; k<N; k++) {
    if(n != k) {
      ank += -1.0*((m[k]))/((x[n]-x[k])*(x[n]-x[k])) * ((x[n]-x[k])/fabs((x[n]-x[k])));
    }
  }
  
  return(ank);
}
