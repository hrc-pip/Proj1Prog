#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestaoReservas.h"


void eliminarReserva(tipoReserva vetorReservas[], int *quantReservas, tipoEstudante vetorAlunos[], int quantAlunos)
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
                posAluno = procuraEstudante(vetorReservas[posReserva].numAluno, vetorAlunos, quantAlunos);
                vetorAlunos[posAluno].totalReservas--;

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








int procuraCodigo (tipoReserva vetorReservas[], int quantReservas, char codigo[])
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


int criarReserva(tipoReserva vetorReservas[], int quantReservas,
                 tipoEstudante vetorAlunos[], int quantAlunos)
{
    int numAluno, posAluno, posReserva;

    if (quantAlunos == 0)
    {
        printf("\nAVISO: nao e possivel efetuar a reserva porque nao existem alunos inscritos\n\n");
    }
    else
    {
        if (quantReservas == MAX_RESERVAS)
        {
            printf("\nAVISO: nao e possivel efetuar a reserva porque lotacao esgotada\n\n");
        }
        else
        {
            // ----  EFETUAR RESERVA
            numAluno = lerInteiro("Nr. Aluno ", MIN_NUMALUNO, MAX_NUMALUNO);
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
                       vetorAlunos[posAluno].totalReservas);

                vetorReservas[quantReservas].numAluno = numAluno;
                lerString("Codigo Reserva: ", vetorReservas[quantReservas].codigo, TAM_CODIGO);
                posReserva = procuraCodigo(vetorReservas, quantReservas, vetorReservas[quantReservas].codigo);
                if (posReserva != -1)
                {
                    printf("\n\nERRO: nao e possivel criar a reserva pois ja existe uma com o mesmo codigo\n\n");
                }
                else
                {
                    vetorReservas[quantReservas].dataRefeicao = lerData("Data da refeicao ");
                    vetorReservas[quantReservas].tipoRefeicao = lerInteiro("\nTipo Refeicao (1-Almoco/2-Jantar) ", ALMOCO, JANTAR);
                    quantReservas++;
                    vetorAlunos[posAluno].totalReservas++;
                }
            }
        }
    }
    return quantReservas;
}





