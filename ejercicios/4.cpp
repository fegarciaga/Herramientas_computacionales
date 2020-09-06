#include <iostream>
#include <cstdlib>
#include <cmath>

double sumexp ( double x);
double expimp (double x);
double expalt (double x);

int main (void)
{
    double x1[8]={0.0, 1, -1, 0.5, -0.123, -25.5, -1776, 3.14159};
    for (int ii=0; ii<=7; ++ii)
    {
    
        expimp(x1[ii]);
    }

    return 0;
}

double sumexp (double x)
{
    double sum=0;
    double term=1;
    int n=0;
    while (std::fabs(term)>0.000001 && n<25)
    {
        sum+=term;
        n+=1;
        term*=1.0*x/n;
        
    }
    double error=std::fabs(sum-std::exp(x));
    std::cout<<n<<"\t"<<sum<<"\t"<<error<<"\t"<<error/std::exp(x)<<"\n";
    
    return sum;
}

double expimp( double x)
{
    double z=x/std::log(2);
    if (x>0)
    {
        int m=z+0.5;
        double w=z-m, u=w*std::log(2);
        double exp =std::pow(2,m)*std::exp(u);
        std::cout<<x<<"\t"<<exp<<"\t"<<std::exp(x)<<"\n";
        return exp ;
        
    }
    else
    {
        int m=z-0.5;
        double w=z-m, u=w*std::log(2);
        double exp =std::pow(2,m)*std::exp(u);
        std::cout<<x<<"\t"<<exp<<"\t"<<std::exp(x)<<"\n";
        return exp ;
    }
    
}

double expalt (double x)
{
    double z=x/std::log(2);
    if (x>0)
    {
        int m=z+0.5;
        double w=z-m, u=w*std::log(2);
        double s=2+u*u*(2520+28*u*u)/(15120+420*u*u+u*u*u*u);
        double expu=s+u/s-u;
        double exp =std::pow(2,m)*expu;
        std::cout<<x<<"\t"<<exp<<"\t"<<std::exp(x)<<"\n";
        return exp ;
        
    }
    else
    {
        int m=z-0.5;
        double w=z-m, u=w*std::log(2);
        double s=2+u*u*(2520+28*u*u)/(15120+420*u*u+u*u*u*u);
        double expu=s+u/s-u;
        double exp =std::pow(2,m)*expu;
        std::cout<<x<<"\t"<<exp<<"\t"<<std::exp(x)<<"\n";
        return exp ;
    }
    
}
