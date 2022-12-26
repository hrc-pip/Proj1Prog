#ifndef GESTAOALUNOS_H_INCLUDED
#define GESTAOALUNOS_H_INCLUDED

#include "funcoesGenericas.h"

#define MAXPORTATEIS 30
#define MAXSTRING 50

#define I3 1
#define I5 2
#define I7 3

#define DISPONIVEL 1
#define REQUISITADO 2
#define AVARIADO 3

#define RESIDENCIAS 0
#define CAMPUS1 1
#define CAMPUS2 2
#define CAMPUS5 3


typedef struct
{
    int num;
    char designacao[MAXSTRING];
    int processador;
    int ram;
    int estado;
    int localizacao;
    tipoData dataAquisicao;
    float valorEquipamento;
    int totalRequisicoes;
    int totalAvarias;
} tipoPortatil;

int lerQuantidadePortateis(void);
int lerDadosPortatil(char nome[]);
void acrescentaPortatil (tipoPortatil vetorAlunos[], int *quantAlunos);
int procuraPortatil (int numAluno, tipoPortatil vetorAlunos[], int quantAlunos);
void mostrarUmPortatil(tipoPortatil aluno);
void mostrarTodosPortateis(tipoPortatil vetorAlunos[], int quantAlunos);

//void lerNotas(tipoPortatil vetorAlunos[], int quantAlunos);


void gravaFicheiroBinario(tipoPortatil vetorAlunos[], int quantAlunos);
int lerFicheiroBinario(tipoPortatil vetorAlunos[], int quantAlunos);
void lerFicheiroBinarioV2(tipoPortatil vetorAlunos[], int *quantAlunos);
void gravaFicheiroTexto(tipoPortatil vetorAlunos[], int quantAlunos);


float contas(tipoPortatil vetorAlunos[], int quantAlunos, int *quantAvaliados);


#endif // GESTAOALUNOS_H_INCLUDED
