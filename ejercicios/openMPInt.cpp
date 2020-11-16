#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <omp.h>

void print_elapsed(auto start, auto end);
void fill(double *d, int n, int nthreads, double xi, double xf);
double integral(double *d, int n, int nthreads, double xi, double xf);


int main (int argc, char ** argv)
{
  const int N = std::atoi(argv[1]);
  const int NTH = std::atoi(argv[2]);
  const double x0 = std::atof(argv[3]);
  const double xF = std::atof(argv[4]);
  double * data = new double [N];
  fill(data, N, NTH, x0, xF);
  auto start = std::chrono::steady_clock::now();
  double value=integral(data, N, NTH, x0, xF);
  auto end = std::chrono::steady_clock::now();
  print_elapsed(start, end);
  //std::cout << value <<"\n";

  delete [] data;
  return 0;
}

void print_elapsed(auto start, auto end)
{
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<"\n";
}

void fill (double * d, int n, int nthreads, double xi, double xf)
{
#pragma omp parallel for num_threads (nthreads)
  for (int ii = 0; ii<n;++ii){
      d[ii]=(xi+1.0*ii/n*(xf-xi))*(xi+1.0*ii/n*(xf-xi));
    }
}

double integral (double * d, int n, int nthreads, double xi, double xf)
{
  double val = 0;
#pragma omp parallel for num_threads (nthreads) reduction (+:val)
  for (int ii = 0; ii<n; ++ii)
    {
      val+=(xf-xi)/n*d[ii];
    }
  return val;
}
