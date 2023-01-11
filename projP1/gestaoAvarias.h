#ifndef GESTAOAVARIAS_H_INCLUDED
#define GESTAOAVARIAS_H_INCLUDED

#include "funcoesGenericas.h"
#include "gestaoportateis.h"
#include "gestaoRequisicoes.h"

#define TEMPORARIA 1
#define PERMANENTE 2

typedef struct{
    int idAvaria;
    int numPortatil;
    int tipoAvaria;
    int localEntrega;
    tipoData dataAvaria;
    tipoData dataReparacao;
    int tempoDuracao;
} tipoAvaria;

int procuraId(int idAvaria, tipoAvaria vetorAvarias[], int quantAvarias);

tipoAvaria leDadosAvaria (tipoData dataAquisicao, tipoAvaria avaria);

tipoAvaria *criarAvaria(tipoAvaria vetorAvarias[], int *quantAvarias, tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis);

void mostrarUmaAvaria(tipoAvaria avaria, tipoPortatil portatil);

void mostrarTodasAvarias (tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis);

tipoAvaria *criarReparacao(tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis);

tipoAvaria *leFichBinAvarias(tipoAvaria *vetorAvarias, int *quantAvarias);

void escreveFichBinAvarias(tipoAvaria *vetorAvarias, int quantAvarias);

#endif // GESTAOAVARIAS_H_INCLUDED
