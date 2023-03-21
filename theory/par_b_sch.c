// gcc -o p -fopenmp par_b_sch.c
#include <stdio.h>
#include <omp.h>

float calc_b(int i, float a0){
    float b = a0;
    for(int j=0; j<i; j++){
      b = 2*b ;
    }
    return b;
}

void main(){
  int N = 10;
  float STARTVALUE = 2.;
  float a[N];

  a[0] = STARTVALUE;

  double start = omp_get_wtime();
  omp_set_num_threads(3); int chunk=3;
  int i,j;
  float b;
#pragma omp parallel private(i,j) shared(a,b) 
  {
    int ID = omp_get_thread_num();

    # pragma omp for schedule(dynamic)
    //# pragma omp for schedule(static,chunk)
    for(int i=1; i<N; i++){
      a[i] = calc_b(i,a[0]);
      printf("Thread %d: a[%d]=%.1f \n",ID,i,a[i]);
    }
  } // end of parallel section

  printf("\n Results:\n");
  for(int i=0; i<N; i++){
    printf("a[%d]=%.1f \n",i,a[i]);
  }

  double time = 1000.*(omp_get_wtime() - start); //ms
  printf("\n Time=%E ms \n",time); 
}
  
