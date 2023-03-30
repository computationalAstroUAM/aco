//====================================================================================================
// test09
//
// the aim of this exercise is to understand how to pass pointers to structures around with functions
//====================================================================================================
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include "my.h"

//==========================================================
// defines
//==========================================================
#define Nstruct 10

//==========================================================
// the structure
//==========================================================
struct my_data {
  double   x;
  double   y;
  double   z;
  double   u;
  double   p;
  double   w;
  double   d[10];
  int32_t  n;     // stores length of i[]
  int32_t *i;     // pointer! -> will be used to allocate a dynamic array inside the structure
};
typedef struct my_data mydata_t;

//==========================================================
// prototypes
//==========================================================
void         my_structure_modifier  (double, double, mydata_t*);    // returns nothing
mydata_t    *my_structure_allocator (int32_t);                      // returns pointer to my_data structure

//==========================================================
// main
//==========================================================
int main(void)
{
  int32_t   i, j;
  double    x, y;
  mydata_t *struct_with_my_stuff;

  // work with structures: a) creation
  struct_with_my_stuff = my_structure_allocator(Nstruct);
  
  // work with structures: b) initialisation/modification of content
#pragma omp parallel for default(none) private(i,x,y) shared(struct_with_my_stuff)
  for(i=0; i<Nstruct; i++) {
    x = 12.*i;
    y = i/15.;
    my_structure_modifier(x, y, &(struct_with_my_stuff[i]));   // note that we only pass a pointer to element [i]: the function does not know that it comes from an array!
  }

  // check structure content
  for(i=0; i<Nstruct; i++) {
    fprintf(stderr,"%lf %lf\n", struct_with_my_stuff[i].x, struct_with_my_stuff[i].y);
    for(j=0; j<struct_with_my_stuff[i].n; j++) {
      fprintf(stderr,"  %"PRIi32" ", struct_with_my_stuff[i].i[j]);
    }
    fprintf(stderr,"\n");
  }

  
  // do not forget to free the allocated memory
  for(i=0; i<Nstruct; i++) {
    if(struct_with_my_stuff[i].i != NULL)  // we need to possible free the memory the pointer points to!
      free(struct_with_my_stuff[i].i);
  }
  free(struct_with_my_stuff);

  return(1);
}

//==========================================================
// my_structure_modifier
//==========================================================
void my_structure_modifier(double a, double b, mydata_t *c)
{
  int32_t i, n;
  
  c->x = a+b;
  c->y = a*b;
  
  n = c->n;
  for(i=0; i<n; i++) {
    c->i[i] = i;
  }
}

//==========================================================
// my_structure_allocator
//==========================================================
mydata_t *my_structure_allocator(int32_t n)
{
  mydata_t *c;
  int32_t   i, j;

  c = (mydata_t *) my_calloc(n, sizeof(mydata_t));

  for(i=0; i<n; i++) {
    c[i].n = i+1;
    c[i].i = (int32_t *) my_calloc((i+1), sizeof(int32_t));
  }

  return(c);
}
