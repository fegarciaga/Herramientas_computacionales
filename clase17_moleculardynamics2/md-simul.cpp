#include "md-simul.h"

void initial_conditions(Particle & body)
{
  body.Rx = 1.340;
  body.Ry = 1.6598;
  body.Rz =0.365;
  body.Vx = 0.23698;
  body.Vy = 0.1567;
  body.Vz = -0.357;
  body.rad = 0.235;
  body.mass = 0.29698;
  Energy(body);
}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

  // gravitational force
  body.Fy += body.mass*G;

  // force with ground
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    //body.Fy -= 1.9876*body.Vy;
  }

  // Force with upper wall
  delta = body.Ry + body.rad - Ywall;
  if (delta > 0) {
    body.Fy-= K*delta;
  }

  // Left wall
  delta = body.rad - body.Rx;
  if (delta > 0) {
    body.Fx += K*delta;
  }

  delta = body.Rx +body.rad - Xwall;
  if (delta > 0) {
    body.Fx -= K*delta;
}

  delta = body.rad - body.Rz;
  if (delta > 0) {
    body.Fz += K*delta;
  }

  // Front wall
  delta = body.Rz +body.rad - Zwall;
  if (delta > 0) {
    body.Fz -= K*delta;
  }
}

void start_integration(Particle & body, const double & dt)
{
  body.Vx -= body.Fx*dt/(2*body.mass);
  body.Vy -= body.Fy*dt/(2*body.mass);
  body.Vz -= body.Fz*dt/(2*body.mass);
}

  void time_integration(Particle & body, const double & dt)
{
  // leap-frog
  Energy(body);
  body.Vx += body.Fx*dt/(body.mass);
  body.Vy += body.Fy*dt/(body.mass);
  body.Vz += body.Fz*dt/(body.mass);
  body.Rx += body.Vx*dt;
  body.Ry += body.Vy*dt;
  body.Rz += body.Vz*dt;
 
}

void print(Particle & body, double time)
{
  std::cout << time << "  "
            << body.Rx << "  "
            << body.Ry << "  "
            << body.Rz << "  "
            << body.Vx << "  "
            << body.Vy << "  "
            << body.Vz << "  "
            << body.E  << "  "
            << "\n";
}

void Energy (Particle & body)
{
  body.E=0.0;
  //kinetical energy
  body.E += 0.5*body.mass*(body.Vx*body.Vx+body.Vy*body.Vy+body.Vz*body.Vz);
  
  //gravitational energy
  body.E -= body.mass*G*body.Ry;
  //Elastic energy
  
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }

  // Force with upper wall
  delta = body.Ry + body.rad - Ywall;
  if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }

  // Left wall
  delta = body.rad - body.Rx;
  if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }

  delta = body.Rx +body.rad - Xwall;
    if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }

  delta = body.rad - body.Rz;
  if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }

  // Front wall
  delta = body.Rz +body.rad - Zwall;
    if (delta > 0) {
    body.E += 0.5*K*delta*delta;
  }
  
}
