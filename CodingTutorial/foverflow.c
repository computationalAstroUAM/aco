//=====================================================================
// test02
//
// the aim of this exercise is to show how a float overflows
//
// additional aims:
//  - a bit of OMP parallelisation/environments
//  - usage of argv[] and argc
//
//
// representation of float numbers:
//
//    (-1)^S * M * 2^E
//
// where
//
//        S = bit  32               Sign
//        E = bits 31-24 (8 bits)   Exponent
//        M = bits 23-1  (23 bits)  Mantissa
//
//  reason for overflow: before addition/subtraction,
//                       the two numbers will have their
//                       exponents E synchronized
//=====================================================================
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <omp.h>

int main(int argc, char **argv)
{
  int32_t   i32, i32_end;
  float       f, g;
  int      i, nthreads, ncpus, ithread, omp_num_threads;
  
  // check what argc and argv[] contain
  fprintf(stderr,"argc=%d\n",argc);
  for(i=0; i<argc; i++) {
    fprintf(stderr,"argv[%d]=%s\n",i,argv[i]); }
  fprintf(stderr,"\n");
  
  // we need at least argc=2
  if(argc!=2) {
    fprintf(stderr,"usage: %s omp_num_threads\nAborting\n",argv[0]);
    exit(-1); }

  //--------------------------------------------------------------------------------------------
  //   OpenMP basics
  //--------------------------------------------------------------------------------------------
  // get omp_num_threads from command line
  omp_num_threads = (int) atoi(argv[1]);

  // set number of threads to be used
  omp_set_num_threads(omp_num_threads);
  
#pragma omp parallel private(nthreads, ncpus, ithread) shared(stderr) default(none)
  {
    int u; // private by construction
    
    // who am I?
    ithread = omp_get_thread_num();
    fprintf(stderr,"ithread=%d\n",ithread);
    
    /* only one thread (==0) does this */
    if (ithread == 0)
    {
      ncpus       = omp_get_num_procs();
      nthreads    = omp_get_num_threads();
      fprintf(stderr,"ncpus=%d nthreads=%d\n",ncpus,nthreads);
    }
  }
  
  //--------------------------------------------------------------------------------------------
  //   overflowing a float straight away
  //     => we cannot add +1.0 to 16777216.0, but we can add 16777216.0 !!!
  //--------------------------------------------------------------------------------------------
  fprintf(stderr,"\ndirect summation:\n");
  f = 16777216.0;
  g = f+1.0;
  fprintf(stderr,"%f+1.0       =%f\n",f,g);
  g = f+10.0;
  fprintf(stderr,"%f+10.0      =%f\n",f,g);
  g = f+16777216.0;
  fprintf(stderr,"%f+16777216.0=%f\n",f,g);
  //exit(0);
  
  //--------------------------------------------------------------------------------------------
  //   overflowing a float in a loop
  //--------------------------------------------------------------------------------------------
  f       = 0.0;
  i32     = (int32_t)0;            // otherwise we will get a compiler warning for uninitialized variable
  i32_end = ((int32_t)1<<24)+10;
  
#pragma omp parallel for private(i32) shared(stderr,i32_end) reduction(+:f) default(none) // parallelisation actually avoids the problem!!!
  for(i32=0; i32<i32_end; i32++) {  // this will overflow i32 (happens at 2^24)
    fprintf(stderr,"%"PRIi32"  %f log2(f)=%d (thread=%d)\n",i32,f,(int)log2(f),(int)omp_get_thread_num());
    f += 1.0;
  }

  // check end result
  fprintf(stderr,"\nend result:\n");
  fprintf(stderr,"%"PRIi32"  %f log2(f)=%d (thread=%d)\n",i32_end,f,(int)log2(f),(int)omp_get_thread_num());
  
  return(1);
}


