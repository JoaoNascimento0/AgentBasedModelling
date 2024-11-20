#ifndef STRUCT_PS_MQ_H_INCLUDED
#define STRUCT_PS_MQ_H_INCLUDED

using namespace std;

//--------------------------------------------------------------------------------------//
//variaveis globais                                                                     //
typedef enum{vivo=0, operante=1, morto=2} tipo_mq;                 //vida do mosquito //
typedef enum{passivo=0, ativo=1} vetor_mq;                           //transmite(?)     //
//typedef enum{macho=0, femea=1} sexo_mq;                              //sexo mosquito  //
//--------------------------------------------------------------------------------------//

struct Mosquito{
//variaveis
    tipo_mq estado;     //enum
    vetor_mq atividade; //enum
    int sexo;
    int latencia;

//prototipos dos metodos
    void print(Mosquito*, int op);
    Mosquito *cria_vetor(int t);
    Mosquito *libera_vetor(Mosquito*);
};
//fim da struct Mosquito

Mosquito* Mosquito::cria_vetor(int t){
    return (struct Mosquito*)calloc(t, sizeof(struct Mosquito));
}

Mosquito* Mosquito::libera_vetor(Mosquito *v){
    free(v);
  return(NULL);
}

void Mosquito::print(Mosquito *p, int op){
  int i;

  switch(op){
    case 1:
        cout << "\nVet[].estado: \t";
        for(i=0; i<tam; i++){
            cout << p[i].estado << "\t";
        }
        cout << endl << endl;
    break;

    case 2:
        cout << "\nVet[].atividade:\t";
        for(i=0; i<tam; i++){
            cout << p[i].atividade << "\t";
        }
        cout << endl << endl;
    break;

    case 3:
        cout << "\nVet[].latencia:\t";
        for(i=0; i<tam; i++){
            cout << p[i].latencia << "\t";
        }
        cout << endl << endl;
    break;

    case 4:
        cout << "\nVet[].sexo:\t";
        for(i=0; i<tam; i++){
            cout << p[i].sexo << "\t";
        }
        cout << endl << endl;
    break;
    }
}
#endif // H_INCLUDED
