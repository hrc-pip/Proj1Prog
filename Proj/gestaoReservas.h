#ifndef GESTAORESERVAS_H_INCLUDED
#define GESTAORESERVAS_H_INCLUDED

#include "funcoesGenericas.h"
#include "gestaoAlunos.h"

#define MAX_RESERVAS 50
#define TAM_CODIGO 10
#define ALMOCO 1
#define JANTAR 2

typedef struct{
    char codigo[TAM_CODIGO];
    int numAluno;
    tipoData dataRefeicao;
    int tipoRefeicao;
} tipoReserva;

int procuraCodigo (tipoReserva vetorReservas[], int quantReservas, char codigo[]);
int criarReserva(tipoReserva vetorReservas[], int quantReservas,tipoEstudante vetorAlunos[], int quantAlunos);
void eliminarReserva(tipoReserva vetorReservas[], int *quantReservas,tipoEstudante vetorAlunos[], int quantAlunos);
#endif // GESTAORESERVAS_H_INCLUDED
