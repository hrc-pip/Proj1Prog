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
#define REQUISITADO 2  // estados do portátil
#define AVARIADO 3

#define RESIDENCIAS 0
#define CAMPUS1 1
#define CAMPUS2 2   // locais
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
    int valorEquipamento;
    int totalRequisicao;
    int totalAvarias;
} tipoPortatil;


int lerQuantidadePortateis(void);

tipoPortatil lerDadosPortatil();

void acrescentaPortatil (tipoPortatil vetorPortateis[], int *quantPorts);

int procuraPortatil (int numAluno, tipoPortatil vetorPortateis[], int quantPorts);

void mostrarUmPortatil(tipoPortatil portatil);

void mostrarTodosPortateis(tipoPortatil vetorPortateis[], int quantPorts);

int quantPortateisDisponiveis(tipoPortatil vetorPortateis[], int quantPorts);

void alteraLocalizacao(tipoPortatil vetorPortateis[], int quantPorts);

void gravaFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantPorts);

int lerFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantPorts);


#endif // GESTAOPORTATEIS_H_INCLUDED



