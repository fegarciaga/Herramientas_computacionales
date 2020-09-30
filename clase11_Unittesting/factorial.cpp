#include "factorial.h"

long factorial (long n)
{
    if(n<0)
    {
        std::cerr<<"ERROR factorial of negative numbers is no computable \n";
        return 0;
    }
    return n<=1 ? 1 : n*factorial(n-1);
}
