//===========================================================================================
// test13
//
// the aim of this exercise is to understand how to read a data file
//
// additional aims:
//  - learn a bit about string operations (strlen(), strcpy(), strcmp(), sprintf(), ...)
//  - basename() function
//  - use of realloc()
//
//===========================================================================================
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <libgen.h>

#include "my.h"
#include "utility.h"

//===========================================================================================
// defines
//===========================================================================================
#define MAXSTRING 2048

//===========================================================================================
// structures
//===========================================================================================
struct my_data {
  double r[3];
  double m;
};

//===========================================================================================
// typedefs
//===========================================================================================
typedef struct my_data halo_t;

//===========================================================================================
// prototypes
//===========================================================================================
void read_ascii1(char *, uint64_t* , halo_t **);
void read_ascii2(char *, uint64_t* , halo_t **);

//===========================================================================================
// main()
//===========================================================================================
int main(int argc, char *argv[])
{
  char *inputfile_name, *outputfile_name;
  uint64_t Nhalos, i;
  halo_t *halo; // our data will be stored and accessible like halo[i].r[] or halo[i].m
  FILE *fp;
  double rCoM[3], Mtot;

  // deal with command line
  if(argc != 2) {
    fprintf(stderr,"usage: ./IO name_of_file_to_read\nABORTING\n");
    exit(0);
  }
  
  // copy filename from argv[1] over to infile[]
  inputfile_name = (char *) my_calloc(strlen(argv[1])+MAXSTRING, sizeof(char));
  //strcpy(inputfile_name, argv[1]);
  sprintf(inputfile_name,"%s.txt",argv[1]);
  fprintf(stderr,"reading file: %s\n",inputfile_name);
  
  //=======================
  // read file into memory
  //=======================
  read_ascii1(inputfile_name, &Nhalos, &halo);
//  read_ascii2(inputfile_name, &Nhalos, &halo);
  
  //============================
  // do something with the data
  //============================
  rCoM[0] = 0.0;
  rCoM[1] = 0.0;
  rCoM[2] = 0.0;
  Mtot    = 0.0;
  for(i=0; i<Nhalos; i++) {
    rCoM[0] += halo[i].r[0]*halo[i].m;
    rCoM[1] += halo[i].r[1]*halo[i].m;
    rCoM[2] += halo[i].r[2]*halo[i].m;
    Mtot    += halo[i].m;
  }
  rCoM[0] /= Mtot;
  rCoM[1] /= Mtot;
  rCoM[2] /= Mtot;

  //=======================
  // write data to disk again
  //=======================
  // prepare fancy name for output file
  outputfile_name = (char *) my_calloc(strlen(inputfile_name)+6, sizeof(char));
  sprintf(outputfile_name,"%s.ascii",argv[1]);

  // write to output file
  fp = my_fopen(outputfile_name,"w");
  for(i=0; i<Nhalos; i++) {
    fprintf(fp,"%lf %lf %lf %lf\n",halo[i].r[0],halo[i].r[1],halo[i].r[2],halo[i].m);
  }
  fclose(fp);

  // free allocated memory
  free(inputfile_name);
  free(outputfile_name);
  free(halo);

  
}


//================================================================================
// we outsourced all of the reading to a function
//  version 1: first getting number of lines and then one calloc() call
//================================================================================
void read_ascii1(char *inputfile_name, uint64_t* Nhalos, halo_t **halo)
{
  char line[MAXSTRING];
  uint64_t i;
  FILE *fpin;
  
  fpin = my_fopen(inputfile_name,"r");
  
  fgets(line, MAXSTRING, fpin);
  *Nhalos = 0;
  while(!feof(fpin)) {
    if(strncmp(line,"#",1) != 0) {
      (*Nhalos)++;
    }
    fgets(line, MAXSTRING, fpin);
  }
  fprintf(stderr,"  found %"PRIu64" halos in file %s\n",*Nhalos,inputfile_name);

  // go back to the start of the file
  rewind(fpin);
  
  // allocate memory for our array of structures
  *halo = (halo_t *) my_calloc(*Nhalos, sizeof(halo_t));
  
  // now actually read the data into our structure
  fgets(line, MAXSTRING, fpin);
  i = 0;
  while(!feof(fpin)) {
    if(strncmp(line,"#",1) != 0) {
      sscanf(line,"%lf %lf %lf %lf", &((*halo)[i].r[0]), &((*halo)[i].r[1]), &((*halo)[i].r[2]), &((*halo)[i].m));
      i++;
    }
    
    fgets(line, MAXSTRING, fpin);
  }
  
  fclose(fpin);
}

//================================================================================
// we outsourced all of the reading to a function
//  version 2: realloc()'ing while reading
//================================================================================
void read_ascii2(char *inputfile_name, uint64_t* Nhalos, halo_t **halo)
{
  char line[MAXSTRING];
  uint64_t i;
  FILE *fpin;
  
  fpin = my_fopen(inputfile_name,"r");
  
  fgets(line, MAXSTRING, fpin);
  *Nhalos = 0;
  *halo   = NULL;
  while(!feof(fpin)) {
    if(strncmp(line,"#",1) != 0) {
      (*Nhalos)++;
      *halo = (halo_t *) my_realloc(*halo, (*Nhalos)*sizeof(halo_t));
      sscanf(line,"%lf %lf %lf %lf", &((*halo)[(*Nhalos)-1].r[0]), &((*halo)[(*Nhalos)-1].r[1]), &((*halo)[(*Nhalos)-1].r[2]), &((*halo)[(*Nhalos)-1].m));
    }
    fgets(line, MAXSTRING, fpin);
  }
  fprintf(stderr,"  found %"PRIu64" halos in file %s\n",*Nhalos,inputfile_name);
  
  fclose(fpin);
}

