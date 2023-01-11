#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "funcoesGenericas.h"
#include "gestaoportateis.h"
#include "gestaoRequisicoes.h"
#include "gestaoAvarias.h"


char menu (int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas); // menu principal

char menuRequisicoes (int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas);  // menu para as requisições

char menuAvarias (int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas);

int main()
{
    int quantRequiAtivas, quantPortateisDisponiveis, quantidadePortateis = 0, quantRequisicoes = 0, quantAvarias = 0;

    char opcao, opcaoRequi, opcaoAvaria;

    tipoPortatil vetorPortateis[MAXPORTATEIS];  // vetor para controlar os portateis

    tipoRequisicao *vetorRequisicoes = NULL;  // vetor dinâmico para controlar as requisições
    tipoAvaria *vetorAvarias = NULL;  // vetor dinâmico para controlar as avarias


    quantidadePortateis = lerFicheiroBinarioPortatil(vetorPortateis, quantidadePortateis); // variavel com a quantidade de Portateis varia segundo o ficheiro

    // inicializar os vetores dinamicos lendo os ficheiros binarios

    vetorRequisicoes = leFichBinRequi(vetorRequisicoes, &quantRequisicoes); 
    vetorAvarias = leFichBinAvarias(vetorAvarias, &quantAvarias);

    do
    {
        quantPortateisDisponiveis = quantidadePortateisDisponiveis(vetorPortateis,quantidadePortateis);   // função para calcular a quantidade de portateis cujo o estado é DISPONIVEL

        quantRequiAtivas = quantRequisiAtivas(vetorRequisicoes, quantRequisicoes);  // função para calcular a quantidade de requisições ativas

        opcao = menu(quantidadePortateis, quantPortateisDisponiveis, quantRequisicoes, quantRequiAtivas);

        switch (opcao)
        {
        case 'A':  // adicionar portatil
            acrescentaPortatil(vetorPortateis, &quantidadePortateis);
            break;

        case 'M':  // mostrar todos os portáteis
            mostrarTodosPortateis(vetorPortateis, quantidadePortateis, vetorRequisicoes, quantRequisicoes);          
            break;

        case 'L':  // mudar a localização de um portatil
            alteraLocalizacao(vetorPortateis, quantidadePortateis);
            break;

        case 'P': // calcula a percentagem de portateis com cada tipo de processador 
            percentagemProcessador(vetorPortateis, quantidadePortateis);
            break;

        case 'F':  // ao fechar o programa salvar as alterações em um ficheiro binário
            gravaFicheiroBinarioPortatil(vetorPortateis, quantidadePortateis);
            break;

        case 'R':  // menu requisições
            do
            {
                quantRequiAtivas = quantRequisiAtivas(vetorRequisicoes, quantRequisicoes);
                quantPortateisDisponiveis = quantidadePortateisDisponiveis(vetorPortateis,quantidadePortateis);

                opcaoRequi = menuRequisicoes(quantidadePortateis, quantPortateisDisponiveis, quantRequisicoes, quantRequiAtivas);

                switch (opcaoRequi)
                {

                case 'C':   // criar requisição
                    vetorRequisicoes = criarRequisicao(vetorRequisicoes, &quantRequisicoes, vetorPortateis, quantidadePortateis);

                    break;

                case 'M':  // mostrar todas as requisições
                    mostrarTodasRequisicoes(vetorRequisicoes, quantRequisicoes, vetorPortateis, quantidadePortateis);

                    break;

                case 'D':   // devolver um portatil
                    criarDevolucao( vetorRequisicoes, quantRequisicoes, vetorPortateis, quantidadePortateis,  quantRequiAtivas);

                    break;                

                case 'S': // mostrar dados de uma requisição selecionada pelo user
                    requisicaoSelecionada(vetorRequisicoes, quantRequisicoes, vetorPortateis);
                    break;

                case 'R': // aumentar o prazo de uma requisição por 7
                    renovarPrazo(vetorRequisicoes, quantRequisicoes, quantRequiAtivas);
                    break;

                case 'V':  // calcula o custo medio de multas, tendo em conta que as requisições ativas tem valorMulta = 0
                    custoMedioMultas(vetorRequisicoes, quantRequisicoes);
                    break;

                case 'W':  // compara as datas de Devolução para ver qual tem o maior valor em dias, que seria a mais recente
                    devolucaoMaisRecente(vetorRequisicoes,quantRequisicoes, vetorPortateis);
                    break;

                case 'U': // escreve qual(quais) tipo(s) de utente tem o menor numero de requisições 
                    utenteMenorQuant(vetorRequisicoes,quantRequisicoes);
                    break;

                case 'F':  // salvar dados do vetor requisicoes em um ficheiro binario
                    escreveFichBinRequi(vetorRequisicoes, quantRequisicoes);
                    break;

                default:
                    printf("\nERRO: opcao desconhecida\n");
                }

            } while (opcaoRequi != 'F');

            break;

        case 'V':  //menu avarias
            do
            {
                quantRequiAtivas = quantRequisiAtivas(vetorRequisicoes, quantRequisicoes);
                quantPortateisDisponiveis = quantidadePortateisDisponiveis(vetorPortateis,quantidadePortateis);

                opcaoAvaria = menuAvarias(quantidadePortateis, quantPortateisDisponiveis, quantRequisicoes, quantRequiAtivas);

                switch (opcaoAvaria)
                {

                case 'A':  // adicionar uma avaria
                    vetorAvarias = criarAvaria(vetorAvarias,&quantAvarias,vetorRequisicoes,quantRequisicoes,vetorPortateis,quantidadePortateis);
                    break;

                case 'R':  // adicionar uma reparação
                    vetorAvarias = criarReparacao(vetorAvarias,quantAvarias,vetorPortateis,quantidadePortateis);
                    break;

                case 'L':  // listar todas as avarias
                    mostrarTodasAvarias(vetorAvarias,quantAvarias,vetorPortateis,quantidadePortateis);
                    break;

                case 'F': // salva os dados do vetorAvarias em um ficheiro binário
                    escreveFichBinAvarias(vetorAvarias, quantAvarias);

                    break;

                default:
                    printf("\nERRO: opcao desconhecida\n");
                }

            } while (opcaoAvaria != 'F');
            break;

        default:
            printf("\nERRO: opcao desconhecida\n");
        }
    }
    while (opcao != 'F');


    free(vetorRequisicoes);  // libertar a memória do vetorRequisicoes

    free(vetorAvarias); // libertar memória do vetorAvarias

    return 0;
}



//                                   MENU PRINCIPAL
// =====================================================================================
char menu (int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas)
{
    char opcao;

    printf("\n\n********************** MENU PRINCIPAL ********************** \n\n");
    printf("Numero de Portateis Inseridos: %d\n", quantidadePortateis);
    printf("Portateis Disponiveis: %d \n", quantPortateisDisponiveis);
    printf("Quantidade de Requisicoes Ativas: %d \n", quantRequiAtivas);
    printf("Quantidade de Requisicoes Totais: %d \n", quantRequiTotais);
    printf("A - Acrescenta Portatil\nM - Mostrar Dados\n");
    printf("L - Alterar Localizacao do Portatil\nP - Percentagem de portateis com cada tipo de processador\n");
    printf("V - Menu de Avarias\nR - Menu de Requisicoes\n");
    printf("F - Fim\n");
    printf("\t\tOPCAO -> ");

    scanf("%c", &opcao);
    limparBuffer();

    opcao = toupper(opcao);

    return opcao;
}


//                                   MENU REQUISIÇÕES
// =====================================================================================
char menuRequisicoes(int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas)
{
    char opcao;

    printf("\n\n********************** MENU REQUISICOES ********************** \n\n");
    printf("Numero de Portateis Inseridos: %d\n", quantidadePortateis);
    printf("Portateis Disponiveis: %d \n", quantPortateisDisponiveis);
    printf("Quantidade de Requisicoes Ativas: %d \n", quantRequiAtivas);
    printf("Quantidade de Requisicoes Totais: %d \n", quantRequiTotais);
    printf("C - Criar Requisicao\nM - Mostrar Dados\n");
    printf("D - Devolver um portatil\nS - Selecionar uma requisicao\n");
    printf("R - Renovar Prazo (7 dias)\nV - Valor medio das multas\n");
    printf("W - Devolucao(oes) mais recente(s)\nU - Tipo Utente com menor quantidade de requisicoes\n");
    printf("F - Voltar\n");
    printf("\t\tOPCAO -> ");

    scanf("%c", &opcao);
    limparBuffer();

    opcao = toupper(opcao);

    return opcao;
}


//                                   MENU AVARIAS
// =====================================================================================
char menuAvarias (int quantidadePortateis, int quantPortateisDisponiveis, int quantRequiTotais, int quantRequiAtivas)
{
    char opcao;

    printf("\n\n********************** MENU AVARIAS ********************** \n\n");
    printf("Numero de Portateis Inseridos: %d\n", quantidadePortateis);
    printf("Portateis Disponiveis: %d \n", quantPortateisDisponiveis);
    printf("Quantidade de Requisicoes Ativas: %d \n", quantRequiAtivas);
    printf("Quantidade de Requisicoes Totais: %d \n", quantRequiTotais);
    printf("A - Avaria\nR - Reparacao\n");
    printf("L - Listar Avarias\n");
    printf("F - Voltar\n");
    printf("\t\tOPCAO -> ");

    scanf("%c", &opcao);
    limparBuffer();

    opcao = toupper(opcao);

    return opcao;
}


