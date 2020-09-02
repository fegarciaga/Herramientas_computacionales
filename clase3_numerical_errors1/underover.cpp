#include<iostream>
#include<cstdlib>

int main(int argc, char *argv[]){
  //argc cuenta los argumentos de la linea de comando
  //argv guarda los valores. Así se evita la compilacion manual para la
  //variacion de un parametro en el codigo
  float under=1.0;
  float over=1.0;
  int N=std::atoi(argv[1]);//atoi convierte string en entero
  for(int ii=0; ii<N;ii++){
    under/=2.0;
    over*=2.0;
    std::cout<<ii<<"\t"<<under<<"\t"<<over<<"\n";
  }
  return 0;
}
