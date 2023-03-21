#include <stdio.h>
#include <stdlib.h> //Includes the rand() library
#include <time.h>

void main(){
  int i=0, j=0;
  double time=0.;
  clock_t begin, end;
  
  double density[2][3] = {{0.}};

  // Populate the array with random numbers from 0 to 99 with rand()%100

  begin = clock();
  // In the 'bad' way
  for(i=0 ; i<3 ;i++){
    for (j=0; j<2; j++){
       density[j][i]=rand()%100;  
    }
  }
  end = clock();
  time = 1000.*(end - begin)/CLOCKS_PER_SEC; 
  printf("Time 'bad' way=%E ms \n",time);
  
  begin = clock();
  // In the 'good' way
  for(i=0 ; i<3 ;i++){
    for (j=0; j<2; j++){
       density[j][i]=rand()%100;   
    }
  }
  end = clock();
  time = 1000.*(end - begin)/CLOCKS_PER_SEC; 
  printf("Time 'good' way=%E ms \n",time);
}
