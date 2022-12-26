#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestaoRequisicoes.h"


void mostrarReservas (tipoReserva vetorReservas[], int quantReservas, tipoEstudante vetorAlunos[], int quantAlunos)
{
    int i, posAluno;

    if (quantReservas == 0)
    {
        printf("\nATENCAO: nao existem reservas criadas\n\n");
    }
    else
    {
        for (i=0; i < quantReservas; i++)
        {
            printf("\n\nCodigo: %s\n", vetorReservas[i].codigo);
            posAluno = procuraEstudante(vetorReservas[i].numPortatil, vetorAlunos, quantAlunos);
            printf("Aluno (%d): %s\n", vetorReservas[i].numPortatil, vetorAlunos[posAluno].nome);
            printf("Data da refeicao: ");
            escreverData(vetorReservas[i].dataDevolucao);
            if (vetorReservas[i].tipoUtente == ESTUDANTE)
            {
                printf("\nTipo: Almoco\n");
            }
            else
            {
                printf("\nTipo: Jantar\n");
            }
        }
    }
}


void eliminarReserva(tipoRequisicao vetorReservas[], int *quantReservas, tipoPortatil vetorAlunos[], int quantAlunos)
{
    char codigo[TAM_CODIGO];
    int posReserva, posAluno, i;

    if(quantAlunos == 0)
    {
        printf("\n\nATENCAO: nao existem alunos inscritos\n\n");
    }
    else
    {
        if (*quantReservas == 0)
        {
            printf("\n\nATENCAO: nao existe reservas efetuadas\n\n");
        }
        else
        {
            lerString("\nIndique o codigo da reserva a eliminar: ", codigo, TAM_CODIGO);
            posReserva = procuraCodigo(vetorReservas, *quantReservas, codigo);
            if (posReserva == -1)
            {
                printf("\n\nATENCAO: codigo de reserva desconhecido\n\n");
            }
            else
            {
                posAluno = procuraEstudante(vetorReservas[posReserva].numPortatil, vetorAlunos, quantAlunos);
                vetorAlunos[posAluno].totalAvarias--;

                for (i=posReserva; i < *quantReservas-1; i++)
                {
                    vetorReservas[i] = vetorReservas[i+1];
                }
                (*quantReservas)--;
                printf("\n\nCancelamento da reserva efetuado com sucesso\n\n");
            }
        }
    }
}

tipoReserva* eliminarReservaDIN(tipoReserva vetorReservas[], int *quantReservas, tipoEstudante vetorAlunos[], int quantAlunos)
{
    char codigo[TAM_CODIGO];
    int posReserva, posAluno, i;
    tipoReserva *pAux = vetorReservas;

    if(quantAlunos == 0)
    {
        printf("\n\nATENCAO: nao existem alunos inscritos\n\n");
    }
    else
    {
        if (*quantReservas == 0)
        {
            printf("\n\nATENCAO: nao existe reservas efetuadas\n\n");
        }
        else
        {
            lerString("\nIndique o codigo da reserva a eliminar: ", codigo, TAM_CODIGO);
            posReserva = procuraCodigo(vetorReservas, *quantReservas, codigo);
            if (posReserva == -1)
            {
                printf("\n\nATENCAO: codigo de reserva desconhecido\n\n");
            }
            else
            {
                posAluno = procuraEstudante(vetorReservas[posReserva].numPortatil, vetorAlunos, quantAlunos);
                vetorAlunos[posAluno].totalReservas--;

                for (i=posReserva; i < *quantReservas-1; i++)
                {
                    vetorReservas[i] = vetorReservas[i+1];
                }
                (*quantReservas)--;

                vetorReservas = realloc(vetorReservas, *quantReservas * sizeof(tipoReserva));
                if (vetorReservas == NULL && *quantReservas > 0)
                {
                    vetorReservas = pAux;
                }
                printf("\n\nCancelamento da reserva efetuado com sucesso\n\n");
            }
        }
    }
    return vetorReservas;
}







int procuraCodigo (tipoRequisicao vetorReservas[], int quantReservas, char codigo[])
{
    int i, pos = -1;

    for (i=0; i < quantReservas; i++)
    {
        if (strcmp(vetorReservas[i].codigo, codigo) == 0)
        {
            pos = i;
            i = quantReservas;
        }
    }
    return pos;
}


tipoRequisicao* criarReservaDIN(tipoRequisicao  vetorReservas[], int *quantReservas, tipoPortatil vetorAlunos[], int quantAlunos)
{
    int posAluno, posReserva;
    tipoRequisicao *pAux = vetorReservas;
    tipoRequisicao reserva;

    if (quantAlunos == 0)
    {
        printf("\nAVISO: nao e possivel efetuar a reserva porque nao existem alunos inscritos\n\n");
    }
    else
    {

        // ----  EFETUAR RESERVA
        reserva.numPortatil = lerInteiro("Nr. Aluno ", MIN_NUMALUNO, MAX_NUMALUNO);
        posAluno = procuraEstudante(reserva.numPortatil, vetorAlunos, quantAlunos);
        if (posAluno == -1)
        {
            printf("\n\nERRO: o aluno nao existe\n\n");
        }
        else
        {
            printf("\n%s (%d) - Total de Reservas: %d\n",
                   vetorAlunos[posAluno].nome,
                   vetorAlunos[posAluno].num,
                   vetorAlunos[posAluno].totalReservas);

            lerString("Codigo Reserva: ", reserva.codigo, TAM_CODIGO);
            posReserva = procuraCodigo(vetorReservas, *quantReservas, reserva.codigo);
            if (posReserva != -1)
            {
                printf("\n\nERRO: nao e possivel criar a reserva pois ja existe uma com o mesmo codigo\n\n");
            }
            else
            {
                reserva.dataRequisicao = lerData("Data da refeicao ");
                reserva.tipoUtente = lerInteiro("\nTipo Refeicao (1-Almoco/2-Jantar) ", ESTUDANTE, TECNICOADMIN);
                vetorReservas = realloc(vetorReservas, (*quantReservas+1) * sizeof(tipoReserva) );
                if (vetorReservas == NULL)
                {
                    printf("\nERRO: falha na alocacao dinamica\n\n");
                    vetorReservas = pAux;
                }
                else
                {
                    vetorReservas[*quantReservas] = reserva;
                    (*quantReservas)++;
                    vetorAlunos[posAluno].totalReservas++;
                }
            }
        }

    }
    return vetorReservas;
}

int criarReserva(tipoRequisicao vetorReservas[], int quantReservas, tipoPortatil vetorAlunos[], int quantAlunos)
{
    int numAluno, posAluno, posReserva;

    if (quantAlunos == 0)
    {
        printf("\nAVISO: nao e possivel efetuar a reserva porque nao existem alunos inscritos\n\n");
    }
    else
    {

            // ----  EFETUAR RESERVA
            numAluno = lerInteiro("Nr. Aluno ", RESIDENCIAS, CAMPUS5);
            posAluno = procuraEstudante(numAluno, vetorAlunos, quantAlunos);
            if (posAluno == -1)
            {
                printf("\n\nERRO: o aluno nao existe\n\n");
            }
            else
            {
                printf("\n%s (%d) - Total de Reservas: %d\n",
                       vetorAlunos[posAluno].nome,
                       vetorAlunos[posAluno].num,
                       vetorAlunos[posAluno].totalRequisicoes);

                vetorReservas[quantReservas].numPortatil = numAluno;
                lerString("Codigo Reserva: ", vetorReservas[quantReservas].codigo, TAM_CODIGO);
                posReserva = procuraCodigo(vetorReservas, quantReservas, vetorReservas[quantReservas].codigo);
                if (posReserva != -1)
                {
                    printf("\n\nERRO: nao e possivel criar a reserva pois ja existe uma com o mesmo codigo\n\n");
                }
                else
                {
                    vetorReservas[quantReservas].dataDevolucao = lerData("Data da refeicao ");
                    vetorReservas[quantReservas].tipoUtente = lerInteiro("\nTipo Refeicao (1-Almoco/2-Jantar) ", ESTUDANTE, TECNICOADMIN);
                    quantReservas++;
                    vetorAlunos[posAluno].totalRequisicoes++;
                }

        }
    }
    return quantReservas;
}





