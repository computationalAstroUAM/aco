//===========================================================================================
// test14
//
// the aim of this exercise is to read in a complex (tree) structure
//
// additional aims:
//  - use bsearch()
//  - get uint64_t from command line (atoi() will not work!)
//  - usage of __func__
//
//===========================================================================================
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "my.h"
#include "utility.h"

//----------------------------------------
// defines
//----------------------------------------
#define MAXSTRING 2048

//----------------------------------------
// merger tree
//----------------------------------------
typedef struct {
  uint64_t     haloid;
  uint32_t     nprog;
  uint64_t    *progid;
  
  double       whatever;
  float        you;
  float        want;
  double       to;
  uint32_t     store;
} mtreenode_t;

typedef struct {
  uint64_t     nhalos;
  mtreenode_t *node;
} mtree_t;            // mtree->node[ihalo].progid[iprog]

//----------------------------------------
// object containing haloid we search for
//----------------------------------------
typedef struct {
  uint64_t haloid;
  float    whatever;
} object_t;

//----------------------------------------
// prototypes
//----------------------------------------
mtree_t *read_mtree      (char *);
int      qcmpnodehaloids (const void *, const void *);
int      bcmphaloids     (const void *, const void *);

/*==============================================================================
 *  main
 *==============================================================================*/
int main(int argc, char **argv)
{
  char         mtreename[MAXSTRING];
  mtree_t     *mtree;                 // for multiple levels, generate an array of such pointers
  uint64_t     haloid, iprog, ihalo;
  mtreenode_t *mtreenode;
  object_t     object;
  
  // deal with command line
  if(argc != 3) {
    fprintf(stderr,"usage: %s MergerTreeFile haloid\n",argv[0]);
    return(0);
  }
  strcpy(mtreename, argv[1]);
  sscanf(argv[2], "%"SCNi64, &haloid);
  
  // hide haloid in some object
  object.haloid   = haloid;
  object.whatever = 13.5;
 
  // read tree
  mtree = read_mtree(mtreename);

  // search for a specific haloid
  fprintf(stderr,"o %s: searching for %"PRIu64" ... ", __func__, haloid);
  mtreenode = (mtreenode_t *)bsearch(&object, mtree->node, mtree->nhalos, sizeof(mtreenode_t), bcmphaloids);
  
  if(mtreenode != NULL) {
    fprintf(stderr,"found\n");
    fprintf(stderr,"o %s: halo with id=%"PRIu64" (==%"PRIu64") has %"PRIu32" progenitors\n", __func__, mtreenode->haloid, mtree->node[mtreenode-mtree->node].haloid, mtreenode->nprog);
    for(iprog=0; iprog<mtreenode->nprog; iprog++) {
      fprintf(stderr,"%"PRIu64"\n",mtreenode->progid[iprog]);
    }
    
    // let's walk the tree for the main branch of that particular haloid
    while(mtreenode->nprog > 0) {
      object.haloid = mtreenode->progid[0];
      mtreenode     = (mtreenode_t *)bsearch(&object, mtree->node, mtree->nhalos, sizeof(mtreenode_t), bcmphaloids);
      if(mtreenode != NULL) {
        fprintf(stderr,"  %"PRIu64"  %"PRIu64"\n",mtreenode->haloid, mtreenode->nprog);
      }
      else {
        break;
      }
    }
  }
  else {
    fprintf(stderr,"not found\n");
  }

  
  // free allocated memory
  for(ihalo=0; ihalo<mtree->nhalos; ihalo++) {
    free(mtree->node[ihalo].progid);
  }
  // we only have one mtree and hence no loop for free'ing the associated node
  free(mtree->node);
  free(mtree);
  
  return(1);
}


/*==============================================================================
 *  read merger tree file
 *==============================================================================*/
mtree_t *read_mtree(char *mtreename)
{
  char     line[MAXSTRING];
  FILE    *fp;
  uint64_t nhalos, ihalo, iprog, haloid, progid;
  uint32_t nprog;
  mtree_t *mtree;
  
  fprintf(stderr,"o %s: reading merger tree from file %s ... ", __func__, mtreename);

  // open file
  fp = my_fopen(mtreename,"r");

  // memory for mtree
  mtree = (mtree_t *) my_calloc(1, sizeof(mtree_t));
  
  // read version no.
  fgets(line,MAXSTRING,fp);
  
  // read header string
  fgets(line,MAXSTRING,fp);
  
  // read number of entries
  fgets(line,MAXSTRING,fp);
  sscanf(line,"%"SCNi64,&nhalos);
  
  mtree->nhalos = nhalos;
  mtree->node = (mtreenode_t *) my_calloc(nhalos, sizeof(mtreenode_t));

  // read full mtree
  for(ihalo=0; ihalo<nhalos; ihalo++) {
    
    // haloid and nprog
    fgets(line,MAXSTRING,fp);
    sscanf(line,"%"SCNi64" %"SCNi32,&haloid,&nprog);
    mtree->node[ihalo].haloid = haloid;
    mtree->node[ihalo].nprog  = nprog;
    
    // progenitor ids
    mtree->node[ihalo].progid = (uint64_t *) my_calloc(nprog, sizeof(uint64_t));
    for(iprog=0; iprog<nprog; iprog++) {
      fgets(line,MAXSTRING,fp);
      sscanf(line,"%"SCNi64,&progid);
      mtree->node[ihalo].progid[iprog] = progid;
    }
  }
  
  // check END feature of tree file
  fgets(line,MAXSTRING,fp);
  if(strncmp(line,"END",3) != 0) {
    fprintf(stderr,"%s: Could not find END in %s!?\n", __func__, mtreename);
  }
  
  // close file
  fclose(fp);
  
  // sort by haloid
  qsort((void*)mtree->node, mtree->nhalos, sizeof(mtreenode_t), qcmpnodehaloids);
  
  fprintf(stderr,"done\n");
  
  return(mtree);
}

/*==============================================================================
 *  compare nodehaloids (used with qsort)
 *==============================================================================*/
int qcmpnodehaloids(const void *node1, const void *node2)
{
  uint64_t n1, n2;
  
  n1 = ((mtreenode_t *)node1)->haloid;
  n2 = ((mtreenode_t *)node2)->haloid;
  
  return n1 < n2 ? -1 : (n1 > n2 ? 1 : 0);
}

/*==============================================================================
 *  compare haloids (used with bsearch)
 *==============================================================================*/
int bcmphaloids(const void *object, const void *node)
{
  const uint64_t haloid1 = ((object_t *) object)->haloid;
  const uint64_t haloid2 = ((mtreenode_t *)node)->haloid;
  
  return (haloid1 < haloid2 ? -1 : (haloid1>haloid2 ? 1 : 0));
  
}

