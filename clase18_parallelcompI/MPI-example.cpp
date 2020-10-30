#include <iostream>
#include <mpi.h>

int main (int argc, char **argv)
{
    MPI_Init(&argc, &argv);//Mandatory
    
    int rank, size; //rank: who am I?
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cout <<"Hello from process: " << rank
              <<" out of "<<size <<"\n";
    
    MPI_Finalize();
    return 0;
}
