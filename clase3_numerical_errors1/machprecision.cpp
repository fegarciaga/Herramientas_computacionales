#include<iostream>
#include<cstdlib>

int main(int argc, char *argv[]){
  //argc cuenta los argumentos de la linea de comando
  //argv guarda los valores. Así se evita la compilacion manual para la
  //variacion de un parametro en el codigo
  float eps=1.0, one=1.0;
  int N=std::atoi(argv[1]);//atoi convierte string en entero
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);
  for(int ii=0; ii<N;ii++){
    eps/=2;
    one=1.0+eps;
    std::cout<<ii<<"\t"<<one<<"\t"<<eps<<"\n";
  }
  return 0;
}
