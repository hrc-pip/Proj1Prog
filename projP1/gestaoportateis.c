#include <stdio.h>
#include <string.h>
#include "gestaoportateis.h"


 tipodata lerdata (char msg []){
        tipodata data;
        int controlo, diaMax;

        do
        {
            do{
            printf ("%s", msg);
            controlo = scanf ("%d-%d-%d", &data.dia, &data.mes, &data.ano);
            limparbuffer ();

            if (controlo !=3)
            {
                printf("\n ERRO: formato de data invalido\n ");
            }
            }
            while (controlo !=3);

        if (data.ano < MINANO||data.ano>MAXANO)         //validaçao do ano
        {
            printf("\n ERRO: ano invalido, o ano devera pertencer ao intrevalo [%d, %d]", MINANO, MAXANO);
        }
        else
        {
           switch (data.mes){
           case 1:
           case 3:
           case 5:
           case 7:
           case 8:
           case 10:
           case 12:
            diaMax=31;
            break;
           case 4:
           case 6:
           case 9:
           case 11:
            diaMax=30;
            break;
           case 2:
            if (data.ano%400==0 || (data.ano%4==0&&data.ano%100!=0))
            {
                //ano bissexto
                diaMax=29;
            }
            else
            {
                diaMax=28;
            }
            break;
           default:
            printf("\n\n ERRO: mes incorreto\n\n");
            diaMax = data.dia;
           }
           if (data.dia<1 || data.dia>diaMax)
           {
               printf("\n ERRO: dia incorreto");
           }
       }
    }
    while (data.ano<MINANO || data.ano>MAXANO||
           data.mes<1 || data.mes>12||
           data.dia<1 || data.dia>diaMax);
    return data;
}

    void limparbuffer(void)
        {
            char letra;
            do
            {
                letra=getchar();
            }
            while (letra!='\n' && letra!=EOF);

        }




 int numidentificador(){

     int numidentificador;

   printf ("introduza o numero do seu portatil: ");
   scanf ("%d", &numidentificador);

   do {
       printf ("\nERRO: numero de portatil invalido. devera introduzir um numero entre 1 e 30.");
       scanf ("%d", &numidentificador);
    }
     while ( numidentificador<=0 && numidentificador>30);

    return numidentificador;
 }




 char processador ()
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


 }



