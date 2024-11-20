#ifndef STRUCT_PESSOA_H_INCLUDED
#define STRUCT_PESSOA_H_INCLUDED

using namespace std;

//--------------------------------------------------------------------------------------//
//variaveis globais                                                                     //
typedef enum{apto=0, exposto=1, infectado=2, recuperado=3} tipo_ps;     //tipo pessoa   //
//--------------------------------------------------------------------------------------//

struct Pessoa{
//variaveis
    tipo_ps estado; //enum
    int tp_exp;
    int tp_inf;

//prototipos dos metodos
    Pessoa **cria_matriz(int t);
    Pessoa **libera_matriz(Pessoa**, int);
    void print(Pessoa **p, int op);
};
//fim da struct Pessoa

Pessoa** Pessoa::cria_matriz(int t){
  int i;
  Pessoa **p;

    p = (struct Pessoa**)calloc(t, sizeof(struct Pessoa*));
        for(i=0; i<t; i++){
            p[i] = (struct Pessoa*)calloc(t, sizeof(struct Pessoa));
        }
    return (p);
}

Pessoa** Pessoa::libera_matriz(Pessoa **v, int t){
  int i;

    for (i=0; i<t; i++){
        free (v[i]);
    }
    free(v);
  return(NULL);
}

void Pessoa::print(Pessoa **p, int op){
  int i, j;

    switch(op){
    case 1:
        cout << "\nMat[][].estado: " << endl << endl;
        for(i=0; i<tam; i++){
            for(j=0; j<tam; j++){
                cout << p[i][j].estado << "\t";
            }
            cout << endl;
        }
    break;

    case 2:
        cout << "\nMat[][].tp_exp: " << endl << endl;
        for(i=0; i<tam; i++){
            for(j=0; j<tam; j++){
                cout << p[i][j].tp_exp << "\t";
            }
            cout << endl;
        }
    break;

    case 3:
        cout << "\nmat[][].tp_inf: " << endl << endl;
        for(i=0; i<tam; i++){
            for(j=0; j<tam; j++){
                cout << p[i][j].tp_inf << "\t";
            }
            cout << endl;
        }
    break;
    }
}

#endif  //H_INCLUDED
