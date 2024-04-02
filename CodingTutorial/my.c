#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "my.h"

//==================================================================================
// my_fopen()
//==================================================================================
FILE *my_fopen(char *filename, char *mode)
{
  FILE *fp;
  
  fp = fopen(filename, mode);
  
  if(fp == NULL) {
    fprintf(stderr,"Could not open %s for mode %s\nABORTING\n",filename,mode);
    exit(-1);
  }
  
  return(fp);
}

//==================================================================================
// my_calloc()
//==================================================================================
void *my_calloc(size_t count, size_t size)
{
  void *ptr;
  
  ptr = calloc(count, size);
  
  if(ptr == NULL) {
    fprintf(stderr,"Could not calloc() count=%d size=%d\nABORTING\n",(int)count,(int)size);
    exit(-1);
  }
  
  return(ptr);
}

//==================================================================================
// my_realloc()
//==================================================================================
void *my_realloc(void *ptr, size_t size)
{
  ptr = realloc(ptr, size);
  
  if(ptr == NULL) {
    fprintf(stderr,"Could not realloc() ptr=%ld size=%d\nABORTING\n",(long)ptr,(int)size);
    exit(-1);
  }
  
  return(ptr);
}