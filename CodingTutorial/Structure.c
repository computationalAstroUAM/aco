//===========================================================================================
// test07
//
// the aim of this exercise is to understand the concept of a structure
//
// the exercise also shows:
//   - alignment of structures: relevant for I/O
//===========================================================================================
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "my.h"

//#define COMPENSATE_ALIGNMENT

// structure definition outside of any function
struct my_data {
  char   c;        // 1 byte
  int    i;        // 4 bytes
  double d;        // 8 bytes
                   // 13 bytes in total
};

int main(void)
{
  // declare a new varibale x that is a structure of type my_data
  struct my_data x[2], y;
   int    i;
  char   c;
#ifdef COMPENSATE_ALIGNMENT
  s1, s2, s3;
#endif
  double d;
  FILE  *fp;

  fprintf(stderr,"sizeof(struct my_data)  = %ld\n",sizeof(struct my_data));
  fprintf(stderr,"sizeof(char+int+double) = %ld\n",sizeof(char)+sizeof(int)+sizeof(double));
  
  // set (and view) values in structure
  x[0].c = 't';
  x[0].i = 15;
  x[0].d = sqrt(37.32);
  x[1].c = 'y';
  x[1].i = 10;
  x[1].d = sqrt(137.32);

  fprintf(stderr,"content of structure x:\n");
  fprintf(stderr,"%c\n", x[0].c);
  fprintf(stderr,"%d\n", x[0].i);
  fprintf(stderr,"%lf\n",x[0].d);
  fprintf(stderr,"%c\n", x[1].c);
  fprintf(stderr,"%d\n", x[1].i);
  fprintf(stderr,"%lf\n\n",x[1].d);

  
  
  // write structure to file
  //=========================
  fp = my_fopen("test.dat","wb");
  fwrite((x+1), sizeof(struct my_data), 1, fp); // only write the second structure
  fclose(fp);

//  fp = my_fopen("test.dat","wb");           // individually (might always be the better choice!)
//  fwrite(&(x[1].c), sizeof(char),   1, fp);
//  fwrite(&(x[1].i), sizeof(int),    1, fp);
//  fwrite(&(x[1].d), sizeof(double), 1, fp);
//  fclose(fp);

  
  
  
  // read structure from file
  //==========================
  fp = my_fopen("test.dat","rb");           // as a structure
  fread(&y, sizeof(struct my_data), 1, fp);
  fclose(fp);
  
  fprintf(stderr,"content of structure y:\n");
  fprintf(stderr,"%c\n", y.c);
  fprintf(stderr,"%d\n", y.i);
  fprintf(stderr,"%lf\n\n",y.d);
  
  // read content from file directly: already the first structure cannot be read...
  fprintf(stderr,"file content read directly:\n");
  fp = my_fopen("test.dat","rb");           // individually
  fread(&c, sizeof(char),   1, fp);
  fprintf(stderr,"%c\n", c);
#ifdef COMPENSATE_ALIGNMENT
  fread(&s1, sizeof(char),   1, fp);
  fread(&s2, sizeof(char),   1, fp);
  fread(&s3, sizeof(char),   1, fp);
  fprintf(stderr,"%d\n", (int)s1);
  fprintf(stderr,"%d\n", (int)s2);
  fprintf(stderr,"%d\n", (int)s3);
#endif
  fread(&i, sizeof(int),    1, fp);
  fread(&d, sizeof(double), 1, fp);
  fprintf(stderr,"%d\n", i);
  fprintf(stderr,"%lf\n",d);
  fclose(fp);
  
  return(1);
}
