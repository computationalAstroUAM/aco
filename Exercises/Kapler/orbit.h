//
// Created by weiguang on 8/05/24.
//

#ifndef KAPLER_ORBIT_H
#define KAPLER_ORBIT_H
// orbit.h
#pragma once
#include <vector>
#include <string>

// choice of units: [l]=m, [m]=kg, [t]=s
constexpr double Grav = 6.6726E-11;             // m^3/kg/s^2
constexpr double Msun = 1.989E30;               // kg
constexpr double Mearth = 5.973E24;             // kg
constexpr double Dse = 1.496E11;                // m

constexpr int Nyears = 5;

//constexpr int Nsteps = 48;
constexpr double Tend = Nyears*365*24*60*60;

#define pow2(x)  ((x)*(x))

struct Orbit {
    double x, y;
    double vx, vy;
};

void output(const std::vector<Orbit>&, const std::string&, uint64_t);
void leapfrog(std::vector<Orbit>&, double, uint64_t);
void rungekutta4(std::vector<Orbit>&, double, uint64_t);
double GMr(double, double);
double hx(double, double, double, double);
double hy(double, double, double, double);
double hvx(double, double, double, double);
double hvy(double, double, double, double);
#endif //KAPLER_ORBIT_H
