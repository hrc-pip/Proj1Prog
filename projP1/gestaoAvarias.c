#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestaoAvarias.h"



// =====================================================================================
int procuraId(int idAvaria, tipoAvaria vetorAvarias[], int quantAvarias)
{
    int i, pos=-1;

    for (i = 0; i < quantAvarias; i++)
    {
        if (idAvaria == vetorAvarias[i].idAvaria)
        {
            pos = i;
            i = quantAvarias;
        }
    }

    return pos;
}


// =====================================================================================
tipoAvaria leDadosAvaria (tipoData dataBase, tipoAvaria avaria)
{
    int diasBase, diasAvaria;
    diasBase = converteDataDias(dataBase);

    avaria.localEntrega = lerInteiro("Local de Entrega do Portatil (0-RESIDENCIAS, 1-CAMPUS1, 2-CAMPUS2, 3-CAMPUS5)", RESIDENCIAS, CAMPUS5);
    avaria.tipoAvaria = lerInteiro("Tipo Avaria (1-Temporaria/2-Permanente) ", TEMPORARIA, PERMANENTE);
     do{
        avaria.dataAvaria = lerData("Qual a data do registo da Avaria (dd-mm-aaaa): ");
        diasAvaria = converteDataDias(avaria.dataAvaria);

        if( diasBase > diasAvaria){
            printf("\nERRO!! A data do registo da avaria e menor qua a data da ultima atividade do portatil - %d-%d-%d\n\n", dataBase.dia,dataBase.mes,dataBase.ano);
        }
    } while (diasBase > diasAvaria);
    avaria.dataReparacao.dia = -1;
    avaria.dataReparacao.mes = -1;
    avaria.dataReparacao.ano = -1;
    avaria.tempoDuracao = -1;

    return avaria;
}


// =====================================================================================
tipoAvaria* criarReparacao(tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int idAvaria, posAvaria, posPort, diasReparacao, diasAvaria;


    if(quantidadePortateis == 0)
    {
        printf("\n\nATENCAO: nao existem portateis inseridos\n\n");
    }
    else
    {
        if (quantAvarias == 0)
        {
            printf("\n\nATENCAO: nao existem avarias efetuadas\n\n");
        }
        else
        {

                idAvaria = lerInteiro("Id da Avaria: ", 0, 99999);

                posAvaria = procuraId(idAvaria, vetorAvarias, quantAvarias);
                if (posAvaria == -1)
                {
                    printf("\n\nATENCAO: id de avaria desconhecido\n\n");
                }
                else
                {
                    diasAvaria = converteDataDias(vetorAvarias[posAvaria].dataAvaria);
                    posPort = procuraPortatil(vetorAvarias[posAvaria].numPortatil, vetorPortateis, quantidadePortateis);
                    do{
                        vetorAvarias[posAvaria].dataReparacao = lerData("Data da Reparacao (dd-mm-aaaa): ");
                        diasReparacao = converteDataDias(vetorAvarias[posAvaria].dataReparacao);
                    }while(diasAvaria > diasReparacao);

                    vetorAvarias[posAvaria].tempoDuracao = diasReparacao - diasAvaria;

                    vetorPortateis[posPort].estado = DISPONIVEL;
                    vetorPortateis[posPort].localizacao = vetorAvarias[posAvaria].localEntrega;
                    vetorPortateis[posPort].dataUltimaAtividade = vetorAvarias[posAvaria].dataReparacao;

                    printf("\n\nReparacao efetuada com sucesso\n");

                }


        }
    }
    return vetorAvarias;
}


// =====================================================================================
tipoAvaria* criarAvaria(tipoAvaria vetorAvarias[], int *quantAvarias, tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int posPort, posAvaria, posRequisicao, diasRequisicao, diasAvaria;
    tipoAvaria *pAux = vetorAvarias;
    tipoAvaria avaria;

    if (quantidadePortateis == 0)
    {
        printf("\nAVISO: nao e possivel registar uma avaria sem portateis inseridos\n\n");
    }
    else
    {
        // ----  EFETUAR REGISTO DA AVARIA
        avaria.numPortatil = lerInteiro("Nr. Portatil ", 0, MAXPORTATEIS);
        posPort = procuraPortatil(avaria.numPortatil, vetorPortateis, quantidadePortateis);

        if (posPort == -1)
        {
            printf("\n\nERRO: o portatil nao existe\n\n");
        }
        else
        {

            if(vetorPortateis[posPort].estado == AVARIADO)
            {
                printf("\n\nAVISO: o portatil inserido ja esta avariado\n\n");
            }
            else
            {
                posRequisicao = procurarRequisicao(vetorPortateis[posPort].num, vetorRequisicoes, quantRequisicoes);

                printf("\n%s (%d) - Total de Avarias: %d\n",
                   vetorPortateis[posPort].designacao,
                   vetorPortateis[posPort].num,
                   vetorPortateis[posPort].quantTotalAvarias);

                do
                {
                    avaria.idAvaria =  lerInteiro("Id da Avaria: ", 0, 99999);

                    posAvaria = procuraId(avaria.idAvaria, vetorAvarias, *quantAvarias);
                    if (posAvaria != -1)
                    {
                        printf("\n\nAVISO: ja existe uma avaria com o mesmo id\n");
                    }
                } while(posAvaria != -1);

                if(posRequisicao == -1)
                {
                    avaria = leDadosAvaria(vetorPortateis[posPort].dataUltimaAtividade, avaria);
                }
                else
                {
                    avaria = leDadosAvaria(vetorRequisicoes[posRequisicao].dataRequisicao, avaria);


                    diasAvaria = converteDataDias(avaria.dataAvaria);
                    diasRequisicao = converteDataDias(vetorRequisicoes[posRequisicao].dataRequisicao);

                    vetorRequisicoes[posRequisicao].estadoRequisicao = CONCLUIDA;
                    vetorRequisicoes[posRequisicao].dataDevolucao = avaria.dataAvaria;
                    vetorRequisicoes[posRequisicao].localDevolucao = avaria.localEntrega;
                    vetorRequisicoes[posRequisicao].diasRequisicao = diasAvaria - diasRequisicao;
                    vetorRequisicoes[posRequisicao].valorMulta = (diasAvaria - diasRequisicao) * 10;

                    escreveFichTextoDevolucao(vetorRequisicoes, quantRequisicoes, vetorPortateis);

                }

                vetorAvarias = realloc(vetorAvarias, (*quantAvarias+1) * sizeof(tipoAvaria) );

                if (vetorAvarias == NULL)
                {
                    printf("\nERRO: falha na alocacao dinamica\n\n");
                    vetorAvarias = pAux;
                }
                else
                {
                    vetorAvarias[*quantAvarias] = avaria;
                    (*quantAvarias)++;
                    vetorPortateis[posPort].quantTotalAvarias++;
                    vetorPortateis[posPort].estado = AVARIADO;
                }
            }
        }
    }
    return vetorAvarias;
}


// =====================================================================================
void mostrarUmaAvaria(tipoAvaria avaria, tipoPortatil portatil)
{
    printf("\n\nId da Avaria.: %d\n", avaria.idAvaria);

    switch(avaria.tipoAvaria)
    {
        case TEMPORARIA:
            printf("Tipo de Avaria.: TEMPORARIA\n");
            break;
        case PERMANENTE:
            printf("Tipo de Avaria.: PERMANENTE\n");
            break;
    }

    printf("Data da Avaria.: ");
    escreverData(avaria.dataAvaria);

    if(avaria.tempoDuracao != -1)
    {

        printf("\nDuracao da Avaria.: %d dia(s)\n", avaria.tempoDuracao);
    }

        printf("\n\tPortatil (%d).: %s\t", avaria.numPortatil, portatil.designacao);

        mostrarUmPortatil(portatil);


}


// =====================================================================================
void mostrarTodasAvarias (tipoAvaria vetorAvarias[], int quantAvarias, tipoPortatil vetorPortateis[], int quantidadePortateis)
{

    int i, posPort;
    if(quantAvarias != 0)
    {
        printf("\n---- LISTAGEM das AVARIAS -----\n\n");
        for (i = 0; i < quantAvarias; i++)
        {

            posPort = procuraPortatil(vetorAvarias[i].numPortatil, vetorPortateis, quantidadePortateis);

            mostrarUmaAvaria(vetorAvarias[i], vetorPortateis[posPort]);
        }
    } else
    {
        printf("\n\tAVISO!! nao existem avarias para serem mostradas!");
    }


}


// =====================================================================================
void escreveFichBinAvarias(tipoAvaria *vetorAvarias, int quantAvarias)
{
    int controlo;
    FILE *fich;
    fich = fopen("dadosAvarias.bin", "wb");
    if (fich == NULL)
    {
        printf("Impossivel abrir ficheiro");
    }
    else
    {
        controlo = fwrite(&quantAvarias, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na gravacao dos dados\n");
        }
        else
        {
            controlo = fwrite(vetorAvarias, sizeof(tipoAvaria), quantAvarias, fich);
            if (controlo != quantAvarias)
            {
                printf("\nERRO: Falha na gravacao dos dados\n");
            }
        }

        fclose(fich);
    }
}


// =====================================================================================
tipoAvaria *leFichBinAvarias(tipoAvaria *vetorAvarias, int *quantAvarias)
{
    FILE *fich;
    fich = fopen("dadosAvarias.bin", "rb");
    if (fich == NULL)
    {
        *quantAvarias = 0;
    }
    else
    {
        fread(&(*quantAvarias), sizeof(int), 1, fich);
        vetorAvarias = realloc(vetorAvarias, (*quantAvarias) * sizeof(vetorAvarias));
        if (vetorAvarias == NULL && *quantAvarias != 0)
        {
            printf ("Erro ao reservar memoria");
            *quantAvarias = 0;
        }
        else
        {
            fread(vetorAvarias,sizeof(vetorAvarias), *quantAvarias, fich);
        }

        fclose(fich);
    }
    return vetorAvarias;
}