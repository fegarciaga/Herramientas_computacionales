#include <iostream>
#include "mpi.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc, &argv);
  int pid=0, nproc=0;
  
  MPI_Comm_rank(MPI_COMM_WORLD, &pid); //process id
  MPI_Comm_size(MPI_COMM_WORLD, &nproc); // Total number of process
  std::cout<<"Hello world from pid:" << pid<<" out of "<<nproc<<"\n";
  
  MPI_Finalize();
  return 0;
}
