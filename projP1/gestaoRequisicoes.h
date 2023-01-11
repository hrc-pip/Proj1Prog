#ifndef GESTAORESERVAS_H_INCLUDED
#define GESTAORESERVAS_H_INCLUDED

#include "funcoesGenericas.h"
#include "gestaoportateis.h"

#define TAM_CODIGO 10     // codigo da requisição

#define ESTUDANTE 1
#define DOCENTE 2        // tipo de utente
#define TECNICOADMIN 3

#define MAX_PRAZO 30     // máximo de dias para requisição
#define MAX_RENOVACAO 7  // máximo de dias para renovar uma requisição

#define ATIVA 0         // estado da requisição
#define CONCLUIDA 1



typedef struct{
    char codigo[TAM_CODIGO];  // chave primária
    int numPortatil;   // chave estrangeira
    char nomeUtente[MAXSTRING];
    int tipoUtente;    //  [1,3]
    tipoData dataRequisicao;
    int prazoRequisicao;  // [0,30]
    int estadoRequisicao;  // [0,1]
    tipoData dataDevolucao;
    int diasRequisicao; 
    int localDevolucao; // [0,3]
    int valorMulta; 
} tipoRequisicao;


// devolve a posição no vetorRequisicoes, se não existir devolve -1
int procuraCodigo (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, char codigo[]);

// mostra todos os portateis com os dados da suas respectivas requisições
void mostrarTodosPortateis(tipoPortatil vetorPortateis[], int quantidadePortateis, tipoRequisicao vetorRequisicoes[], int quantRequi);

// le os dados necessários para a criação de uma requisição
tipoRequisicao leDadosRequi (tipoData dataAquisicao, tipoRequisicao requisicao);

// cria uma requisição
tipoRequisicao *criarRequisicao(tipoRequisicao vetorRequisicoes[], int *quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis);

// lista todas as requisições no ecrã
void mostrarTodasRequisicoes (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis);

// realiza a devolução de um portatil 
void criarDevolucao(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis, int quantRequisiAtivas);

// devolve quantas requisições estão ativas
int quantRequisiAtivas(tipoRequisicao vetorRequisicoes[], int quantRequisicoes);

// mostra uma requisição
void mostrarUmaRequisicao(tipoRequisicao requisicao, tipoPortatil portatil);

// salva os dados da requisições em um ficheiro binario
void escreveFichBinRequi(tipoRequisicao *vetorRequisicoes, int quantRequisicoes);

// lê os dados do fich binario para não perder o progresso de usos anteriores
tipoRequisicao *leFichBinRequi(tipoRequisicao *vetorRequisicoes, int *quantRequisicoes);

// lê os dados necesários para realizar uma devolução
tipoRequisicao dadosDevolucao(tipoRequisicao requisicao);

// renova o prazo de uma requisição
void renovarPrazo(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, int quantRequiAtivas);

//mostra uma requisição específica
void requisicaoSelecionada(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[]);

// calcula quantas devoluções ocorrem
int quantDevolucoes(tipoRequisicao vetorRequisicoes[], int quantRequisicoes);

// salva os dados das devoluções em um ficheiro .txt
void escreveFichTextoDevolucao (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[]);

// procura por uma requisição ativa utilizando o numPortatil
int procurarRequisicao(int numPortatil, tipoRequisicao vetorRequisicoes[], int quantRequi);

// calcula e mostra o custo médio das multas
void custoMedioMultas(tipoRequisicao vetorRequisicoes[], int quantRequi);

// calcula e mostra qual(quais) tipo(s) tem menor requisicao(oes) 
void utenteMenorQuant(tipoRequisicao vetorRequisicoes[], int quantRequi);

// calcula e exibe qual a devolução mais recente
void devolucaoMaisRecente(tipoRequisicao vetorRequisicoes[], int quantRequi, tipoPortatil vetorPortateis[]);

#endif // GESTAOREQUISICOES_H_INCLUDED
