#include <stdio.h>
#include <stdlib.h>


int main()
{

     char processador;
        printf("escolha um dos processador disponiveis para o seu portatil:\na)i3\nb)i5\nc)i7\n");
        scanf ("%c", &processador);


    switch (processador){
        case 'a':
            printf("processador escolhido: i3");
            break;
        case 'b':
            printf("processador escolhido: i5");
            break;
        case 'c':
            printf("processador escolhido: i7");
            break;
        default:
            printf("\nERRO: escolha uma opcao valida.");
        }




    return 0;
}
