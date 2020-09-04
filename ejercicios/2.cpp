#include <iostream>
#include <cstdlib>
#include <cmath>

double euler(void);

int main (int argc, char* argv[])
{
    //Calcula el valor de la constante de Euler
    euler();
    return 0;
}

double euler (void)
{
    double sum=0,eu2=0, eu1=0;
    for(int N=1;N<=5000;++N)
    {
        sum+=1.0/N;
        if(N%100==0)
        {
            eu1=sum-std::log(N);
            eu2=sum-std::log(N+0.5);
            std::cout<<N<<"\t"<<eu1<<"\t"<<eu2<<"\n";
        }
        
        else; 
    }
    return 0;
}
