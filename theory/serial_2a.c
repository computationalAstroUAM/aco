// gcc -o p  serial_2a.c
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
    a[i] = 2*a[i-1];
  }
  
  printf("\n Results:\n");  
  for(int i=0; i<N; i++){
    printf("a[%d]=%.1f \n",i,a[i]);
  }

  end = clock();
  time = 1000.*(end - begin)/CLOCKS_PER_SEC; //ms
  printf("\n Time=%E ms \n",time);
  
}
  
