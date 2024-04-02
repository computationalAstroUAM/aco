//===========================================================================================
// test10
//
// the aim of this exercise is to understand how to use (arrays of) pointers to functions
//===========================================================================================

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "my.h"

// prototypes
double multiply   (double, double);
double add        (double, double);
double subtract   (double, double);
double calculate  (double(*func)(double, double), double, double);

#define NFUNC 3

//=================================================================
// main()
//=================================================================
int main()
{
  double x,y,z;
  int    i;

  // dynamic function array
  double (**func)(double,double);
  func = (double (**)(double,double))my_calloc(NFUNC, sizeof(*func));  // we will use 3 different functions...

  x = 15.8;
  y = 12.75;

  // using function pointers straight away
  z = calculate(add, x, y);
  fprintf(stderr,"%lf + %lf = %lf\n",x,y,z);

  z = calculate(multiply, x, y);
  fprintf(stderr,"%lf * %lf = %lf\n",x,y,z);
  
  z = calculate(subtract, x, y);
  fprintf(stderr,"%lf - %lf = %lf\n\n",x,y,z);
  
  // using an array of function pointers
  func[0] = add;   // yes, you can simply use the name here!
  func[1] = multiply;
  func[2] = subtract;

#pragma omp parallel for private(i,z) shared(func,x,y,stderr) schedule(dynamic) default(none)
  for(i=0; i<NFUNC; i++) {
    z = calculate(func[i], x, y);
    fprintf(stderr,"x=%lf, y=%lf, z=%lf (thread=%d)\n",x,y,z,omp_get_thread_num());
  }

  return(1);
}

//=================================================================
// calculate()
//=================================================================
double calculate(double(*func)(double,double), double x, double y)
{
  double c;

  c = (*func)(x,y);

  return(c);
}

//=================================================================
// multiply()
//=================================================================
double multiply(double x, double y)
{
  // multiply x and y
  return(x*y);
}

//=================================================================
// add()
//=================================================================
double add(double x, double y)
{
  // add x and y
  return(x+y);
}

//=================================================================
// subtract()
//=================================================================
double subtract(double x, double y)
{
  // subtract x and y
  return(x-y);
}
