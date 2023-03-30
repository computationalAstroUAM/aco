#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

#define INFTY ((uint64_t)1<<30)

int main(int argc, char **argv)
{
  uint64_t k;
  double pi;
  time_t tstart, tend;
  int    nthreads_to_be_used;

  if(argc != 2) {
    fprintf(stderr,"usage: ./pi NTHREADS\nABORTING\n");
  }
  
  nthreads_to_be_used = atoi(argv[1]);
  fprintf(stderr,"using %d threads for execution\n",nthreads_to_be_used);
  omp_set_num_threads(nthreads_to_be_used);

#pragma omp parallel shared(stderr) default(none)
  {
    // all private by construction
    int nthreads, ncpus, ithread, omp_num_threads;
    
    // who am I?
    ithread = omp_get_thread_num();
    
    /* only one thread (==0) does this */
    if (ithread == 0)
    {
      ncpus       = omp_get_num_procs();
      nthreads    = omp_get_num_threads();
      fprintf(stderr,"ncpus=%d nthreads=%d\n",ncpus,nthreads);
    }
  }

  pi = 0.0;

  tstart = time(NULL);
#pragma omp parallel for default(none) private(k) reduction(+:pi) schedule(static)
  for(k=0; k<INFTY; k++) {
    pi += pow(-1.0/3.0, (double)k) / (2.*(double)k+1.);
  }
  tend = time(NULL);
  
  pi *= sqrt(12);
  fprintf(stderr,"pi = %16.12lf (time=%3.1lf [sec])\n",pi,difftime(tend,tstart));
}




