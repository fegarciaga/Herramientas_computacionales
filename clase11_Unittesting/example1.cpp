#include <iostream>
#include "factorial.h"

int main(int argc, char **argv)
{
    std::cout << factorial(0) <<"\n"; //Error
    std::cout << factorial(1) <<"\n";
    std::cout << factorial(3) <<"\n";
    std::cout << factorial(5) <<"\n";
    std::cout << factorial(20) <<"\n";
        
    return 0;
}
