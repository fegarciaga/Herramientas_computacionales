#include <iostream>
#include <cmath>
#include <cstdlib>

/* para compilar con una version mas moderna de c++ se debe utilizar la
 bandera g++ -std=c++17 (o le version en cuestion). El compilador debe 
soportar la version requerida */

int main (int argc, char* argv[])
{
    double x=-1;
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    int Nmax=std::atoi(argv[1]);
    for(int ii=0; ii<Nmax; ++ii)
    {
        std::cout<<x<<"\t"<<std::legendre(5,x)<<"\n";
        x+=0.01;
    }

    return 0;
}
