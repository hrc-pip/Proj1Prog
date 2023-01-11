#ifndef GESTAOPORTATEIS_H_INCLUDED
#define GESTAOPORTATEIS_H_INCLUDED

#include "funcoesGenericas.h"

#define MAXPORTATEIS 30  //nº máximo de portateis
#define MAXSTRING 50

#define I3 1
#define I5 2  // opções de processadores
#define I7 3

#define MAXRAM 64

#define DISPONIVEL 1
#define REQUISITADO 2  // estados do portatil
#define AVARIADO 3

#define RESIDENCIAS 0
#define CAMPUS1 1
#define CAMPUS2 2   // locais
#define CAMPUS5 3


typedef struct
{
    int num;  // chave primária
    char designacao[MAXSTRING]; 
    int processador;   // [1,3]
    int ram;
    int estado;  // [1,3]
    int localizacao;  // [0,3]
    tipoData dataAquisicao;
    int valorEquipamento;
    int quantTotalRequisicao;
    int quantTotalAvarias;
    int quantTotalDiasRequisitados;
} tipoPortatil;


// devolve a posição no vetorPortatil, se não existir devolve -1
int procuraPortatil (int numPortatil, tipoPortatil vetorPortateis[], int quantidadePortateis);

// devolve os dados necessários para criar um novo registo de um portátil
tipoPortatil lerDadosPortatil(tipoPortatil port);

// cria um novo registo no vetorPortateis
void acrescentaPortatil (tipoPortatil vetorPortateis[], int *quantidadePortateis);

// escreve no ecrã todos os dados necessários de um portátil
void mostrarUmPortatil(tipoPortatil portatil);

// devolve o número de portateis disponíveis (.estado == DISPONIVEL)
int quantidadePortateisDisponiveis(tipoPortatil vetorPortateis[], int quantidadePortateis);

// altera somente a localizacao de um portatil
void alteraLocalizacao(tipoPortatil vetorPortateis[], int quantidadePortateis);

// guarda os dados do vetorPortateis no fich dadosPortateis.bin
void gravaFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantidadePortateis);

// lê os dados do fich binario para não perder o progresso de usos anteriores
int lerFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantidadePortateis);

// escreve a percentagem de cada processador
void percentagemProcessador(tipoPortatil vetorPortateis[], int quantidadePortateis);


#endif // GESTAOPORTATEIS_H_INCLUDED



