#include <iostream>
#include <cstdlib>
#include <cmath>

float f (float x);
float fimp(float x);

int main (int argc, char* argv[])
{
    std::cout.precision(8);
    std::cout.setf(std::ios::scientific);
    float x=0;
    for (int ii=1; ii<=100;++ii)
    {
        std::cout<<x<<"\t"<<f(x)<<"\t"<<fimp(x)<<"\n";
        x+=(M_PI)/(4*100);
    }

    return 0;
}

float f (float x)
{
    return std::sin(x)-1+std::cos(x);
}

float fimp (float x)
{
    return 2*std::sin(x/2)*(std::cos(x/2)-std::sin(x/2));
}
