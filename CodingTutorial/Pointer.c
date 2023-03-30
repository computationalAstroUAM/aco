//===========================================================================================
// test03
//
// the aim of this exercise is to remind about the usage of pointers
//
// the exercise also shows:
//   - functions and their prototypes
//===========================================================================================

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// prototypes
void function1(double);
void function2(double *);

//=================================================================
// main()
//=================================================================
int main(void)
{
  double a;

  a=12.5;

  function1(a);
  fprintf(stderr,"a=%g\n",a);

  function2(&a);
  fprintf(stderr,"a=%g\n",a);

  fprintf(stderr,"a=%g &a=%lu\n",a,&a);

  return(1);
}

//=================================================================
// function1()
//=================================================================
void function1(double x)
{
  x /= 2;  // x = x / 2
}

//=================================================================
// function2()
//=================================================================
void function2(double *x)
{
  *x /= 2;
}
