// gcc -o p serial_b.c
#include <stdio.h>
#include <time.h>

void main(){
  int N = 10;
  float STARTVALUE = 2.;
  float a[N];

  double time=0.;
  clock_t begin, end;
  begin = clock();
  
  a[0] = STARTVALUE;
  
  for(int i=1; i<N; i++){
    double b = a[0];
    for(int j=0; j<i; j++){
      b = 2*b ;
    }
    a[i] = b;
  }

  for(int i=0; i<N; i++){
    printf("a[%d]=%f \n",i,a[i]);
  }

  end = clock();
  time = 1000.*(end - begin)/CLOCKS_PER_SEC; //ms
  printf("\n Time=%E ms \n",time);  
}
  
