#ifndef GESTAOAVARIAS_H_INCLUDED
#define GESTAOAVARIAS_H_INCLUDED

#include "funcoesGenericas.h"
#include "gestaoportateis.h"
#include "gestaoRequisicoes.h"

#define TEMPORARIA 1 // tipo de avaria
#define PERMANENTE 2

typedef struct{
    int idAvaria; // chave primária
    int numPortatil;  // chave estrangeira
    int tipoAvaria; // [1,2]
    int localEntrega;  //[0,3]
    tipoData dataAvaria;  
    tipoData dataReparacao;
    int tempoDuracao;
} tipoAvaria;

// devolve a posição no vetorAvarias, se não existir devolve -1 
int procuraId(int idAvaria, tipoAvaria vetorAvarias[], int quantAvarias);

// lê os dados necessários para inserir no vetorAvarias
tipoAvaria leDadosAvaria (tipoData dataAquisicao, tipoAvaria avaria);

// cria o registo de uma avaria
tipoAvaria *criarAvaria(tipoAvaria vetorAvarias[], int *quantAvarias, tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis);

// mostra uma avaria
void mostrarUmaAvaria(tipoAvaria avaria, tipoPortatil portatil);

// lista todas as avarias ocorridas
void mostrarTodasAvarias (tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis);

// altera os dados no vetorAvarias para guardar uma reparação
tipoAvaria *criarReparacao(tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis);

// lê os dados de um ficheiro binario para não perder o progresso de usos anteriores
tipoAvaria *leFichBinAvarias(tipoAvaria *vetorAvarias, int *quantAvarias);

// salva os dados do vetor em um fich binario
void escreveFichBinAvarias(tipoAvaria *vetorAvarias, int quantAvarias);

#endif // GESTAOAVARIAS_H_INCLUDED
