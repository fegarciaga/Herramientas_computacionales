#include <iostream>
#include <random>

int main (void)
{
    const int NBINS =20;
    const double XMIN=0.0, XMAX=1.0;
    const int SEED= 1;
    const double DX=(XMAX-XMIN)/NBINS;

    double hist[NBINS]={0.0};
    std::mt19937 gen(SEED); //Declarando el generador 0 es la semilla
    std::uniform_real_distribution<double> dis(XMIN,XMAX);
    for ( int ii=0; ii<=10000; ++ii)
    {
        double r= dis(gen);
        int bin =int((r- XMIN)/DX);
        hist[bin] +=1;
    }

    for (int ii=0; ii<NBINS; ++ii)
    {
        std::cout<<XMIN+ii*DX<<"\t"<< hist[ii]<<"\n";
    }
    
    return 0;
}
