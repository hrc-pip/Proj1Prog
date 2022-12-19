#ifndef GESTAOALUNOS_H_INCLUDED
#define GESTAOALUNOS_H_INCLUDED

#include "funcoesGenericas.h"

#define MAXALUNOS 100
#define MAXNOTA 20
#define MAXSTRING 50
#define MIN_NUMALUNO 1
#define MAX_NUMALUNO 9999

typedef struct
{
    int num;
    char nome[MAXSTRING];
    tipoData dataAvaliacao;
    int notaFinal;
    int totalReservas;
} tipoEstudante;

int lerQuantidadeEstudantes(void);
int lerDadosEstudante(char nome[]);
void acrescentaAluno (tipoEstudante vetorAlunos[], int *quantAlunos);
int procuraEstudante (int numAluno, tipoEstudante vetorAlunos[], int quantAlunos);
void mostrarUmAluno(tipoEstudante aluno);
void mostrarTodosAlunos(tipoEstudante vetorAlunos[], int quantAlunos);
void lerNotas(tipoEstudante vetorAlunos[], int quantAlunos);


void gravaFicheiroBinario(tipoEstudante vetorAlunos[], int quantAlunos);
int lerFicheiroBinario(tipoEstudante vetorAlunos[], int quantAlunos);
void lerFicheiroBinarioV2(tipoEstudante vetorAlunos[], int *quantAlunos);
void gravaFicheiroTexto(tipoEstudante vetorAlunos[], int quantAlunos);


float contas(tipoEstudante vetorAlunos[], int quantAlunos, int *quantAvaliados);


#endif // GESTAOALUNOS_H_INCLUDED
