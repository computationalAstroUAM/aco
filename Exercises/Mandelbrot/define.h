//
// Created by weiguang on 18/04/24.
//

#ifndef MANDELBROT_DEFINE_H
#define MANDELBROT_DEFINE_H

/* definitions for our Mandelbrot series */
#define C_REAL_MIN      -2.0
#define C_IMG_MIN       -1.1
#define C_REAL_MAX      +0.5
#define C_IMG_MAX       +1.1
#define Z_INIT_REAL      0
#define Z_INIT_IMG       0
#define EPS              1e-5
#define NMAX_ITER        50

/* some boolean defines */
#define FALSE            0
#define TRUE             1

/* some handy shortcuts */
#define pow2(x)    ((x)*(x))
#define index(i,j,N) ((i)*(N)+(j))

#endif //MANDELBROT_DEFINE_H

