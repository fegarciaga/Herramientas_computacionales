#ifndef __MD_SIMUL_H_
#define __MD_SIMUL_H_

#include <iostream>
#include "particle.h"

const double G = -9.81;
const int NSTEPS = 10000;
const double DT = 0.001;
const double K = 253.57;
const double Xwall =3.0;
const double Ywall =3.0;
const double Zwall =3.0;

// function declarations
void initial_conditions(Particle & body);
void compute_force(Particle & body);
void time_integration(Particle & body, const double & dt);
void start_integration(Particle & body, const double & dt);
void print(Particle & body, double time);
void Energy (Particle & body);

#endif // __MD_SIMUL_H_
