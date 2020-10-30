#include <iostream>
#include <omp.h>

int main(int argc, char **argv)
{
    double x=15; //global variable
#pragma omp parallel
    {
        double y=56.8; //local variable
        int tid = omp_get_thread_num();
        int nth=omp_get_num_threads();
        if(0==tid){
            std::cout<<"nth:"<<nth<<"\n";
        }
        
        std::cout<< "Hello world, from id:"<<tid<< "\n";
    }
    return 0;
}
