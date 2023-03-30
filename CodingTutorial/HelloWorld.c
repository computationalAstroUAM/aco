//===========================================================================================
// test00
//
// the aim of this exercise is to demonstrate the buffering of printf()
//
// also re-direct stdout and stderr in the Terminal:
//  $./HelloWorld >& progress.txt       => none of the printf()'s will show in progress.txt!
//===========================================================================================


#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
  double *a;
  int     i;

  printf("Hello World\n");
  
  a=NULL; // this ensures to always encounter the mistake...
  
  for(i=0; i<10; i++) {
    printf("printf:  %d",i);         // printf() is buffered
    fprintf(stderr,"fprintf: %d",i); // fprintf(stderr) goes straight to stderr
    a[i]= 1.;
  }

  return(1);
}
