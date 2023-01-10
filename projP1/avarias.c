# include <stdio.h>
# include <string.h>
# include "avarias.h"


tipoData lerdataavaria (char mensagem[])
{
    tipoData data;
    int diaMax, controlo;

    do
    {
        do
        {
            printf ("%s", mensagem);
            controlo = scanf ("%d-%d-%d", &data.dia, &data.mes, &data.ano);
            limparBuffer();

            if (controlo!=3)
            {
                printf ("\nERRO:data invalida.");
            }
        }
        while(controlo !=3)


        if (data.ano<MINANO||data.ano>MAXANO)
        {
            printf ("\nERRO: ano invalido, o ano devera pertencer ao intrevalo [%d, %d]", MINANO, MAXANO);
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
            diaMax =31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            diaMax = 30;
            break;
        case 2:
            if (data.ano%400==0||data.ano%4==0||data.ano%100!=0)
            {
                diaMax=29;
            }
            else
            {
                diaMax=28;
            }
            break;
        default:
            printf ("\nERRO: mes invalido.");
            diaMax=dia.data;
            }

            if (data.dia<1||data.dia>diaMax)
            {
                printf ("\nERRO: dia invalido. O dia deve pertencer ao intrevalo [1,%d]", diaMax);
            }
        }
    }
    while (data.ano<MINANO||data.ano>MAXANO||
           data.mes<1 || data.mes>12||
           data.dia<1 || data.dia >diaMax);


    return data;
}

void escreverdataavaria(tipoData)
{
    printf ("%02d-%02d-%d", data.dia, data.mes, data.ano);
}




tipoportatil dadosportatilavariado ()
{
    tipoportatil portatil;

    portatil.num = lerinteiro ("\nNumero do portatil", 0, MAXPORTATEIS);
    portatil.processador = lerinteiro ("\nProcessador (1-i3 | 2-i5 | 3-i7)", I3, I7 );
    portatil.ram = lerinteiro ("\nRAM ", 0, MAXRAM);
    portatil.localizacao = lerinteiro ("\nLocalizacao (0-RESIDENCIAS |1-CAMPUS1 | 2-CAMPUS2 | 3-CAMPUS5)", RESIDENCIAS, CAMPUS5 );
    potatil.valorequipamento = lerinteiro ("\nValor do portatil ", 0, 99999);
    portatil.dataaquisicao = lerdataavaria("\nData da avaria (dd-mm-aaaa) ");
    portatil.tipoavaria = lerinteiro ("\n avaria (1-temporaria | 2-permanente)", TEMPORARIA, PERMANENTE);

    return portatil;
}


void tipoavaria
{
    if (portatil.tipoavaria==2)
    {
        printf ("O portatil introduzido ja nao esta disponivel. Escolha outro portatil.");
        tipoportatil dadosportatilavariado;
    }
    else {
        printf ("O portatil introduzido esta com uma avaria.");
    }
}


tipoData lerdataaposavaria ()
{
    tipoData data;
    int diaMax, controlo;

    do
    {
        do
        {
            printf ("%s", mensagem);
            controlo = scanf ("%d-%d-%d", &data.dia, &data.mes, &data.ano);
            limparBuffer();

            if (controlo!=3)
            {
                printf ("\nERRO:data invalida.");
            }
        }
        while(controlo !=3)


        if (data.ano<MINANO||data.ano>MAXANO)
        {
            printf ("\nERRO: ano invalido, o ano devera pertencer ao intrevalo [%d, %d]", MINANO, MAXANO);
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
            diaMax =31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            diaMax = 30;
            break;
        case 2:
            if (data.ano%400==0||data.ano%4==0||data.ano%100!=0)
            {
                diaMax=29;
            }
            else
            {
                diaMax=28;
            }
            break;
        default:
            printf ("\nERRO: mes invalido.");
            diaMax=dia.data;
            }

            if (data.dia<1||data.dia>diaMax)
            {
                printf ("\nERRO: dia invalido. O dia deve pertencer ao intrevalo [1,%d]", diaMax);
            }
        }
    }
    while (data.ano<MINANO||data.ano>MAXANO||
           data.mes<1 || data.mes>12||
           data.dia<1 || data.dia >diaMax);

    tipoData lerdataaposavaria = ("%d-%d-%d", &data.dia+7, &data.mes, &data.ano);
    switch (data.mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (data.dia>31)
        {
            data.mes = data.mes+1;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (data.dia>30){
            data.mes = data.mes+1;
        }
        break;
    case 2:
        if (data.mes>28){
            data.mes = data.mes +1;
        }

    }

    return data;

}



void limparBuffer(void)
{
    char letra;

    do
    {
        letra = getchar();
    }
    while (letra != '\n'&& letra != EOF);
}
