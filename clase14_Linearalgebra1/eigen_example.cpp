#include <iostream>
#include <Eigen/Dense>
#include <cstdlib>
 
 
int main(int argc, char **argv)
{
    //Creates random number between -1 and 1
    Eigen::MatrixXd m=Eigen::MatrixXd::Random(3,3);
    std::cout << m << std::endl;

    //Solves a linear algebra problem
    int N=std::atoi(argv[1]);
    Eigen::MatrixXd A(N,N);
    Eigen::VectorXd b(N);
    A=Eigen::MatrixXd::Random(N,N);
    b=Eigen::VectorXd::Random(N);
    std::cout << "Here is the matrix A:\n" << A << std::endl;
    std::cout << "Here is the vector b:\n" << b << std::endl;
    Eigen::VectorXd x(N);
    x = A.colPivHouseholderQr().solve(b);
    std::cout << "The solution is:\n" << x << std::endl;
    std::cout << "Error is :"<<(A*x-b).norm()<<"\n";
    return 0;
}
