#include <math.h>

#ifndef RANDOM_H
#define RANDOM_H

class random{    //abriga o nmax e o metodo para gerar numeros aleatorios;
private:
    double Nmax = (pow(2,32)-1);  //Nmáx
    int first_inf = 5;      //numero de agentes que recebera a doença para start do programa
    double beta = 1;
    int min_exp = 8, max_exp = 12;  //de 8 a 12 dias para comecar a transmitir

protected:                       //mantem a funcao funcional pq a seed nao pode ser alterada
    unsigned seed = 62556245;    //se for alterada pode acontecer da funcao retornar um valor "zero" nao aleatorio
    unsigned r = 9989989;        //precisa ser public pois precisa ser constantemente alterado

public:
    double random_number(); //prototipo de metodos
    int parametro(int, int);
    int prob_infeccao();
};
#endif // RANDOM_H

//metodos
double random::random_number(){
    r = r * seed;
  return (r/Nmax);
}

int random::parametro(int x0, int x1){
    double rn = random_number();
  return (rn*(x1-x0)+x0);
}

int random::prob_infeccao(){
  int n=1;
  double rn = random_number();

    //double termo1 = (1 - beta);
    //double prob = (1 - (pow(termo1, n)));
    double prob = (1 - (1-beta));

    //termo1 = (1 - beta);  prob = (1 - (pow(termo1, n)));

    if(rn<prob){  return parametro(min_exp, max_exp);  }
    else{  return 0;  }
}
