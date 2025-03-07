//
// Created by weiguang on 8/05/24.
//
// orbit.cpp
// orbit.cpp
#include "orbit.h"
#include <cmath>
#include <fstream>
#include <iostream>
#ifdef USE_OPENMP
#include <omp.h>
#endif

void leapfrog(std::vector<Orbit>& orbit, double dt, uint64_t istep) {
    double xmid, ymid;

#ifdef USE_OPENMP
    #pragma omp parallel sections
    {
        #pragma omp section
        {
#endif
            xmid = orbit[istep].x  + hx(orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy) * dt/2.;
            orbit[istep+1].vx = orbit[istep].vx + hvx(xmid, ymid, orbit[istep].vx, orbit[istep].vy) * dt;
            orbit[istep+1].x  = xmid + hx(orbit[istep].x, orbit[istep].y, orbit[istep+1].vx, orbit[istep+1].vy) * dt/2.;
#ifdef USE_OPENMP
        }
        #pragma omp section
        {
#endif
            ymid = orbit[istep].y  + hy(orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy) * dt/2.;
            orbit[istep+1].vy = orbit[istep].vy + hvy(xmid, ymid, orbit[istep].vx, orbit[istep].vy) * dt;
            orbit[istep+1].y  = ymid + hy(orbit[istep].x, orbit[istep].y, orbit[istep+1].vx, orbit[istep+1].vy) * dt/2.;
#ifdef USE_OPENMP
        }
    }
#endif
}

void rungekutta4(std::vector<Orbit>& orbit, double dt, uint64_t istep) {
    double k1, m1, n1, o1;
    double k2, m2, n2, o2;
    double k3, m3, n3, o3;
    double k4, m4, n4, o4;

#ifdef USE_OPENMP
    #pragma omp parallel sections
    {
        #pragma omp section
        {
#endif
            k1 = hx (orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy);
            k2 = hx (orbit[istep].x + k1*dt/2., orbit[istep].y + m1*dt/2., orbit[istep].vx + n1*dt/2., orbit[istep].vy + o1*dt/2.);
            k3 = hx (orbit[istep].x + k2*dt/2., orbit[istep].y + m2*dt/2., orbit[istep].vx + n2*dt/2., orbit[istep].vy + o2*dt/2.);
            k4 = hx (orbit[istep].x + k3*dt, orbit[istep].y + m3*dt, orbit[istep].vx + n3*dt, orbit[istep].vy + o3*dt);
            orbit[istep+1].x  = orbit[istep].x  + (k1+2*k2+2*k3+k4)/6. * dt;
#ifdef USE_OPENMP
        }
        #pragma omp section
        {
#endif
            m1 = hy (orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy);
            m2 = hy (orbit[istep].x + k1*dt/2., orbit[istep].y + m1*dt/2., orbit[istep].vx + n1*dt/2., orbit[istep].vy + o1*dt/2.);
            m3 = hy (orbit[istep].x + k2*dt/2., orbit[istep].y + m2*dt/2., orbit[istep].vx + n2*dt/2., orbit[istep].vy + o2*dt/2.);
            m4 = hy (orbit[istep].x + k3*dt, orbit[istep].y + m3*dt, orbit[istep].vx + n3*dt, orbit[istep].vy + o3*dt);
            orbit[istep+1].y  = orbit[istep].y  + (m1+2*m2+2*m3+m4)/6. * dt;
#ifdef USE_OPENMP
        }
        #pragma omp section
        {
#endif
            n1 = hvx(orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy);
            n2 = hvx(orbit[istep].x + k1*dt/2., orbit[istep].y + m1*dt/2., orbit[istep].vx + n1*dt/2., orbit[istep].vy + o1*dt/2.);
            n3 = hvx(orbit[istep].x + k2*dt/2., orbit[istep].y + m2*dt/2., orbit[istep].vx + n2*dt/2., orbit[istep].vy + o2*dt/2.);
            n4 = hvx(orbit[istep].x + k3*dt, orbit[istep].y + m3*dt, orbit[istep].vx + n3*dt, orbit[istep].vy + o3*dt);
            orbit[istep+1].vx = orbit[istep].vx + (n1+2*n2+2*n3+n4)/6. * dt;
#ifdef USE_OPENMP
        }
        #pragma omp section
        {
#endif
            o1 = hvy(orbit[istep].x, orbit[istep].y, orbit[istep].vx, orbit[istep].vy);
            o2 = hvy(orbit[istep].x + k1*dt/2., orbit[istep].y + m1*dt/2., orbit[istep].vx + n1*dt/2., orbit[istep].vy + o1*dt/2.);
            o3 = hvy(orbit[istep].x + k2*dt/2., orbit[istep].y + m2*dt/2., orbit[istep].vx + n2*dt/2., orbit[istep].vy + o2*dt/2.);
            o4 = hvy(orbit[istep].x + k3*dt, orbit[istep].y + m3*dt, orbit[istep].vx + n3*dt, orbit[istep].vy + o3*dt);
            orbit[istep+1].vy = orbit[istep].vy + (o1+2*o2+2*o3+o4)/6. * dt;
#ifdef USE_OPENMP
        }
    }
#endif
}

void output(const std::vector<Orbit>& orbit, const std::string& outfile, uint64_t Nsteps) {
    std::ofstream fpout(outfile);
    if(!fpout) {
        std::cerr << "could not open output file " << outfile << "\nABORTING\n";
        exit(0);
    }

    fpout << "#     x(1)             y(2)                vx(3)            vy(4)\n";
    for(uint64_t istep=0; istep<Nsteps; istep++){
        fpout << orbit[istep].x << " " << orbit[istep].y << " " << orbit[istep].vx << " " << orbit[istep].vy << "\n";
    }
    fpout.close();

    std::cerr << "wrote output file " << outfile << "\n";
}

double GMr(double x, double y) {
    return(Grav*Msun/pow( pow2(x)+pow2(y) , 1.5 ));
}

double hx(double x, double y, double vx, double vy) {
    return(vx);
}

double hy(double x, double y, double vx, double vy) {
    return(vy);
}

double hvx(double x, double y, double vx, double vy) {
    return(-GMr(x,y) * x);
}

double hvy(double x, double y, double vx, double vy) {
    return(-GMr(x,y) * y);
}