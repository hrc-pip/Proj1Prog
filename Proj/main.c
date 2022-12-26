#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "funcoesGenericas.h"
#include "gestaoPortateis.h"
#include "gestaoRequisicoes.h"


char menu (int quantAlunos, int quantAvaliados, float percPositivas);

int main()
{
    //tipoReserva vetorReservas[MAX_RESERVAS];
    tipoRequisicao *vetorReservas = NULL;
    int quantReservas=0;

    tipoPortatil vetorAlunos[MAXPORTATEIS];
    int quantAlunos = 0;

    int quantAvaliados=0;
    float percPositivas =0;
    char opcao;

    do
    {
        opcao = menu(quantAlunos, quantAvaliados, percPositivas);
        switch (opcao)
        {
        case 'A':
            acrescentaAluno(vetorAlunos, &quantAlunos);
            break;
        case 'I':
            lerNotas(vetorAlunos, quantAlunos);
            percPositivas = contas(vetorAlunos, quantAlunos, &quantAvaliados);
            break;
        case 'M':
            mostrarTodosAlunos(vetorAlunos, quantAlunos);
            break;
        case 'G':
            gravaFicheiroBinario(vetorAlunos, quantAlunos);
            gravaFicheiroTexto(vetorAlunos, quantAlunos);
            break;
        case 'L':
            //quantAlunos = lerFicheiroBinario(vetorAlunos, quantAlunos);
            lerFicheiroBinarioV2(vetorAlunos, &quantAlunos);
            percPositivas = contas(vetorAlunos, quantAlunos, &quantAvaliados);
            break;
        case 'C':
            quantReservas = criarReserva(vetorReservas, quantReservas, vetorAlunos, quantAlunos);
            break;
        case 'E':
            eliminarReserva(vetorReservas, &quantReservas, vetorAlunos, quantAlunos);
            break;
        case 'F':
            break;
        default:
            printf("\nERRO: opcao desconhecida\n");
        }
    }
    while (opcao != 'F');

    free(vetorReservas);
    return 0;
}

//--------- IMPLEMENTAÇÃO das FUNÇÕES -----


char menu (int quantAlunos, int quantAvaliados, float percPositivas)
{
    char opcao;

    printf("\n\n********************** MENU PRINCIPAL ********************** \n\n");
    printf("Estudantes Inscritos: %d\n", quantAlunos);
    printf("Estudantes Avaliados: %d \t\t Notas Positivas (%%): %.2f\n\n", quantAvaliados, percPositivas);
    printf("A - Acrescenta Estudante\nI - Introducao das Notas\n");
    printf("M - Mostrar Dados\nG - Gravar dados em ficheiros\n");
    printf("L - Ler dados de Ficheiro\n");
    printf("--- RESERVAS ---\n");
    printf("\t C - Criar reserva\n\tE - Eliminar reserva\n");
    printf("F - Fim\n");
    printf("\t\tOPCAO -> ");

    scanf("%c", &opcao);
    limparBuffer();

    opcao = toupper(opcao);

    return opcao;
}

