#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestaoRequisicoes.h"



// =====================================================================================
void utenteMenorQuant(tipoRequisicao vetorRequisicoes[], int quantRequi)
{
    if(quantRequi != 0)
    {
        int i, somaEstud = 0, somaDoc = 0, somaAdm = 0;
        for(i = 0; i < quantRequi; i++)
        {
            switch(vetorRequisicoes[i].tipoUtente)
            {
                case ESTUDANTE:
                    somaEstud++;
                    break;

                case DOCENTE:
                    somaDoc++;
                    break;

                case TECNICOADMIN:
                    somaAdm++;
                    break;
            }
        }
        printf("\n\tTipo de Utente com menor nr. requisicoes.: ");

        if(somaEstud < somaDoc && somaDoc < somaAdm)
        {
            printf("ESTUDANTE");
        }
        else
        {
            if(somaDoc < somaAdm && somaAdm < somaEstud)
            {
                printf("DOCENTE");
            }
            else
            {
                if(somaAdm < somaEstud && somaEstud < somaDoc)
                {
                    printf("TECNICOADMIN");
                }
                else
                {
                    if (somaEstud == somaDoc) 
                    {
                        printf("ESTUDANTE E DOCENTE");
                    }
                    if (somaEstud == somaAdm) 
                    {
                        printf("ESTUDANTE E TECNICOADMIN");
                    }
                    if (somaDoc == somaAdm) 
                    {
                        printf("DOCENTE E TECNICOADMIN");
                    }
                }
            }

        }

    }
}


// =====================================================================================
void devolucaoMaisRecente(tipoRequisicao vetorRequisicoes[], int quantRequi, tipoPortatil vetorPortateis[])
{
    int i, maisRecente, aux;
    if(quantRequi != 0)
    {
        maisRecente = converteDataDias(vetorRequisicoes[0].dataDevolucao);
        for(i = 0; i < quantRequi; i++)
        {
            if(vetorRequisicoes[i].estadoRequisicao == CONCLUIDA)
            {
                aux = converteDataDias(vetorRequisicoes[i].dataDevolucao);
                if(aux > maisRecente)
                {
                    maisRecente = aux;
                }
            }
        }

        for(i = 0; i < quantRequi; i++)
        {
            if(vetorRequisicoes[i].estadoRequisicao == CONCLUIDA)
            {
                aux = converteDataDias(vetorRequisicoes[i].dataDevolucao);
                if(aux == maisRecente)
                {
                    mostrarUmaRequisicao(vetorRequisicoes[i], vetorPortateis[vetorRequisicoes[i].numPortatil]);
                }
            }

        }
    }
    else
    {
        printf("\n\tAviso: nao existem requisicoes inseridas!");
    }

}


// =====================================================================================
void custoMedioMultas(tipoRequisicao vetorRequisicoes[], int quantRequi)
{
    int i, soma = 0;
    if(quantRequi != 0)
    {
        for(i = 0; i < quantRequi; i++)
        {
            soma += vetorRequisicoes[i].valorMulta;
        }
        printf("\n\tCusto Medio das Multas.: %d", soma/quantRequi);
    }
    else
    {
        printf("\n\tAviso: nao existem requisicoes inseridas!");
    }

}


// =====================================================================================
int procuraCodigo (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, char codigo[])
{
    int i, pos = -1;

    for (i = 0; i < quantRequisicoes; i++)
    {
        if (strcmp(vetorRequisicoes[i].codigo, codigo) == 0)
        {
            pos = i;
            i = quantRequisicoes;
        }
    }
    return pos;
}


// =====================================================================================
void mostrarTodosPortateis(tipoPortatil vetorPortateis[], int quantidadePortateis, tipoRequisicao vetorRequisicoes[], int quantRequi)
{
    int i, j;

    printf("\n---- LISTAGEM dos POSTATEIS -----\n");
    for (i=0; i < quantidadePortateis; i++)
    {
        printf("\n\nPortatil: %d", i+1);
        mostrarUmPortatil(vetorPortateis[i]);
        for (j = 0; j < quantRequi; j++)
        {
            if(vetorPortateis[i].num == vetorRequisicoes[j].numPortatil)
            {
                printf("\n\t\tRequisicao:");
                printf("\n\t\t\tNome Utente.: %s\n", vetorRequisicoes[j].nomeUtente);
                switch(vetorRequisicoes[j].tipoUtente)
                {
                case ESTUDANTE:
                    printf("\t\t\tTipo de Utente.: ESTUDANTE\n");
                    break;
                case DOCENTE:
                    printf("\t\t\tTipo de Utente.: DOCENTE\n");
                    break;
                case TECNICOADMIN:
                    printf("\t\t\tTipo de Utente.: TECNICOADMIN\n");
                    break;
                }
                printf("\t\t\tPrazo da Requisicao.: %d", vetorRequisicoes[j].prazoRequisicao);
            }

        }
    }
}


// =====================================================================================
void mostrarUmaRequisicao(tipoRequisicao requisicao, tipoPortatil portatil)
{
    printf("\n\tCodigo.: %s\n", requisicao.codigo);

    printf("\tPortatil (%d).: %s\n", requisicao.numPortatil, portatil.designacao);
    printf("\tNome Utente.: %s\n", requisicao.nomeUtente);

    switch(requisicao.tipoUtente)
    {
    case ESTUDANTE:
        printf("\tTipo de Utente.: ESTUDANTE\n");
        break;
    case DOCENTE:
        printf("\tTipo de Utente.: DOCENTE\n");
        break;
    case TECNICOADMIN:
        printf("\tTipo de Utente.: TECNICOADMIN\n");
        break;
    }



    printf("\tData da Requisicao.: ");
    escreverData(requisicao.dataRequisicao);

    switch(requisicao.estadoRequisicao)
    {
    case ATIVA:
        printf("\n\tEstado da Requisicao.: ATIVA\n");
        break;
    case CONCLUIDA:
        printf("\n\tEstado da Requisicao.: CONCLUIDA\n");
        break;
    }

    if(requisicao.estadoRequisicao == CONCLUIDA)
    {
        printf("\tData da Devolucao.: ");
        escreverData(requisicao.dataDevolucao);

        printf("\n\tDuracao da Requisicao.: %d dia(s)\n", requisicao.diasRequisicao);

        switch(requisicao.localDevolucao)
        {
        case RESIDENCIAS:
            printf("\tLocal da Devolucao.: RESIDENCIAS\n");
            break;
        case CAMPUS1:
            printf("\tLocal da Devolucao.: CAMPUS1\n");
            break;
        case CAMPUS2:
            printf("\tLocal da Devolucao.: CAMPUS2\n");
            break;
        case CAMPUS5:
            printf("\tLocal da Devolucao.: CAMPUS5\n");
            break;
        }

        printf("\tValor da multa.: %d \n", requisicao.valorMulta);
    }

}


// =====================================================================================
void mostrarTodasRequisicoes (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis)
{

    int i, posPort;
    if(quantRequisicoes != 0)
    {
        printf("\n---- LISTAGEM das REQUISICOES -----");
        for (i = 0; i < quantRequisicoes; i++)
        {
            printf("\n\nRequisicao: %d", i+1);

            posPort = procuraPortatil(vetorRequisicoes[i].numPortatil, vetorPortateis, quantidadePortateis);

            mostrarUmaRequisicao(vetorRequisicoes[i], vetorPortateis[posPort]);
        }
    } else
    {
        printf("\n\tAVISO!! nao existem requisicose para serem mostrados!");
    }


}


// =====================================================================================
tipoRequisicao dadosDevolucao(tipoRequisicao requisicao)
{
    int diasRequi, diasDevo;
    diasRequi = converteDataDias(requisicao.dataRequisicao);

    requisicao.estadoRequisicao = CONCLUIDA;

    requisicao.localDevolucao = lerInteiro("Local da Devolucao (0-RESIDENCIAS, 1-CAMPUS1, 2-CAMPUS2, 3-CAMPUS5)", RESIDENCIAS, CAMPUS5);
    do{
        requisicao.dataDevolucao = lerData("Data de Devolucao (dd-mm-aaaa): ");
        diasDevo = converteDataDias(requisicao.dataDevolucao);
        if(diasRequi > diasDevo)
        {
            printf("ERRO!! A data de devolucao inserida e menor que a data de requisicao\n");
        }
    }while(diasRequi > diasDevo);

    requisicao.diasRequisicao = diasDevo - diasRequi;

    if(requisicao.diasRequisicao <= requisicao.prazoRequisicao)
    {
        requisicao.valorMulta = 0;
    }
    else
    {
        requisicao.valorMulta = (requisicao.diasRequisicao - requisicao.prazoRequisicao) * 10; // cada dia é 10€ de multa
    }

    return requisicao;
}


// =====================================================================================
void criarDevolucao(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis, int quantRequisiAtivas)
{
    char codigo[TAM_CODIGO];

    int posRequisicao, posPort;


    if(quantidadePortateis == 0)
    {
        printf("\n\nATENCAO: nao existem portateis inseridos\n\n");
    }
    else
    {
        if (quantRequisicoes == 0)
        {
            printf("\n\nATENCAO: nao existem requisicoes efetuadas\n\n");
        }
        else
        {
            if(quantRequisiAtivas == 0)
            {
                printf("\n\nATENCAO: nao existem requisicoes ativas\n\n");
            }
            else
            {
                lerString("\nIndique o codigo da requisicao a devolver: ", codigo, TAM_CODIGO);

                posRequisicao = procuraCodigo(vetorRequisicoes, quantRequisicoes, codigo);
                if (posRequisicao == -1)
                {
                    printf("\n\nATENCAO: codigo de requisicao desconhecido\n\n");
                }
                else
                {
                    posPort = procuraPortatil(vetorRequisicoes[posRequisicao].numPortatil, vetorPortateis, quantidadePortateis);

                    vetorRequisicoes[posRequisicao] = dadosDevolucao(vetorRequisicoes[posRequisicao]);

                    vetorPortateis[posPort].estado = DISPONIVEL;
                    vetorPortateis[posPort].localizacao = vetorRequisicoes[posRequisicao].localDevolucao;
                    vetorPortateis[posPort].dataUltimaAtividade = vetorRequisicoes[posRequisicao].dataDevolucao;
                    vetorPortateis[posPort].quantTotalDiasRequisitados += vetorRequisicoes[posRequisicao].diasRequisicao;



                    escreveFichTextoDevolucao(vetorRequisicoes,quantRequisicoes,vetorPortateis);

                    printf("\n\nDevolucao efetuada com sucesso\n");
                    printf("\n Dias requisitado: %d   - -   multa a pagar: %d    - -  prazo: %d", vetorRequisicoes[posRequisicao].diasRequisicao, vetorRequisicoes[posRequisicao].valorMulta, vetorRequisicoes[posRequisicao].prazoRequisicao);

                }
            }

        }
    }

}


// =====================================================================================
int quantDevolucoes(tipoRequisicao vetorRequisicoes[], int quantRequisicoes)
{
    int i, quantDev = 0;
    for(i = 0; i < quantRequisicoes; i++)
    {
        if(vetorRequisicoes[i].estadoRequisicao == CONCLUIDA)
        {
            quantDev++;
        }
    }
    return quantDev;
}


// =====================================================================================
void escreveFichTextoDevolucao (tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[])
{
    FILE *fich; int i;
    fich = fopen("devolucoes.txt","w");
    if (fich == NULL)
    {
        printf("\nErro abrir ficheiro");
    }
    else
    {
        fprintf(fich,"Quantidade De Devolucoes.: %d\n\n", quantDevolucoes(vetorRequisicoes, quantRequisicoes));
        for (i = 0; i < quantRequisicoes; i++)
        {
            if(vetorRequisicoes[i].estadoRequisicao == CONCLUIDA)
            {
                fprintf(fich,"\tCodigo da Requisicao.: %s\n",vetorRequisicoes[i].codigo);
                fprintf(fich,"\t\tNome Utente.: %s\n",vetorRequisicoes[i].nomeUtente);
                switch(vetorRequisicoes[i].tipoUtente)
                {
                case ESTUDANTE:
                    fprintf(fich,"\t\tTipo de Utente.: ESTUDANTE\n");
                    break;
                case DOCENTE:
                    fprintf(fich,"\t\tTipo de Utente.: DOCENTE\n");
                    break;
                case TECNICOADMIN:
                    fprintf(fich,"\t\tTipo de Utente.: TECNICOADMIN\n");
                    break;
                }
                fprintf(fich,"\t\tData de Requisicao.: %d-%d-%d\n",vetorRequisicoes[i].dataRequisicao.dia, vetorRequisicoes[i].dataRequisicao.mes, vetorRequisicoes[i].dataRequisicao.ano);
                fprintf(fich,"\t\tPrazo da Requisicao.: %d dia(s)\n",vetorRequisicoes[i].prazoRequisicao);
                switch(vetorRequisicoes[i].estadoRequisicao)
                {
                case ATIVA:
                    fprintf(fich,"\t\tEstado da Requisicao.: ATIVA\n");
                    break;
                case CONCLUIDA:
                    fprintf(fich,"\t\tEstado da Requisicao.: CONCLUIDA\n");
                    break;
                }
                fprintf(fich,"\t\tData de Devolucao.: %d-%d-%d\n",vetorRequisicoes[i].dataDevolucao.dia, vetorRequisicoes[i].dataDevolucao.mes, vetorRequisicoes[i].dataDevolucao.ano);
                fprintf(fich,"\t\tDuracao da Requisicao.: %d dia(s)\n",vetorRequisicoes[i].diasRequisicao);
                switch(vetorRequisicoes[i].localDevolucao)
                {
                case RESIDENCIAS:
                    fprintf(fich,"\t\tLocal da Devolucao.: RESIDENCIAS\n");
                    break;
                case CAMPUS1:
                    fprintf(fich,"\t\tLocal da Devolucao.: CAMPUS1\n");
                    break;
                case CAMPUS2:
                    fprintf(fich,"\t\tLocal da Devolucao.: CAMPUS2\n");
                    break;
                case CAMPUS5:
                    fprintf(fich,"\t\tLocal da Devolucao.: CAMPUS5\n");
                    break;
                }
                fprintf(fich,"\t\tValor da Multa.: %d \n",vetorRequisicoes[i].valorMulta);
                fprintf(fich,"\t\tNr. Portatil.: %d \n",vetorRequisicoes[i].numPortatil);
                switch(vetorPortateis[vetorRequisicoes[i].numPortatil].processador)
                {
                case I3:
                    fprintf(fich,"\t\t\tProcessador.: I3\n");
                    break;
                case I5:
                    fprintf(fich,"\t\t\tProcessador.: I5\n");
                    break;
                case I7:
                    fprintf(fich,"\t\t\tProcessador.: I7\n");
                    break;
                }
                fprintf(fich,"\t\t\tMemoria RAM.: %d Gb\n\n",vetorPortateis[vetorRequisicoes[i].numPortatil].ram);
            }
        }
        fclose(fich);
    }
}


// =====================================================================================
tipoRequisicao leDadosRequi (tipoData dataUltimaAtividade, tipoRequisicao requisicao)
{
    int diasUltimaAtividade, diasRequisicao;
    diasUltimaAtividade = converteDataDias(dataUltimaAtividade);

    lerString("Nome do Utente: ", requisicao.nomeUtente, MAXSTRING);
    requisicao.tipoUtente = lerInteiro("Tipo Utente (1-Estudante/2-Docente/3-TecnicoAdmin) ", ESTUDANTE, TECNICOADMIN);
     do{
        requisicao.dataRequisicao = lerData("Qual a data de Requisicao (dd-mm-aaaa): ");
        diasRequisicao = converteDataDias(requisicao.dataRequisicao);

        if( diasUltimaAtividade > diasRequisicao){
            printf("\nERRO!! A data de requisicao e menor que a data da ultima atividade do portatil  - %d-%d-%d\n\n",dataUltimaAtividade.dia,dataUltimaAtividade.mes,dataUltimaAtividade.ano );
        }
    } while (diasUltimaAtividade > diasRequisicao);
    requisicao.prazoRequisicao = lerInteiro("\nDias do Prazo de Requisicao ", 0, MAX_PRAZO);
    requisicao.estadoRequisicao = ATIVA;
    requisicao.dataDevolucao.dia = 01;
    requisicao.dataDevolucao.mes = 01;
    requisicao.dataDevolucao.ano = MIN_ANO;
    requisicao.localDevolucao = -1;
    requisicao.diasRequisicao = 0;
    requisicao.valorMulta = 0;

    return requisicao;
}


// =====================================================================================
tipoRequisicao* criarRequisicao(tipoRequisicao vetorRequisicoes[], int *quantRequisicoes, tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int posPort, posRequisicao;
    tipoRequisicao *pAux = vetorRequisicoes;
    tipoRequisicao requisicao;

    if (quantidadePortateis == 0)
    {
        printf("\nAVISO: nao e possivel efetuar a requisicao porque nao existem portateis\n\n");
    }
    else
    {

        // ----  EFETUAR REQUISICAO
        requisicao.numPortatil = lerInteiro("Nr. Portatil ", 0, MAXPORTATEIS);
        posPort = procuraPortatil(requisicao.numPortatil, vetorPortateis, quantidadePortateis);

        if (posPort == -1)
        {
            printf("\n\nERRO: o portatil nao existe\n\n");
        }
        else
        {
            if(vetorPortateis[posPort].estado != DISPONIVEL)
            {
                printf("\nAVISO!! O portatil requisitado nao esta disponivel");
            } else
            {

                printf("\n%s (%d) - Total de Reservas: %d\n",
                   vetorPortateis[posPort].designacao,
                   vetorPortateis[posPort].num,
                   vetorPortateis[posPort].quantTotalRequisicao);

                lerString("Codigo Reserva: ", requisicao.codigo, TAM_CODIGO);
                posRequisicao = procuraCodigo(vetorRequisicoes, *quantRequisicoes, requisicao.codigo);
                if (posRequisicao != -1)
                {
                    printf("\n\nERRO: nao e possivel criar a requisicao pois ja existe uma com o mesmo codigo\n\n");
                }
                else
                {

                    requisicao = leDadosRequi(vetorPortateis[posPort].dataUltimaAtividade, requisicao);


                    vetorRequisicoes = realloc(vetorRequisicoes, (*quantRequisicoes+1) * sizeof(tipoRequisicao) );

                    if (vetorRequisicoes == NULL)
                    {
                        printf("\nERRO: falha na alocacao dinamica\n\n");
                        vetorRequisicoes = pAux;
                    }
                    else
                    {
                        vetorRequisicoes[*quantRequisicoes] = requisicao;
                        (*quantRequisicoes)++;
                        vetorPortateis[posPort].quantTotalRequisicao++;
                        vetorPortateis[posPort].estado = REQUISITADO;
                    }

                }
            }
        }

    }
    return vetorRequisicoes;
}


// =====================================================================================
int quantRequisiAtivas(tipoRequisicao vetorRequisicoes[], int quantRequisicoes)
{
    int quantAtiva = 0, i;
    for(i = 0; i < quantRequisicoes; i++)
    {
        if(vetorRequisicoes[i].estadoRequisicao == ATIVA)
            quantAtiva++;
    }
    return quantAtiva;
}


// =====================================================================================
void escreveFichBinRequi(tipoRequisicao *vetorRequisicoes, int quantRequisicoes)
{
    int controlo;
    FILE *fich;
    fich = fopen("dadosRequisicoes.bin", "wb");
    if (fich == NULL)
    {
        printf("Impossivel abrir ficheiro");
    }
    else
    {
        controlo = fwrite(&quantRequisicoes, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na gravacao dos dados\n");
        }
        else
        {
            controlo = fwrite(vetorRequisicoes, sizeof(tipoRequisicao), quantRequisicoes, fich);
            if (controlo != quantRequisicoes)
            {
                printf("\nERRO: Falha na gravacao dos dados\n");
            }
        }

        fclose(fich);
    }
}


// =====================================================================================
tipoRequisicao *leFichBinRequi(tipoRequisicao *vetorRequisicoes, int *quantRequisicoes)
{
    FILE *fich;
    fich = fopen("dadosRequisicoes.bin", "rb");
    if (fich == NULL)
    {
        *quantRequisicoes = 0;
    }
    else
    {
        fread(&(*quantRequisicoes), sizeof(int), 1, fich);
        vetorRequisicoes = realloc(vetorRequisicoes, (*quantRequisicoes) * sizeof(tipoRequisicao));
        if (vetorRequisicoes == NULL && *quantRequisicoes != 0)
        {
            printf ("Erro ao reservar memoria");
            *quantRequisicoes = 0;
        }
        else
        {
            fread(vetorRequisicoes,sizeof(tipoRequisicao), *quantRequisicoes, fich);
        }

        fclose(fich);
    }
    return vetorRequisicoes;
}


// =====================================================================================
void renovarPrazo(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, int quantRequiAtivas)
{
    char codigo[TAM_CODIGO];
    int posRequisicao, dataAtualDias, dataRequisicaoDias, deltaT;
    tipoData dataAtual;

    if (quantRequisicoes == 0)
    {
        printf("\nAVISO!! nao existem requisicoes");
    }
    else
    {
        if ( quantRequiAtivas == 0)
        {
            printf("\nAVISO!! nao existem requisicoes ativas");
        }
        else
        {

            lerString("\nIndique o codigo da requisicao a renovar: ", codigo, TAM_CODIGO);

            posRequisicao = procuraCodigo(vetorRequisicoes, quantRequisicoes, codigo);
            if (posRequisicao == -1)
            {
                printf("\n\nATENCAO: codigo de requisicao desconhecido\n\n");
            }
            else
            {
                if(vetorRequisicoes[posRequisicao].estadoRequisicao != ATIVA) 
                {
                    printf("\n\tERRO! nao é possivel aumentar o prazo de uma requisicao que ja foi concluida");
                }
                else
                {

                    dataRequisicaoDias = converteDataDias(vetorRequisicoes[posRequisicao].dataRequisicao);

                    do {
                    dataAtual = lerData("Data de hoje (dd-mm-aaaa): ");
                    dataAtualDias = converteDataDias(dataAtual);
                    if(dataAtualDias < dataRequisicaoDias)
                    {
                        printf("\nERRO!! a data atual nao pode ser inferior a data de requisicao");
                    }
                    } while(dataAtualDias < dataRequisicaoDias);

                    deltaT = dataAtualDias - dataRequisicaoDias;

                    if(deltaT <= vetorRequisicoes[posRequisicao].prazoRequisicao)
                    {
                        vetorRequisicoes[posRequisicao].prazoRequisicao += MAX_RENOVACAO; // so acrescentar o prazo se o ele ainda estiver dentro do prazo
                        printf("\nPrazo atualizado com sucesso!");
                    }
                    else
                    {
                        printf("\nAVISO! nao foi possivel renovar a requisicao, pois ja passou o prazo");
                    }
                }
            }
        }
    }
}


// =====================================================================================
void requisicaoSelecionada(tipoRequisicao vetorRequisicoes[], int quantRequisicoes, tipoPortatil vetorPortateis[])
{
    char codigo[TAM_CODIGO];
    int posRequisicao;

    if (quantRequisicoes == 0)
    {
        printf("\nAVISO!! nao existem requisicoes");
    }
    else
    {
        lerString("\nIndique o codigo da requisicao : ", codigo, TAM_CODIGO);

        posRequisicao = procuraCodigo(vetorRequisicoes, quantRequisicoes, codigo);
        if (posRequisicao == -1)
        {
            printf("\n\nATENCAO: codigo de requisicao desconhecido\n\n");
        }
        else
        {
            mostrarUmaRequisicao(vetorRequisicoes[posRequisicao], vetorPortateis[vetorRequisicoes[posRequisicao].numPortatil]);
            printf("\n\t\tPortatil: \n");
            switch(vetorPortateis[vetorRequisicoes[posRequisicao].numPortatil].estado)
            {
            case DISPONIVEL:
                printf("\t\t\tEstado.: DISPONIVEL\n");
                break;
            case REQUISITADO:
                printf("\t\t\tEstado.: REQUISITADO\n");
                break;
            case AVARIADO:
                printf("\t\t\tEstado.: AVARIADO\n");
                break;
            }
            printf("\t\t\tQuantidade Total de dias Requisitado: %d \n", vetorPortateis[vetorRequisicoes[posRequisicao].numPortatil].quantTotalDiasRequisitados);

        }

    }
}


// =====================================================================================
int procurarRequisicao(int numPortatil, tipoRequisicao vetorRequisicoes[], int quantRequi)
{
    int i, pos=-1;
    for (i = 0; i < quantRequi; i++)
    {
        if(vetorRequisicoes[i].numPortatil == numPortatil && vetorRequisicoes[i].estadoRequisicao == ATIVA) // procura por uma requisicao ativa utilizando o numPortatil
        {
            pos = i;
            i = quantRequi;
        }
    }
    return pos;
}
