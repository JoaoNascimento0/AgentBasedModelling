/*  Versao 1.0
-implementar vetor em ps ao inves de matrizes (complexidade desnecessaria)
-Melhorar a dinamica dentro de do-while
*/

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

const int tam = 10;  // global
const int quant = 5; // quantidade de mosquitos por vez
const int first_inf =
    15; // definicao de quantos agentes serao infectados em time = 0;

#include "Mosquito1.hpp"
#include "Pessoa1.hpp"
#include "aleatorio.hpp"

struct Mosquito mq;
struct Pessoa ps;
Random rn;

// metodo que define os primeiros infectados com a doença
void primeiros_infectados(Pessoa *m) {
  for (int i = 0; i < first_inf;) { // define n agentes infectados inicialmente
    int ci = rn.parametro(
        0, tam); // define um valor int a partir de rn entre zero e L

    if (m[ci].estado == apto) {
      m[ci].estado = infectado;
      m[ci].tp_inf = rn.parametro(0, tam);
      i++; // incremento do for, dessa forma não corre o risco de um mesmo
           // agente receber "infectado" duas vezes
    }
  }
}

// metodo que define que vetor e ativado e qual agente "visitar"
void transmissao(Pessoa *m, Mosquito *v) {
  for (int i = 0; i < quant; i++) {
    int aux = rn.parametro(0, tam); // sorteio de um mosquito dentro de vet[]

    int ci = rn.parametro(0, tam); // sorteio de um agente em mat[][]

    if (m[ci].estado == infectado) { // a pessoa picada tem o virus(?)
      v[aux].latencia =
          rn.parametro(30, 45); // se infectada, mosquito recebe uma latencia
                                // para comecar a transmitir
      v[aux].estado = operante;
    }
  }
}

void primeiros_vetores(Mosquito *v) {
  for (int i = 0; i < tam; i++) {
    v[i].latencia = rn.parametro(
        30, 45); // tempo de vida do mosquito varia entre 30 e 45 dias
    v[i].sexo = rn.parametro(0, 1); // zero se for macho, um se for femea
    v[i].atividade = passivo;       // todos os mosquitos iniciam sem a infeccao
    // v[i].estado = vivo;                   //vet[i] ja e instanciado como
    // "vivo" cout << v[i].latencia << "\t";
  }
}

void redefine(Mosquito *v, int i) {
  v[i].latencia = rn.parametro(
      30, 45); // tempo de vida do mosquito varia entre 30 e 45 dias
  v[i].sexo = rn.parametro(0, 1); // zero se for macho, um se for femea
  v[i].atividade = passivo;
}

void copia_vetor(Mosquito *aux, Mosquito *v) {
  for (int i = 0; i < tam; i++) {
    v[i].latencia = aux[i].latencia;
    v[i].sexo = aux[i].sexo;
    v[i].atividade = aux[i].atividade;
    v[i].estado = aux[i].estado;
  }
}

int main(int argc, char **argv) {
  int i, j;
  int time = 0;                  // medido em dias
  int contagem_de_agentes = tam; // contagem de agentes recebe a quantidade
                                 // inicial e toda vez que um morre, soma ++
  bool var = true;

  struct Pessoa *mat =
      ps.cria_matriz(tam); // alocando uma matriz de struct dinamicamente
  struct Mosquito *vet =
      mq.cria_vetor(tam); // alocando um vetor de struct dinamicamente

  primeiros_infectados(mat); // primeiros agentes a receber a doença
  primeiros_vetores(vet);    // primeiros vetores sao definidos
  // mq.print(vet, 1); mq.print(vet, 2); mq.print(vet, 3); mq.print(vet, 4);

  // time++;
  cout << "novo tempo!!!!"
       << "\t"
       << "time: " << time << endl;
  // mq.print(vet, 1); mq.print(vet, 2); mq.print(vet, 3); mq.print(vet, 4);
  system("pause");

  // transmissao(mat, vet);
  // do{
  for (int k = 0; k < 100; k++) {
    cout << "novo tempo!!!!"
         << "\t"
         << "time: " << time << endl;
    time++;

    transmissao(mat, vet);
    // ps.print(mat, 1); ps.print(mat,2); ps.print(mat, 3);

    // contadores

    for (i = 0; i < tam; i++) {
      for (j = 0; j < tam; j++) {
        if (mat[i].tp_exp !=
            0) { // se tempo de exposicao for diferente de zero, ou seja, se o
                 // agente tiver recebido a infeccao
          mat[i].tp_exp--;
        }
        if (mat[i].tp_exp ==
            1) { // se tempo de exposicao acabou, agente comeca a infectar
          mat[i].tp_exp--;
          mat[i].estado = infectado;
        }

        if (mat[i].tp_inf != 0) { // se tempo de infeccao for diferente de zero,
                                  // ou seja, se o agente estiver "ativo"
          mat[i].tp_inf--;
        }
        if (mat[i].tp_inf ==
            1) { // se tempo de infeccao acabou, agente se torna recuperado
          mat[i].tp_inf--;
          mat[i].estado = recuperado;
        }
      }
    }

    for (i = 0; i < tam; i++) {
      /*if(vet[i].latencia == 1){
          redefine(vet, i);
          contagem_de_agentes++;
      }*/
      if (vet[i].latencia != 0) {
        vet[i].latencia--;
      }
      if (vet[i].latencia <= 12 && vet[i].estado == operante) {
        vet[i].atividade = ativo;
      }
    }

    // ps.print(mat, 1); ps.print(mat,2); ps.print(mat, 3);
    mq.print(vet, 1);
    mq.print(vet, 2);
    mq.print(vet, 3);
    mq.print(vet, 4);
    system("pause");

    // var = false;
    // teste_break.cpp
  } // while(var);    //enquanto var == true

  mat = ps.libera_matriz(mat);
  vet = mq.libera_vetor(vet);
  return 0;
}
