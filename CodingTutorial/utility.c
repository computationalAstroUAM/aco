/*==============================================================================
 *    NR routines along with own adaptive 5th order Runge-Kutta INTEGRATE
 *==============================================================================*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utility.h"


/*
 Read a string of n characters
 */
int ReadString(FILE *fptr,char *s,int n)
{
  int i,c;
  
  if(sizeof(char) != 1)
   {
    fprintf(stderr,"ReadString: sizeof(char)=%ld and not 1\n",sizeof(char));
    exit(0);
   }
  
  s[0] = '\0';
  for (i=0;i<n;i++) {
    c = fgetc(fptr);
    if (c == EOF)
      return(FALSE);
    s[i] = c;
    s[i+1] = '\0';
  }
  return(TRUE);
}

/*
 Read an array of n characters
 NOTE: the difference to ReadString() is that we do not '\0'-terminate the array
 */
int ReadChars(FILE *fptr,char *s,int n)
{
  int i,c;
  
  if(sizeof(char) != 1)
   {
    fprintf(stderr,"ReadChars: sizeof(char)=%ld and not 1\n",sizeof(char));
    exit(0);
   }
  
  s[0] = '\0';
  for (i=0;i<n;i++) {
    c = fgetc(fptr);
    if (c == EOF)
      return(FALSE);
    s[i] = c;
  }
  return(TRUE);
}

/*
 Read a possibly byte swapped integer
 */
int ReadInt(FILE *fptr,int *n,int swap)
{
  unsigned char *cptr,tmp;
  
  if(sizeof(int) != 4)
   {
    fprintf(stderr,"ReadInt: sizeof(int)=%ld and not 4\n",sizeof(int));
    exit(0);
   }
  
  if (fread(n,4,1,fptr) != 1)
    return(FALSE);
  if (swap) {
    cptr = (unsigned char *)n;
    tmp     = cptr[0];
    cptr[0] = cptr[3];
    cptr[3] = tmp;
    tmp     = cptr[1];
    cptr[1] = cptr[2];
    cptr[2] = tmp;
  }
  return(TRUE);
}

/*
 Read a possibly byte swapped unsigned integer
 */
int ReadUInt(FILE *fptr,unsigned int *n,int swap)
{
  unsigned char *cptr,tmp;
  
  if(sizeof(int) != 4)
   {
    fprintf(stderr,"ReadUInt: sizeof(int)=%ld and not 4\n",sizeof(int));
    exit(0);
   }
  
  if (fread(n,4,1,fptr) != 1)
    return(FALSE);
  if (swap) {
    cptr = (unsigned char *)n;
    tmp     = cptr[0];
    cptr[0] = cptr[3];
    cptr[3] = tmp;
    tmp     = cptr[1];
    cptr[1] = cptr[2];
    cptr[2] = tmp;
  }
  return(TRUE);
}

/*
 Read a possibly byte swapped long integer
 */
int ReadLong(FILE *fptr,long *n,int swap)
{
  unsigned char *cptr,tmp;
  
  if(sizeof(long) == 4)
   {
    if (fread(n,4,1,fptr) != 1)
      return(FALSE);
    if (swap) {
      cptr = (unsigned char *)n;
      tmp     = cptr[0];
      cptr[0] = cptr[3];
      cptr[3] = tmp;
      tmp     = cptr[1];
      cptr[1] = cptr[2];
      cptr[2] = tmp;
    }
   }
  else if(sizeof(long) == 8)
   {
    if (fread(n,8,1,fptr) != 1)
      return(FALSE);
    if (swap) {
      cptr = (unsigned char *)n;
      tmp     = cptr[0];
      cptr[0] = cptr[7];
      cptr[7] = tmp;
      tmp     = cptr[1];
      cptr[1] = cptr[6];
      cptr[6] = tmp;
      tmp     = cptr[2];
      cptr[2] = cptr[5];
      cptr[5] = tmp;
      tmp     = cptr[3];
      cptr[3] = cptr[4];
      cptr[4] = tmp;
    }
   }
  else
   {
    fprintf(stderr,"ReadLong: something wrong...cannot read long\n");
    exit(0);
   }
  
  
  
  return(TRUE);
}

/*
 Read a possibly byte swapped long long integer
 */
int ReadLongLong(FILE *fptr,long long *n,int swap)
{
  unsigned char *cptr,tmp;
  
  if (fread(n,8,1,fptr) != 1)
    return(FALSE);
  if (swap) {
    cptr = (unsigned char *)n;
    tmp     = cptr[0];
    cptr[0] = cptr[7];
    cptr[7] = tmp;
    tmp     = cptr[1];
    cptr[1] = cptr[6];
    cptr[6] = tmp;
    tmp     = cptr[2];
    cptr[2] = cptr[5];
    cptr[5] = tmp;
    tmp     = cptr[3];
    cptr[3] = cptr[4];
    cptr[4] = tmp;
  }
  return(TRUE);
}

/*
 Read a possibly byte swapped double precision number
 Assume IEEE
 */
int ReadDouble(FILE *fptr,double *n,int swap)
{
  unsigned char *cptr,tmp;
  
  if(sizeof(double) != 8)
   {
    fprintf(stderr,"ReadDouble: sizeof(double)=%ld and not 8\n",sizeof(double));
    exit(0);
   }
  
  if (fread(n,8,1,fptr) != 1)
    return(FALSE);
  if (swap) {
    cptr = (unsigned char *)n;
    tmp     = cptr[0];
    cptr[0] = cptr[7];
    cptr[7] = tmp;
    tmp     = cptr[1];
    cptr[1] = cptr[6];
    cptr[6] = tmp;
    tmp     = cptr[2];
    cptr[2] = cptr[5];
    cptr[5] = tmp;
    tmp     = cptr[3];
    cptr[3] = cptr[4];
    cptr[4] = tmp;
  }
  
  return(TRUE);
}

/*
 Read a possibly byte swapped floating point number
 Assume IEEE format
 */
int ReadFloat(FILE *fptr,float *n, int swap)
{
  unsigned char *cptr,tmp;
  
  if(sizeof(float) != 4)
   {
    fprintf(stderr,"ReadFloat: sizeof(float)=%ld and not 4\n",sizeof(float));
    exit(0);
   }
  
  if (fread(n,4,1,fptr) != 1)
    return(FALSE);
  if (swap) 
   {
    cptr = (unsigned char *)n;
    tmp     = cptr[0];
    cptr[0] = cptr[3];
    cptr[3] = tmp;
    tmp     = cptr[1];
    cptr[1] = cptr[2];
    cptr[2] = tmp;
   }
  return(TRUE);
}


/* Routine to locate mass in Mtable */
void locate(double xx[], int n, double x, int *j) 
{
  int ju, jm, jl;
  
  jl = 0;
  ju = n-1;
  while(ju-jl > 1)
   {
    jm = (ju + jl)>>1;
    if(x >= xx[jm])
      jl = jm;
    else
      ju = jm;
   }
  if (x < xx[0]) *j = 1;
  else if(x > xx[n-1]) *j = n - 1;
  else *j = jl;
}


/* Function to give random numbers */
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

float ran3(long *idum)
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;
  
	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
    inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
/* (C) Copr. 1986-92 Numerical Recipes Software ,2kB. */

#include <math.h>

void polint(float xa[], float ya[], int n, float x,
            float *y, float *dy)
{
  int i, m, ns=1;
  float den, dif, dift, ho, hp, w;
  float *c, *d;
  
  dif = fabs(x-xa[1]);
  c = vector(1,n);
  d = vector(1,n);
  
  for(i=1; i<n; i++)
   {
    if((dift=fabs(x-xa[i])) < dif)
     {
      ns = i;
      dif = dift;
     }
    c[i] = ya[i];
    d[i] = ya[i];
   }
  
  *y = ya[ns--];
  for(m=1; m<n; m++)
   {
    for(i=1; i<=n-m; i++)
     {
      ho = xa[i] - x;
      hp = xa[i+m] - x;
      w = c[i+1] - d[i];
      if((den=ho-hp) == 0.0) 
        nrerror("Error in routine polint");
      den = w / den;
      d[i] = hp * den;
      c[i] = ho * den;
     }
    *y += (*dy = (2 * ns < (n-m) ? c[ns+1] : d[ns--]));
   }
  free_vector(d,1,n);
  free_vector(c,1,n);
}

/* CAUTION: This is the ANSI C (only) version of the Numerical Recipes
 utility file nrutil.c.  Do not confuse this file with the same-named
 file nrutil.c that is supplied in the same subdirectory or archive
 as the header file nrutil.h.  *That* file contains both ANSI and
 traditional K&R versions, along with #ifdef macros to select the
 correct version.  *This* file contains only ANSI C.               */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
	float *v;
  
	v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
	if (!v) nrerror("allocation failure in vector()");
	return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;
  
	v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl+NR_END;
}

unsigned char *cvector(long nl, long nh)
/* allocate an unsigned char vector with subscript range v[nl..nh] */
{
	unsigned char *v;
  
	v=(unsigned char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(unsigned char)));
	if (!v) nrerror("allocation failure in cvector()");
	return v-nl+NR_END;
}

unsigned long *lvector(long nl, long nh)
/* allocate an unsigned long vector with subscript range v[nl..nh] */
{
	unsigned long *v;
  
	v=(unsigned long *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(long)));
	if (!v) nrerror("allocation failure in lvector()");
	return v-nl+NR_END;
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;
  
	v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl+NR_END;
}

float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;
  
	/* allocate pointers to rows */
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
  
	/* allocate rows and set pointers to them */
	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
  
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
  
	/* return pointer to array of pointers to rows */
	return m;
}

double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;
  
	/* allocate pointers to rows */
	m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
  
	/* allocate rows and set pointers to them */
	m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
  
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
  
	/* return pointer to array of pointers to rows */
	return m;
}

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;
  
	/* allocate pointers to rows */
	m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
  
  
	/* allocate rows and set pointers to them */
	m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
  
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
  
	/* return pointer to array of pointers to rows */
	return m;
}

float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch,
                  long newrl, long newcl)
/* point a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
{
	long i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;
	float **m;
  
	/* allocate array of pointers to rows */
	m=(float **) malloc((size_t) ((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure in submatrix()");
	m += NR_END;
	m -= newrl;
  
	/* set pointers to rows */
	for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+ncol;
  
	/* return pointer to array of pointers to rows */
	return m;
}

float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix m[nrl..nrh][ncl..nch] that points to the matrix
 declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
 and ncol=nch-ncl+1. The routine should be called with the address
 &a[0][0] as the first argument. */
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;
  
	/* allocate pointers to rows */
	m=(float **) malloc((size_t) ((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure in convert_matrix()");
	m += NR_END;
	m -= nrl;
  
	/* set pointers to rows */
	m[nrl]=a-ncl;
	for(i=1,j=nrl+1;i<nrow;i++,j++) m[j]=m[j-1]+ncol;
	/* return pointer to array of pointers to rows */
	return m;
}

float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
/* allocate a float 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
	float ***t;
  
	/* allocate pointers to pointers to rows */
	t=(float ***) malloc((size_t)((nrow+NR_END)*sizeof(float**)));
	if (!t) nrerror("allocation failure 1 in f3tensor()");
	t += NR_END;
	t -= nrl;
  
	/* allocate pointers to rows and set pointers to them */
	t[nrl]=(float **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float*)));
	if (!t[nrl]) nrerror("allocation failure 2 in f3tensor()");
	t[nrl] += NR_END;
	t[nrl] -= ncl;
  
	/* allocate rows and set pointers to them */
	t[nrl][ncl]=(float *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(float)));
	if (!t[nrl][ncl]) nrerror("allocation failure 3 in f3tensor()");
	t[nrl][ncl] += NR_END;
	t[nrl][ncl] -= ndl;
  
	for(j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
	for(i=nrl+1;i<=nrh;i++) {
		t[i]=t[i-1]+ncol;
		t[i][ncl]=t[i-1][ncl]+ncol*ndep;
		for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
	}
  
	/* return pointer to array of pointers to rows */
	return t;
}

void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_cvector(unsigned char *v, long nl, long nh)
/* free an unsigned char vector allocated with cvector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_lvector(unsigned long *v, long nl, long nh)
/* free an unsigned long vector allocated with lvector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_matrix(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by imatrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch)
/* free a submatrix allocated by submatrix() */
{
	free((FREE_ARG) (b+nrl-NR_END));
}

void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch)
/* free a matrix allocated by convert_matrix() */
{
	free((FREE_ARG) (b+nrl-NR_END));
}

void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,
                   long ndl, long ndh)
/* free a float f3tensor allocated by f3tensor() */
{
	free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
	free((FREE_ARG) (t[nrl]+ncl-NR_END));
	free((FREE_ARG) (t+nrl-NR_END));
}
/* (C) Copr. 1986-92 Numerical Recipes Software ,2kB. */

void   RUNGE5VAR (double *y, double dydx, double *x, double htry, double eps, 
                  double yscale, double *dxnext, double (*func)(double));
void   RUNGE     (double y, double dydx, double x, double h,double(*func)(double),
                  double *yout, double *yerr);

/*===============================================================================
 * INTEGRATE:  integrates a supplied function func(x) from a to b accurately !
 *===============================================================================*/
double INTEGRATE (double (*func)(double), double a, double b, double step,
                  double eps)
{
  double x, dx, y, dydx, yscale, dxnext;
  int    Nstep;
  
  
  x     = a;
  dx    = step;
  y     = (double)0.0;
  Nstep = 0;
  
  while( ((x-b)*(b-a) < (double)0.0) && (Nstep < MAXSTEPS))
   {
    Nstep  = Nstep + 1;
    dydx   = FUNC(x);
    yscale = MAX(fabs(y) + fabs(dx*dydx), (double)1.e-8);
    
    if ((x+dx-b)*(x+dx-a) > (double)0.0)
     {
      dx = b - x;
     }
    
    RUNGE5VAR(&y,dydx,&x,dx,eps,yscale,&dxnext,func);
    
    dx = dxnext;
   }
  
  return(y);
}

#define safety  (double) 0.9e0
#define pgrow   (double) -0.2e0
#define pshrink (double) -0.25e0
#define errcon  (double)  1.89e-4

void RUNGE5VAR(double *y, double dydx, double *x, double htry, double eps, 
               double yscale, double *hnext, double (*func)(double))
{
  double errmax,h,hold,htemp,xnew,yerr,ytemp,temp;
  
  h      = htry;
  errmax = (double) 10.0;
  while(errmax > (double) 1.0)
   {
    RUNGE(*y,dydx,*x,h,func,&ytemp,&yerr);
    
    errmax = fabs(yerr/yscale)/eps;
    if(errmax > (double) 1.0)
     { 
       htemp = safety*h * pow(errmax,pshrink);
       hold  = h;
       temp  = MAX(fabs(htemp),(double)0.1*fabs(h));
       
       if(h  >= 0)
         h = fabs(temp);
       else
         h = -fabs(temp);
       
       xnew = *x + h;
       
       if (fabs(xnew-*x) < (double)1e-5)
        {
         /*    	      printf("WARNING: Stepsize underflow in RUNGE5VAR()\n"); */
         h      = hold;
         errmax = (double)0.0;
        }
     }
   }
  if (errmax > errcon)
   {
    *hnext = safety*h * pow(errmax,pgrow);
   }
  else
   {
    *hnext = (double) 5.0 * h;
   }
  
  *x = *x + h;
  *y = ytemp;
  
  return;
}

#define a2      ((double) 0.2e0)
#define a3      ((double) 0.3e0)
#define a4      ((double) 0.6e0)
#define a5      ((double) 1.e0)
#define a6      ((double) 0.875e0)
#define c1      ((double) 37.e0/378.e0)
#define c3      ((double) 250.e0/621.e0)
#define c4      ((double) 125.e0/594.e0)
#define c6      ((double) 512.e0/1771.e0)
#define dc1     (c1 -  (double) 2825.e0/27648.e0)
#define dc3     (c3 -  (double) 18575.e0/48384.e0)
#define dc4     (c4 -  (double) 13525.e0/55296.e0)
#define dc5     ((double) -277.e0/14336.e0)
#define dc6     (c6 -  (double) 0.25e0)

void RUNGE(double y, double dydx, double x, double h, double(*func)(double),
           double *yout, double *yerr)
{
  double ak3, ak4, ak5, ak6;
  
  ak3  = FUNC((double)(x+a3*h));
  ak4  = FUNC((double)(x+a4*h));
  ak5  = FUNC((double)(x+a5*h));
  ak6  = FUNC((double)(x+a6*h));
  
  *yout = y + h*(c1*dydx + c3*ak3 + c4*ak4  + c6*ak6);
  *yerr = h*(dc1*dydx + dc3*ak3 + dc4*ak4 + dc5*ak5 + dc6*ak6);
}

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;
  
	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX
/* (C) Copr. 1986-92 Numerical Recipes Software ,2kB. */
float gasdev(long *idum)
{
	float ran1(long *idum);
	static int iset=0;
	static float gset;
	float fac,rsq,v1,v2;
  
	if  (iset == 0) {
		do {
			v1=2.0*ran1(idum)-1.0;
			v2=2.0*ran1(idum)-1.0;
			rsq=v1*v1+v2*v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac=sqrt(-2.0*log(rsq)/rsq);
		gset=v1*fac;
		iset=1;
		return v2*fac;
	} else {
		iset=0;
		return gset;
	}
}
/* (C) Copr. 1986-92 Numerical Recipes Software ,2kB. */


#define NR_END 1
#define FREE_ARG char*

#define SWAP(a,b) itemp=(a);(a)=(b);(b)=itemp;
#define NSTACK 50
#define M 7

void indexx(long n, double arr[], long indx[])
{
  long i,indxt,ir=n,itemp,j,k,l=1;
  int jstack=0,*istack;
  double a;
  
  istack=ivector(1,NSTACK);
  for (j=1;j<=n;j++) indx[j]=j;
  for (;;) {
    if (ir-l < M) {
      for (j=l+1;j<=ir;j++) {
        indxt=indx[j];
        a=arr[indxt];
        for (i=j-1;i>=1;i--) {
          if (arr[indx[i]] <= a) break;
          indx[i+1]=indx[i];
        }
        indx[i+1]=indxt;
      }
      if (jstack == 0) break;
      ir=istack[jstack--];
      l=istack[jstack--];
    } else {
      k=(l+ir) >> 1;
      SWAP(indx[k],indx[l+1]);
      if (arr[indx[l+1]] > arr[indx[ir]]) {
        SWAP(indx[l+1],indx[ir])
      }
      if (arr[indx[l]] > arr[indx[ir]]) {
        SWAP(indx[l],indx[ir])
      }
      if (arr[indx[l+1]] > arr[indx[l]]) {
        SWAP(indx[l+1],indx[l])
      }
      i=l+1;
      j=ir;
      indxt=indx[l];
      a=arr[indxt];
      for (;;) {
        do i++; while (arr[indx[i]] < a);
        do j--; while (arr[indx[j]] > a);
        if (j < i) break;
        SWAP(indx[i],indx[j])
      }
      indx[l]=indx[j];
      indx[j]=indxt;
      jstack += 2;
      if (jstack > NSTACK) nrerror("NSTACK too small in indexx.");
      if (ir-i+1 >= j-l) {
        istack[jstack]=ir;
        istack[jstack-1]=i;
        ir=j-1;
      } else {
        istack[jstack]=j-1;
        istack[jstack-1]=l;
        l=i;
      }
    }
  }
  free_ivector(istack,1,NSTACK);
}



/**
 * \brief  Finds the maximum in a given array.
 *
 * \param  *x      An array containing the x-values.
 * \param  *y      An array containing the y-values.
 * \param  num     The length of the both arrays.
 * \param  steps   Total number of interpolation steps.
 * \param  smooth  Total number of smoothing steps.
 * \param  *maxx   A pointer to a variable that will hold the position of
 *                 the maximum.
 * \param  *maxy   A pointer to a variable that will hold the value of
 *                 the function at the found maximum.
 *
 * \return  Returns nothing.
 */
void find_max_spline(double *x, double *y, int num, int smooth, double *maxx, double *maxy, int steps)
{
  double *y2, xi, yi, incr;
  
  /* Smooth the data */
  smooth3(y, num, smooth);
  
  /* obtain second derivatives to be used with splint(), i.e. "spline interpolation" */
  y2 = (double *) calloc(num, sizeof(double));
  spline(x-1, y-1, num, 2E33, 2E33, y2-1);
  
  /* scan the spline interpolation using splint() */
  *maxy = -1e10;
  incr = (x[num-1] - x[0])/(double)(steps-1);
  xi = x[0];
  while (xi <= x[num-1]) {
    splint(x-1, y-1, y2-1, num, xi, &yi);
    if (yi > *maxy) {
      *maxx = xi;
      *maxy = yi;
    }
    xi += incr;
  }
  
  free(y2);
  
  return;
}

/*==============================================================================
 * smooth data array
 *==============================================================================*/
void smooth3(double *data, int nbins, int nsmooth)
{
  int    i,j;
  double *tmpdata;
  
  if (nsmooth == 0)
    return;
  
  tmpdata = (double *)calloc(nbins, sizeof(double));
  
  for(j=0; j<nsmooth; j++)
   { 
     tmpdata[0] = (data[0]+data[1])/2.;
     
     for(i=1; i<nbins-1; i++)
       tmpdata[i] = (data[i-1]+data[i]+data[i+1])/3.;
     
     tmpdata[nbins-1] = (data[nbins-1]+data[nbins-2])/2.;
     
     for(i=0; i<nbins-1; i++)
       data[i] = tmpdata[i];
   }
  
  free(tmpdata);
  
}


void spline(double x[], double y[], int n, double yp1, double ypn, double y2[])
{
  int i,k;
  double p,qn,sig,un,*u;
  
  u=dvector((long)1,(long)(n-1));
  if (yp1 > 0.99e30)
    y2[1]=u[1]=0.0;
  else {
    y2[1] = -0.5;
    u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
  }
  for (i=2;i<=n-1;i++) {
    sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
    p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
    u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
  }
  if (ypn > 0.99e30)
    qn=un=0.0;
  else {
    qn=0.5;
    un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
  }
  y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
  for (k=n-1;k>=1;k--)
    y2[k]=y2[k]*y2[k+1]+u[k];
  free_dvector(u,(long)1,(long)(n-1));
}

void splint(double xa[], double ya[], double y2a[], int n, double x, double *y)
{
  void nrerror(char error_text[]);
  int klo,khi,k;
  double h,b,a;
  
  klo=1;
  khi=n;
  while (khi-klo > 1) {
    k=(khi+klo) >> 1;
    if (xa[k] > x) khi=k;
    else klo=k;
  }
  h=xa[khi]-xa[klo];
  if (h == 0.0) nrerror("Bad xa input to routine splint");
  a=(xa[khi]-x)/h;
  b=(x-xa[klo])/h;
  *y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
}

/*==============================================================================
 *  find maximum within array y[]
 *==============================================================================*/
void find_max(double *x, double *y, int nbins, int ismooth, double *x_max, double *y_max)
{
  int    ibin, ibin_max[2];
  double ymax;
  
  smooth3(y, nbins, ismooth);
  
  ymax = -10.0;
  
  /* approach from left */
  ibin_max[0] = nbins-1;
  for(ibin=0; ibin<nbins-1; ibin++)
   {
    if(y[ibin] > ymax)
     {
      ymax        = y[ibin];
      ibin_max[0] = ibin;
     }
   }
  
  /* approch from right */
  ibin_max[1] = ibin_max[0];
  for(ibin=(nbins-1+ibin_max[0])/2; ibin>ibin_max[0]; ibin--)
   {
    if(y[ibin] > ymax)
     {
      ymax        = y[ibin];
      ibin_max[1] = ibin;
     }
   }
  
  *x_max = ( x[ibin_max[0]] + x[ibin_max[1]] )/2;
  *y_max = ( y[ibin_max[0]] + y[ibin_max[1]] )/2;   
}




