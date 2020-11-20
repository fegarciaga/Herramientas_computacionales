#include <iostream>
#include "mpi.h"
#include <numeric>
#include <cstdlib>
#include <chrono>

void fill(double * data, int ns, int nslocal, int pid, int nproc, double xi, double xf);
void integral(double * data, int ns, int nslocal, int pid, int nproc, double xi, double xf);

int main (int argc, char ** argv)
{
  double start=0.0, end=0.0;
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  const int NS = std::atoi(argv[1]);
  const double Xi = std:: atof(argv[2]);
  const double Xf = std::atof(argv[3]);
			  
  MPI_Init(&argc, &argv);
  int pid = 0, nproc = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();
  const int NSlocal= NS/nproc;
  double * data = new double [NSlocal] {0.0};
  fill(data, NS, NSlocal, pid, nproc, Xi, Xf);
  integral(data, NS, NSlocal, pid, nproc, Xi, Xf);
  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();
  if(pid==0){
    std::cout<< end-start<<"\n";
      }
  delete [] data;
  MPI_Finalize();
  return 0;
}

void fill(double * data, int ns, int nslocal, int pid, int nproc, double xi, double xf)
{
  for (int ilocal = 0; ilocal < nslocal; ++ilocal ){
    data[ilocal]=(xi+1.0*(nslocal*pid+ilocal)/ns*(xf-xi))*(xi+1.0*(nslocal*pid+ilocal)/ns*(xf-xi));
  }
}

void integral(double * data, int ns, int nslocal, int pid, int nproc, double xi, double xf)
{
  int tag = 0;
  double sum = 0.0;
  sum =  std::accumulate(data, data + nslocal, 0.0);
  sum *= (xf-xi)/ns;
  if(0==pid)
    {
      double aux;
      for (int src = 1; src < nproc; ++src){
	MPI_Recv(&aux, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	sum += aux;
      }
    }
  else
    {
      int dest = 0;
      MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }
}
