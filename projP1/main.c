#include <stdio.h>
#include <stdlib.h>


#include "funcoesGenericas.h"
#include "gestaoportateis.h"
#include "avarias.h"


char menu (int quantPortateis, int quantDisponiveis);

int main()
{

    tipoPortatil vetorPortateis[MAXPORTATEIS];
    int quantPortateis = lerFicheiroBinarioPortatil(vetorPortateis, quantPortateis);


    char opcao;

    do
    {
        int quantDisponiveis=quantPortateisDisponiveis(vetorPortateis,quantPortateis);
        opcao = menu(quantPortateis, quantDisponiveis);
        switch (opcao)
        {
        case 'A':
            acrescentaPortatil(vetorPortateis, &quantPortateis);
            break;

        case 'M':
            mostrarTodosPortateis(vetorPortateis, quantPortateis);
            break;

        case 'L':
            alteraLocalizacao(vetorPortateis, quantPortateis);
            break;

        case 'F':
            gravaFicheiroBinarioPortatil(vetorPortateis, quantPortateis);
            break;

        default:
            printf("\nERRO: opcao desconhecida\n");
        }
    }
    while (opcao != 'F');

    return 0;
}

//--------- IMPLEMENTAÇÃO das FUNÇÕES -----


char menu (int quantPortateis, int quantDisponiveis)
{
    char opcao;

    printf("\n\n********************** MENU PRINCIPAL ********************** \n\n");
    printf("Número de Portateis Inseridos: %d\n", quantPortateis);
    printf("Portateis Disponiveis: %d \n\n", quantDisponiveis);
    printf("A - Acrescenta Portatil\nM - Mostrar Dados\n");
    printf("L - Alterar Localizacao do Portatil\n");
    printf("F - Fim\n");
    printf("\t\tOPCAO -> ");

    scanf("%c", &opcao);
    limparBuffer();

    opcao = toupper(opcao);

    return opcao;
}
