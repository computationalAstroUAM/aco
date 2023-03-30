/*==============================================================================
 *    NR routines along with own adaptive 5th order Runge-Kutta INTEGRATE
 *==============================================================================*/
#ifndef NR_H_INCLUDED
#define NR_H_INCLUDED

#define PI           3.14159265358979323846264338
#define TWOPI       (2*PI)

#define TRUE         1
#define FALSE        0

#define pow2(x)  ((x)*(x))
#define pow3(x)  ((x)*(x)*(x))
#define MIN(A,B) ((A)<(B)?(A):(B))
#define MAX(A,B) ((A)>(B)?(A):(B))

#define FUNC(x)  ((*func)(x))

int ReadFloat          (FILE *fptr,float *n, int swap);
int ReadDouble         (FILE *fptr,double *n,int swap);
int ReadLongLong       (FILE *fptr,long long *n,int swap);
int ReadLong           (FILE *fptr,long *n,int swap);
int ReadUInt           (FILE *fptr,unsigned int *n,int swap);
int ReadInt            (FILE *fptr,int *n,int swap);
int ReadChars          (FILE *fptr,char *s,int n);
int ReadString         (FILE *fptr,char *s,int n);



void   indexx          (long n, double arr[], long indx[]);
void   locate          (double *, int, double, int *);
void   polint          (float *, float *, int, float, float *, float *);
double dilog           (double);
double dilogAPPROX     (double);
double gsl_sf_dilog    (double);
float  ran3            (long *idum);
float  gasdev          (long *idum);
double INTEGRATE       (double (*func)(double), double a, double b, double step, double eps);

void find_max(double *x, double *y, int nbins, int ismooth, double *x_max, double *y_max);
void find_max_spline(double *x, double *y, int num, int smooth, double *maxx, double *maxy, int steps);
void smooth3(double *data, int nbins, int nsmooth);

#ifndef _NR_UTILS_H_ 
#define _NR_UTILS_H_ 

#define MAXSTEPS 1000000000

static float sqrarg; 
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg) 

static double dsqrarg; 
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg) 

static double dmaxarg1,dmaxarg2; 
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?\ (dmaxarg1) : (dmaxarg2)) 

static double dminarg1,dminarg2; 
#define DMIN(a,b) (dminarg1=(a),dminarg2=(b),(dminarg1) < (dminarg2) ?\ (dminarg1) : (dminarg2)) 

static float maxarg1,maxarg2; 
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\ (maxarg1) : (maxarg2)) 

static float minarg1,minarg2; 
#define FMIN(a,b) (minarg1=(a),minarg2=(b),(minarg1) < (minarg2) ?\ (minarg1) : (minarg2)) 

static long lmaxarg1,lmaxarg2; 
#define LMAX(a,b) (lmaxarg1=(a),lmaxarg2=(b),(lmaxarg1) > (lmaxarg2) ?\ (lmaxarg1) : (lmaxarg2)) 

static long lminarg1,lminarg2;
#define LMIN(a,b) (lminarg1=(a),lminarg2=(b),(lminarg1) < (lminarg2) ?\ (lminarg1) : (lminarg2)) 

static int imaxarg1,imaxarg2; 
#define IMAX(a,b) (imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\ (imaxarg1) : (imaxarg2)) 

static int iminarg1,iminarg2; 
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\ (iminarg1) : (iminarg2)) 

//#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a)) 
#define SIGN(x)   (((x) > 0) ? 1 : (((x) < 0) ? -1 : 0))

#if defined(__STDC__) || defined(ANSI) || defined(NRANSI) /* ANSI */

void nrerror(char error_text[]); 
float *vector(long nl, long nh); 
int *ivector(long nl, long nh); 
unsigned char *cvector(long nl, long nh); 
unsigned long *lvector(long nl, long nh); 
double *dvector(long nl, long nh); 
float **matrix(long nrl, long nrh, long ncl, long nch); 
double **dmatrix(long nrl, long nrh, long ncl, long nch); 
int **imatrix(long nrl, long nrh, long ncl, long nch); 
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch, long newrl, long newcl); 
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch); 
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh); 
void free_vector(float *v, long nl, long nh); 
void free_ivector(int *v, long nl, long nh); 
void free_cvector(unsigned char *v, long nl, long nh); 
void free_lvector(unsigned long *v, long nl, long nh); 
void free_dvector(double *v, long nl, long nh); 
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch); 
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch); 
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch); 
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch); 
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch); 
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void spline(double x[], double y[], int n, double yp1, double ypn, double y2[]);
void splint(double xa[], double ya[], double y2a[], int n, double x, double *y);

#else /* ANSI */ 
/* traditional - K&R */ 

void nrerror(); 
float *vector(); 
Rest of traditional declarations are here on the diskette. 
#endif /* ANSI */ 
#endif /* _NR_UTILS_H_ */

#endif /* NR_H_INCLUDED */
