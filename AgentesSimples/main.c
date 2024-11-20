#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define suscetivel 0
#define exposto 1
#define infectado 2
#define recuperado 3

#define inf_inicial 5   //numero de pessoas infectadas no inicio da simulacao
#define L 317           //tamanho da matriz L*L /*OBJETIVO É L = 317*/

#define tmin_inf 7      //7 dias é o tempo mínimo para continuar infectado
#define tmax_inf 12     //12 dias é o tempo maximo para continuar infectado

#define tmin_exp 7      //7 dias é o tempo mínimo para continuar exposto
#define tmax_exp 12     //7 dias é o tempo mínimo para continuar exposto

#define beta 0.05

#define Nmax 4294967295

unsigned r = 9989989, seed = 62556245;

struct pessoa{          //struct para definir os parametros dentro das matrizes
    int saude;          //{0, 1, 2, 3}
    int texp;           //tempo dps da exposicao para se tornar infectado {7 a 12 dias}
    int tinf;           //tempo dps de infectado para se tornar recuperado {7 a 12 dias}
};
//suscetivel{0} -> exposto{1} -> infectado{2} -> recuperado{3}

double random_number(){
    r = r * seed;
    return (r/Nmax);
}

void print_matriz(struct pessoa matriz[L+4][L+4], int tempo, int op){
//indice op 1 = matriz.saude, op 2 = tempo de exposicao, op 3 = tempo de infeccao
int i, j;

    if(op == 1){
        printf("\nt=%d\n", tempo);
        for (i=1; i<=L; i++){
            for (j=1; j<=L; j++){
                printf("%d\t", matriz[i][j].saude);
            }
            printf("\n");
        }
    }
    if(op == 2){
        printf("\ntempo de exposicao:\n");
        for (i=1; i<=L; i++){
            for (j=1; j<=L; j++){
                printf("%d\t", matriz[i][j].texp);
            }
            printf("\n");
        }
    }
    if(op == 3){
        printf("\ntempo de infeccao\n");
        for (i=1; i<=L; i++){
            for (j=1; j<=L; j++){
                printf("%d\t", matriz[i][j].tinf);
            }
            printf("\n");
        }
    }
}

void copia_borda(struct pessoa m[L+4][L+4]){
int i, j;

    for (i=1; i<=L; i++){
        for (j=1; j<=L; j++){
        m[i][0].saude = m[i][L].saude;      //coluna "zero" recebe "L"
        m[i][L+1].saude = m[i][1].saude;    //coluna "L+1" recebe "um"

        m[0][j].saude = m[L][j].saude;      //linha "zero" recebe "L"
        m[L+1][j].saude = m[1][j].saude;    //linha "L+1" recebe "um"
        }
    }                           //os contornos verticais e horizontais funcionam!
}

void copia_matriz(struct pessoa aux[L+4][L+4], struct pessoa m[L+4][L+4]){
int i, j;

    for(i=1; i<=L; i++){
        for(j=1; j<=L; j++){
            m[i][j].saude = aux[i][j].saude; //copiando matriz aux para matriz m
            m[i][j].texp = aux[i][j].texp; //copiando matriz aux para matriz m
            m[i][j].tinf = aux[i][j].tinf; //copiando matriz aux para matriz m
        }
    }
}

int parametro(int tmin, int tmax){
    double rn = random_number();
    return (rn*(tmax - tmin) + tmin);
}

int prob_infeccao(int n){
double rn = random_number();
double prob;
double termo1;

    termo1 = (1 - beta);
    prob = (1 - (pow(termo1, n)));

    if(rn < prob){
        return parametro(tmin_exp, tmax_exp);
    }
    else{
        return 0;
    }
}

void salva_matriz(struct pessoa m[L+4][L+4], int tempo, FILE *fp){
int i, j;
int cont_susceptivel=0, cont_exposto=0, cont_infectado=0, cont_recuperado=0, soma=0;

    for (i=1; i<=L; i++){
        for (j=1; j<=L; j++){
            if (m[i][j].saude == suscetivel){
            cont_susceptivel++;   }

            else if(m[i][j].saude == exposto){
            cont_exposto++;
            }

            else if (m[i][j].saude == infectado){
            cont_infectado++;  }

            else if (m[i][j].saude == recuperado){
            cont_recuperado++;    }
        }
    }
    soma = cont_susceptivel + cont_exposto + cont_infectado + cont_recuperado;

    //tempo, susceptiveis, infectados, recuperados
    fprintf( fp,"%d\t %d\t %d\t %d\t %d\t %d\n", tempo, cont_susceptivel, cont_exposto, cont_infectado, cont_recuperado, soma);
}

void main()
{
FILE *fp;
int cont=1, contj=0, conti=0, n=0, tempo = 0;   //contadores
double rn;                                      //random number
struct pessoa m[L+4][L+4];
struct pessoa aux[L+4][L+4];       //matrizes
int i, j, k, tam=(L+4)*2*3;
int *mat;

    //mat =(pessoa*)malloc(tam*sizeof(pessoa));

    //fp = fopen("teste_agente_simples.txt", "wt");

    for (i=1; i<=L; i++){
        for (j=1; j<=L; j++){
            m[i][j].saude = 0;              //tornando todos os agentes da matriz suscetiveis
            m[i][j].texp = 0;               //aproveitando o "for" para zerar todos os parametros da matriz
            m[i][j].tinf = 0;               //evita que o pc preencha os espaços com lixo ("numeros aleatorios indesejados")
            aux[i][j].saude = 0;
            aux[i][j].texp = 0;
            aux[i][j].tinf = 0;
        }
    }
        //print_matriz(m, tempo, 1);     //print m[][].saude
        //print_matriz(m, tempo, 2);     //print m[][].texp
        //print_matriz(m, tempo, 3);     //print m[][].tinf

    for(k=1; k<=inf_inicial; ){             //define n agentes infectados inicialmente
        conti = parametro(0, L);            //define um valor int a partir de rn entre zero e L
        contj = parametro(0, L);

        if (m[conti][contj].saude == suscetivel){
            m[conti][contj].saude = infectado;
            m[conti][contj].tinf = parametro(tmin_inf, tmax_inf);
            k++;    //incremento do for, dessa forma não corre o risco de um mesmo agente receber "infectado" duas vezes
        }
    }

    for(i=1; i<=L; i++){                    //tempo de infeccao ta sendo gravado certinho ma matriz m[][].tinf para os n primeiros
        for(j=1; j<=L; j++){
            if (m[i][j].saude == infectado){
                m[i][j].tinf = parametro(tmin_inf, tmax_inf);
            }
        }
    }
    copia_borda(m);
    salva_matriz(m, tempo, fp);

    //print_matriz(m, tempo, 1);     //print m[][].saude
        //print_matriz(m, tempo, 2);     //print m[][].texp
        //print_matriz(m, tempo, 3);     //print m[][].tinf

        //printf("\n\nAUXILIAR\n\n");
        //print_matriz(aux, tempo, 1);
        //print_matriz(aux, tempo, 2);
        //print_matriz(aux, tempo, 3);


    while(cont != 0){    //enquanto houver infectados faça

        cont = 0;       //caso nenhuma condicao seja satisfeita, a simulacao se encerra.
        tempo++;

        for (i=1; i<=L; i++){           //for para exposicao de agentes
            for (j=1; j<=L; j++){

                if(m[i][j].saude == suscetivel){    //aux para os suscetiveis
                    n=0;
                    if(m[i-1][j].saude == infectado){ n++; }
                    if(m[i+1][j].saude == infectado){ n++; }
                    if(m[i][j-1].saude == infectado){ n++; }
                    if(m[i][j+1].saude == infectado){ n++; }
                    if(n>0){
                        aux[i][j].texp = prob_infeccao(n);
                    }
                    if(aux[i][j].texp != 0){
                        aux[i][j].saude = exposto;
                    }
                }
                else if(m[i][j].saude == infectado){                 //aux para os infectados
                    if(m[i][j].tinf != 1){
                        aux[i][j].saude = infectado;
                    }
                }
                else if(m[i][j].saude == recuperado){                //aux para os recuperados
                        aux[i][j].saude = recuperado;
                }

                aux[i][j].tinf = m[i][j].tinf;

                if(m[i][j].texp == 1){  //passa de exposto para infectado
                    aux[i][j].saude = infectado;
                    aux[i][j].tinf = parametro(tmin_inf, tmax_inf);
                }
                if(m[i][j].tinf == 1){  //passa de infectado para recuperado
                    aux[i][j].saude = recuperado;
                }
                if (m[i][j].texp != 0){ //contador do tempo de exposicao
                    aux[i][j].texp--;
                }
                if (m[i][j].tinf != 0){ //contador do tempo de infeccao
                    aux[i][j].tinf--;
                }
            }
        }

        copia_matriz(aux, m);
        copia_borda(m);
        //salva_matriz(m, tempo, fp);

        //print_matriz(m, tempo, 1);     //print m[][].saude
        //print_matriz(m, tempo, 2);     //print m[][].texp
        //print_matriz(m, tempo, 3);     //print m[][].tinf

        //printf("\n\nAUXILIAR\n\n");
        //print_matriz(aux, tempo, 1);
        //print_matriz(aux, tempo, 2);
        //print_matriz(aux, tempo, 3);

        for(i=1; i<=L; i++){
            for(j=1; j<=L; j++){
                if(m[i][j].saude == exposto){ //se houver infectados ou expostos na matriz, continue
                    cont++;
                }
                else if(m[i][j].saude == infectado){
                    cont++;
                }
            }
        }
    }
    printf("\ntempo final :%d\n\n", tempo);

    //fclose(fp);
    //free(mat);
}


