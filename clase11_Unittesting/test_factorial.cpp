#include <iostream>
#include "factorial.h"

int main(int argc, char **argv)
{
    if( factorial(0)!=1)
    {
        std::cerr << "ERROR: factorial(0)!=1 \n";
    }
    if( factorial(1)!=1)
    {
        std::cerr << "ERROR: factorial(1)!=1 \n";
    }
    if( factorial(2)!=2)
    {
        std::cerr << "ERROR: factorial(2)!=1 \n";
    }
    if( factorial(10)!=3628800)
    {
        std::cerr << "ERROR: factorial(10)!=3628800 \n";
    }
    else
    {
        std::cout<<"ALL TESTS PASSED \n";
    }
    /*std::cout << factorial(3) <<"\n";
    std::cout << factorial(5) <<"\n";
    std::cout << factorial(20) <<"\n";
     */   
    return 0;
}
