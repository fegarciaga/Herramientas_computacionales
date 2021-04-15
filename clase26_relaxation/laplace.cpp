#include <iostream>
#include <vector>
#include "mpi.h"

const double DELTA = 0.1;
const double XMIN = 0.0;
const double XMAX = 0.8;
const double YMIN = 0.0;
const double YMAX = 1.2;
const int NX = (XMAX-XMIN)/DELTA;
const int NY = (YMAX-YMIN)/DELTA;
const int NSTEPS = 1000;

typedef std::vector<double> data_t;

//parallel functions
void initial_conditions_p(data_t & data, int nx, int ny, int pid, int np);
void print_screen_p(const data_t & data, int nx, int ny, int pid, int np);
void boundary_conditions_p(data_t & data, int nx, int ny, int pid, int np);
void evolve_p(data_t & data, int nx, int ny, int nsteps, int pid, int np);
void relaxation_step_p(data_t & data, int nx, int ny, int pid, int np);
void exchangeghost(data_t & data, int nx, int ny, int pid, int np);
//serial functions
void initial_conditions(data_t & data, int nx, int ny);
void boundary_conditions(data_t & data, int nx, int ny);
void evolve(data_t & data, int nx, int ny, int nsteps);
void relaxation_step(data_t & data, int nx, int ny);
void print_screen(const data_t & data, int nx, int ny);
void start_gnuplot(int pid, int np);
void print_gnuplot(const data_t & data, int nx, int ny, int pid, int np);


int main(int argc, char **argv)
{
    int pid = 0, nproc = 0;
    //inti mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    
    // declare data structures
    int NXlocal = NX/nproc;
    data_t potential ((NXlocal+2)*NY);

    // set initial and boundary conditions
    initial_conditions_p(potential, NXlocal+2, NY, pid, nproc);
    boundary_conditions_p(potential, NXlocal+2, NY, pid, nproc);
    //print before interaction
    print_screen_p(potential, NXlocal+2, NY, pid, nproc);
    // evolve and print
    evolve_p(potential, NXlocal+2, NY, NSTEPS, pid, nproc);
    //print after relaxation
    print_screen_p(potential, NXlocal+2, NY, pid, nproc);

    MPI_Finalize();
    return 0;
}

void initial_conditions(data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 1.0;
        }
    }
}

void initial_conditions_p(data_t & data, int nx, int ny, int pid, int np)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 0;
        }
    }
}
void boundary_conditions(data_t & data, int nx, int ny)
{
    int ix, iy;
    // first row
    ix = 0;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 100.0;
    }
    // last row
    ix = nx-1;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 0.0;
    }
    // first row
    iy = 0;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    // last row
    iy = ny-1;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    //new
    //ix = nx/2;
    //for(int iy = ny/3; iy <= 2*ny/3; ++iy) {
    //    data[ix*ny + iy] = -50.0;
    //}
}

void boundary_conditions_p(data_t & data, int nx, int ny, int pid, int np)
{
    int ix, iy;
    if(pid==0){
        // first row leaving ghost cell empty
        ix = 1;
        for(iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 100.0;
        }
    }       
    if (pid==np-1){
        // last row leaving ghost cell empty
        ix = nx-2;
        for(iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 0.0;
        }
    }

    // first row
    iy = 0;
    for(ix = 2; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    // last row
    iy = ny-1;
    for(ix = 2; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
}
void evolve(data_t & data, int nx, int ny, int nsteps)
{
    //start_gnuplot();
    for(int istep = 0; istep < nsteps; ++istep) {
        relaxation_step(data, nx, ny);
        print_screen(data, nx, ny);
        //print_gnuplot(data, nx, ny);
    }
}

void relaxation_step(data_t & data, int nx, int ny)
{
    // recorrer toda la matriz y aplicar el algoritmo,
    // teniendo cuidado con no modificar las condiciones de
    // frontera
    for(int ix = 1; ix < nx-1; ++ix) {
        for(int iy = 1; iy < ny-1; ++iy) {
            // check that this cell is NOT a boundary condition or a border
            //if ( (ix == nx/2) && (ny/3 <= iy) && (iy <= 2*ny/3) ) continue;
            // update the cell
            data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
        }
    }
}

void evolve_p(data_t & data, int nx, int ny, int nsteps, int pid, int np)
{
    //start_gnuplot();
    for(int istep = 0; istep < nsteps; ++istep) {
        exchangeghost(data, nx, ny, pid, np);
        relaxation_step_p(data, nx, ny, pid, np);
        //print_gnuplot(data, nx, ny);
    }
}

void exchangeghost(data_t & data, int nx, int ny, int pid, int np)
{
    if(pid!=0){
        MPI_Send(&data[ny], ny, MPI_DOUBLE, pid-1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data[0], ny, MPI_DOUBLE, pid-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (pid!= np-1){
        MPI_Send(&data[ny*(nx-2)], ny, MPI_DOUBLE, pid+1, 1, MPI_COMM_WORLD);
        MPI_Recv(&data[ny*(nx-1)], ny, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void relaxation_step_p(data_t & data, int nx, int ny, int pid, int np)
{
    // recorrer toda la matriz y aplicar el algoritmo,
    // teniendo cuidado con no modificar las condiciones de
    // frontera
    int upbound = nx-1;
    int downbound = 1;
    if(pid==0){
        // implements relaxation method
        // for pid == 0 the first ghost zone is not used
        downbound = 2;
    } if (pid==np-1){
        // for pid == np-1 the last ghost zone is not used
        upbound = nx-2;       
    }
    for(int ix = downbound; ix < upbound; ++ix) {
            for(int iy = 1; iy < ny-1; ++iy) {
                data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
            }
        }
}
void print_screen(const data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
                std::cout << data[ix*ny + iy] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_screen_p(const data_t & data, int nx, int ny, int pid, int np)
{
    if(pid == 0){
        print_screen(data, nx, ny);
        data_t buffer(nx*ny); 
        int tag = 0;
        for (int src = 1; src<np; ++src){
            MPI_Recv(&buffer[0], nx*ny, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print_screen(buffer, nx, ny);
        }
        
    } else {
        int dest = 0;
        MPI_Send(&data[0], nx*ny, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
    }
}

void start_gnuplot(int pid, int np)
{
    if(0 == pid)
    {
    std::cout << "set pm3d\n";
    std::cout << "set contour base\n";
    std::cout << "set term gif animate\n";
    std::cout << "set output 'anim.gif'\n";
    }
}

void print_gnuplot(const double * data, int nx, int ny, int pid, int np)
{
    std::cout << "splot '-' w l lt 3 \n";
    for(int ix = 0; ix < nx; ++ix) {
        double x = XMIN + ix*DELTA;
        for(int iy = 0; iy < ny; ++iy) {
            double y = YMIN + iy*DELTA;
            std::cout << x << "  " << y << "  " << data[ix*ny + iy] << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "e\n";
}
