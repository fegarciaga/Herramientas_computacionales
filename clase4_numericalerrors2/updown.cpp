#include <iostream>
#include <cstdlib>
#include <cmath>

typedef float REAL;

REAL up (int Nmax);
REAL down (int Nmax);

int main (int argc, char*argv[])
{
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);
    int N =std::atoi(argv[1]);
    for (int ii=2; ii<N; ii+=5){
        REAL diff=std::fabs((up(ii)-down(ii)))/(up(ii)+down(ii));
        std::cout<<ii<<"\t"<<diff<<"\t"<< up(ii)<<"\t"<<down(ii)<<"\n";
    }
    return 0;
}

REAL up (int Nmax)
{
    REAL sum=0;
    for (int n=1; n<=Nmax; ++n){
        sum+=1.0/n;
    }

    return sum;
}

REAL down (int Nmax)
{
    REAL sum=0;
    for (int n=Nmax; n>=1;--n)
    {
        sum+=1.0/n;
    }
    return sum;
}

