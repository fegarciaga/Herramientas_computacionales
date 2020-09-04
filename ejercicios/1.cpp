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
    double sum=0,eu=0;
    for(int N=1;N<=5000;++N)
    {
        sum+=1.0/N;
        if(5000%100==0)
        {
            eu=sum-std::log(N);
            std::cout<<N<<"\t"<<eu<<"\n";
        }
        
        else; 
    }
    return eu;
}
