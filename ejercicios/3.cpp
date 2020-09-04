#include <iostream>
#include <cstdlib>
#include <cmath>

void findroot(double a, double b, double c);

int main (int argc, char* argv[])
{
    double a=std::atof(argv[1]), b=std::atof(argv[2]), c=std::atof(argv[3]);
    findroot(a,b,c);

    return 0;
}

void findroot(double a, double b, double c)
{
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);
    double root1=0, root2=0;
    if(std::fabs(4*c*a)<0.01)
    {
        root1=(-b-std::sqrt(b*b-4*a*c))/(2*a);
        root2=-2*c/(b+std::sqrt(b*b-4*a*c));
        std::cout<<"algorithm avoids sustractive cancelation \n";
        std::cout<< root1 <<"\t"<<root2<<"\n";
    }
    else {
    
        double root1 = (-b +std::sqrt(b*b-4.0*a*c))/(2.0*a);
        double root2= (-b -std::sqrt(b*b-4.0*a*c))/(2.0*a);
        std::cout << root1<<"\t"<<root2<<"\n";
    }

    return;
}

