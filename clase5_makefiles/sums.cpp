#include <iostream>
#include <cmath>

typedef float REAL;

double sumup (int Nmax);
double sumdown (int Nmax);

int main (void)
{
    for (int nmax=1; nmax<=100; ++nmax){
        std::cout<<nmax<<"\t"
                 << std::fabs(1-sumdown(nmax)/sumup(nmax))<< "\n";
    }
    
    return 0;
}

double sumup (int Nmax)
{
    REAL suma=0.0;
    for (int ii=1; ii<=Nmax; ++ii){
        suma += 1.0/ii;
    }

    return suma;
}
double sumdown (int Nmax)
{
    REAL suma=0.0;
    for (int ii=Nmax; ii >=1; --ii){
        suma += 1.0/ii;
    }

    return suma;
    
}
