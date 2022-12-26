#ifndef GESTAORESERVAS_H_INCLUDED
#define GESTAORESERVAS_H_INCLUDED

#include "funcoesGenericas.h"
#include "gestaoPortateis.h"

#define TAM_CODIGO 10

#define ESTUDANTE 1
#define DOCENTE 2
#define TECNICOADMIN 3

#define REQUISICAO_ATIVA 0
#define REQUISICAO_CONCLUIDA 1


typedef struct{
    char codigo[TAM_CODIGO];
    int numPortatil;
    char nomeUtente;
    int tipoUtente;
    tipoData dataRequisicao;
    int prazoRequisicao;
    int estadoRequisicao;
    tipoData dataDevolucao;
    int localDevolucao;
    int valorMulta;
} tipoRequisicao;


int procuraCodigo (tipoRequisicao vetorReservas[], int quantReservas, char codigo[]);
int criarReserva(tipoRequisicao vetorReservas[], int quantReservas,tipoPortatil vetorAlunos[], int quantAlunos);
void eliminarReserva(tipoRequisicao vetorReservas[], int *quantReservas,tipoPortatil vetorAlunos[], int quantAlunos);

tipoRequisicao* criarReservaDIN(tipoRequisicao vetorReservas[], int *quantReservas, tipoPortatil vetorAlunos[], int quantAlunos);
void mostrarReservas (tipoRequisicao vetorReservas[], int quantReservas, tipoPortatil vetorAlunos[], int quantAlunos);
tipoRequisicao* eliminarReservaDIN(tipoRequisicao vetorReservas[], int *quantReservas, tipoPortatil vetorAlunos[], int quantAlunos);
#endif // GESTAORESERVAS_H_INCLUDED
