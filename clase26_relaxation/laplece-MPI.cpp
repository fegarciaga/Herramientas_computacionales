#include <iostream>
#include <vector>
#include "mpi.h"

const double DELTA = 0.1;
const double XMIN = 0.0;
const double XMAX = 1.0;
const double YMIN = 0.0;
const double YMAX = 1.2;
const int NX = (XMAX-XMIN)/DELTA;
const int NY = (YMAX-YMIN)/DELTA;
const int NSTEPS = 100;

typedef std::vector<double> data_t;

//parallel functions
void initial_conditions_p(double * data, int nx, int ny, int pid, int np);
void print_screen_p(const double * data, int nx, int ny, int pid, int np);
void boundary_conditions_p(double * data, int nx, int ny, int pid, int np);
void evolve_p(double * data, int nx, int ny, int nsteps, int pid, int np);
void relaxation_step_p(double * data, int nx, int ny, int pid, int np);
void exchangeghost(double * data, int nx, int ny, int pid, int np);
//serial functions
void initial_conditions(double * data, int nx, int ny);
void boundary_conditions(double * data, int nx, int ny);
void evolve(double * data, int nx, int ny, int nsteps);
void relaxation_step(double * data, int nx, int ny);
void print_screen(const double*data, int nx, int ny);
void start_gnuplot(void);
void print_gnuplot(const double * data, int nx, int ny);


int main(int argc, char **argv)
{
    int pid = 0, nproc = 0;
    //inti mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    
    // declare data structures
    int NXlocal = NX/nproc;
    double * potential=new double [(NXlocal+2)*NY];

    // set initial and boundary conditions
    initial_conditions_p(potential, NXlocal+2, NY, pid, nproc);
    boundary_conditions_p(potential, NXlocal+2, NY, pid, nproc);
    print_screen_p(potential, NXlocal+2, NY, pid, nproc);
    // evolve and print
    evolve_p(potential, NXlocal+2, NY, NSTEPS, pid, nproc);
    print_screen_p(potential, NXlocal+2, NY, pid, nproc);
    delete [] potential;
    MPI_Finalize();
    return 0;
}

void initial_conditions(double * data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 1.0;
        }
    }
}

void initial_conditions_p(double * data, int nx, int ny, int pid, int np)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = pid;
        }
    }
}
void boundary_conditions(double * data, int nx, int ny)
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

void boundary_conditions_p(double * data, int nx, int ny, int pid, int np)
{
    if(pid==0){
        int ix, iy;
        // first row leaving ghost cell empty
        ix = 1;
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 100.0;
        }
    
        // first row
        iy = 0;
        for(int ix = 2; ix < nx; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
        // last row
        iy = ny-1;
        for(int ix = 2; ix < nx; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
    } else if (pid==np-1){
        int ix, iy;
        // last row leaving ghost cell empty
        ix = nx-2;
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 0.0;
        }
    
        // first row
        iy = 0;
        for(int ix = 0; ix < nx-1; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
        // last row
        iy = ny-1;
        for(int ix = 0; ix < nx-1; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
    } else {
        int iy;
    
        // first row
        iy = 0;
        for(int ix = 0; ix < nx; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
        // last row
        iy = ny-1;
        for(int ix = 0; ix < nx; ++ix) {
            data[ix*ny + iy] = 0.0;
        }
    }
}
void evolve(double * data, int nx, int ny, int nsteps)
{
    //start_gnuplot();
    for(int istep = 0; istep < nsteps; ++istep) {
        relaxation_step(data, nx, ny);
        print_screen(data, nx, ny);
        //print_gnuplot(data, nx, ny);
    }
}

void evolve_p(double * data, int nx, int ny, int nsteps, int pid, int np)
{
    //start_gnuplot();
    for(int istep = 0; istep < nsteps; ++istep) {
        exchangeghost(data, nx, ny, pid, np);
        relaxation_step_p(data, nx, ny, pid, np);
        //print_gnuplot(data, nx, ny);
    }
}
void relaxation_step(double * data, int nx, int ny)
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

void exchangeghost(double * data, int nx, int ny, int pid, int np)
{
    if(pid!=0){
        MPI_Send(data+ny, ny, MPI_DOUBLE, pid-1, 0, MPI_COMM_WORLD);
        MPI_Recv(data, ny, MPI_DOUBLE, pid-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (pid!= np-1){
        MPI_Send(data+ny*(nx-2), ny, MPI_DOUBLE, pid+1, 1, MPI_COMM_WORLD);
        MPI_Recv(data+ny*(nx-1), ny, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void relaxation_step_p(double *data, int nx, int ny, int pid, int np)
{
    // recorrer toda la matriz y aplicar el algoritmo,
    // teniendo cuidado con no modificar las condiciones de
    // frontera
    if(pid==0){
        // implements relaxation method
        // for pid == 0 the first ghost zone is not used
        for(int ix = 2; ix < nx-1; ++ix) {
            for(int iy = 1; iy < ny-1; ++iy) {
                data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
            }
        }
    } else if (pid==np-1){
        // for pid == np-1 the last ghost zone is not used
        for(int ix = 1; ix < nx-2; ++ix) {
            for(int iy = 1; iy < ny-1; ++iy) {
                data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
            }
        }
    } else {
        for(int ix = 1; ix < nx-1; ++ix) {
            for(int iy = 1; iy < ny-1; ++iy) {
                data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
            }
        }
    }
}
void print_screen(const double * data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            std::cout << data[ix*ny + iy] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_screen_p(const double * data, int nx, int ny, int pid, int np)
{
    if(pid == 0){
        print_screen(data, nx, ny);
        double * buffer= new double [nx*ny] {0.0}; 
        int tag = 0;
        for (int src = 1; src<np; ++src){
            MPI_Recv(buffer, nx*ny, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print_screen(buffer, nx, ny);
        }
        delete [] buffer; 
    } else {
        int dest = 0;
        MPI_Send(data, nx*ny, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
    }
}

void start_gnuplot(void)
{
    std::cout << "set pm3d\n";
    std::cout << "set contour base\n";y
    std::cout << "set term gif animate\n";
    std::cout << "set output 'anim.gif'\n";
}

void print_gnuplot(const double * data, int nx, int ny)
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
