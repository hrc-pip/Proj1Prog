#include <stdio.h>
#include <string.h>
#include "gestaoportateis.h"


// =====================================================================================
void mostrarUmPortatil(tipoPortatil portatil)
{
    printf("\n\tNr.: %d\n", portatil.num);
    printf("\tDesignacao: %s\n", portatil.designacao);
    printf("\tProcessador.: %d\n", portatil.processador);
    printf("\tRAM.: %d Gb\n", portatil.ram);

    switch(portatil.estado)
    {
    case DISPONIVEL:
        printf("\tEstado.: DISPONIVEL\n");
        break;
    case REQUISITADO:
        printf("\tEstado.: REQUISITADO\n");
        break;
    case AVARIADO:
        printf("\tEstado.: AVARIADO\n");
        break;
    }

    switch(portatil.localizacao)
    {
    case RESIDENCIAS:
        printf("\tLocalizacao.: RESIDENCIAS\n");
        break;
    case CAMPUS1:
        printf("\tLocalizacao.: CAMPUS1\n");
        break;
    case CAMPUS2:
        printf("\tLocalizacao.: CAMPUS2\n");
        break;
    case CAMPUS5:
        printf("\tLocalizacao.: CAMPUS5\n");
        break;
    }

    printf("\tData: ");
    escreverData(portatil.dataAquisicao);
    printf("\n\tValor Equipamento: %d\n", portatil.valorEquipamento);
    printf("\n\tTotal Requisicoes.: %d\n", portatil.totalRequisicao);
    printf("\n\tTotal Requisicoes.: %d\n", portatil.totalAvarias);

}


// =====================================================================================
void mostrarTodosPortateis(tipoPortatil vetorPortateis[], int quantPortateis)
{
    int i;

    printf("\n---- LISTAGEM dos POSTATEIS -----\n");
    for (i=0; i < quantPortateis; i++)
    {
        printf("\n\nPortatil: %d", i+1);
        mostrarUmPortatil(vetorPortateis[i]);
    }
}


// =====================================================================================
int procuraPortatil(int numPortatil, tipoPortatil vetorPortateis[], int quantPortateis)
{
    int i, pos=-1;

    for (i=0; i < quantPortateis; i++)
    {
        if (numPortatil == vetorPortateis[i].num)
        {
            pos = i;
            i = quantPortateis;
        }
    }

    return pos;
}


// =====================================================================================
int lerQuantidadePortateis(void)
{
    int num;

    num = lerInteiro("\nIndique a quantidade de portateis inscritos", 0, MAXPORTATEIS);

    return num;
}


// =====================================================================================
void acrescentaPortatil (tipoPortatil vetorPortateis[], int *quantPortateis)
{
    int pos, opcao=0;

    if (*quantPortateis == MAXPORTATEIS)
    {
        printf("\nATENCAO: impossivel inscrever mais portateis. Lotacao esgota\n ");
    }
    else
    {
        do
        {
            vetorPortateis[*quantPortateis] = lerDadosPortatil();
            pos = procuraPortatil(vetorPortateis[*quantPortateis].num, vetorPortateis, *quantPortateis);
            if (pos != -1) // significa que o portatil já existe no vetor
            {
                printf("\nERRO: o portatil ja se encontra inscrito\n");
                opcao=lerInteiro("Quer inserir outro portatil (1 - Sim, 0 - Nao)", 0, 1);
            }
            else
            {
                vetorPortateis[*quantPortateis].estado = DISPONIVEL; // indicador de que o portatil é inserido disponivel
                (*quantPortateis)++;
                opcao = 0;
            }
        }
        while(opcao == 1);
    }
}


// =====================================================================================
tipoPortatil lerDadosPortatil()
{
    tipoPortatil port;


    port.num = lerInteiro("\nNr. Portatil", 0, MAXPORTATEIS);
    lerString("Designacao: ", port.designacao, MAXSTRING);
    port.processador = lerInteiro("Processador (1-i3 | 2-i5 | 3-i7) ", I3, I7);
    port.ram = lerInteiro("RAM",1, MAXRAM);
    port.localizacao = lerInteiro("Localizacao (0-RESIDENCIAS, 1-CAMPUS1, 2-CAMPUS2, 3-CAMPUS5)", RESIDENCIAS, CAMPUS5);
    port.dataAquisicao = lerData("Data de Aquisicao (dd-mm-aaaa): ");
    port.valorEquipamento = lerInteiro("Valor do Portatil", 0, 99999);
    port.totalRequisicao = 0;
    port.totalAvarias = 0;

    return port;
}


// =====================================================================================
int quantPortateisDisponiveis(tipoPortatil vetorPortateis[], int quantPorts)
{
    int quantDispo = 0;
    for(int i = 0; i < quantPorts; i++)
    {
        if(vetorPortateis[i].estado == DISPONIVEL)
        {
            quantDispo++;
        }
    }
    return quantDispo;
}


// =====================================================================================
void alteraLocalizacao(tipoPortatil vetorPortateis[], int quantPorts)
{
    int num, posPort;
    if(quantPorts != 0)
    {

        num = lerInteiro("\nNr. Portatil", 0, MAXPORTATEIS);
        posPort = procuraPortatil(num, vetorPortateis, quantPorts);
        if( posPort != -1)
        {
            vetorPortateis[num].localizacao = lerInteiro("Localizacao (0 - RESIDENCIAS, 1 - CAMPUS1, 2 - CAMPUS2, 3 - CAMPUS5)", RESIDENCIAS, CAMPUS5);
            printf("Localizacao alterada com sucesso!!");
        } else {
            printf("\n\tERRO!! Nao existe nenhum portatil com este numero");
        }
        printf("\nERRO!! Nao existem portateis");
    }

}


// =====================================================================================
void gravaFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantPorts)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosPortateis.bin", "wb");

    if (fich == NULL)
    {
        printf("\nERRO: Falha na abertura do ficheiro\n");
    }
    else
    {
        controlo = fwrite(&quantPorts, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na gravacao dos dados\n");
        }
        else
        {
            controlo = fwrite(vetorPortateis, sizeof(tipoPortatil), quantPorts, fich);
            if (controlo != quantPorts)
            {
                printf("\nERRO: Falha na gravacao dos dados\n");
            }
        }

        fclose(fich);
    }

}


// =====================================================================================
int lerFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantPorts)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosPortateis.bin", "rb");

    if (fich == NULL)
    {
        quantPorts = 0;
    }
    else
    {
        controlo = fread(&quantPorts, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na leitura dos dados\n");
        }
        else
        {
            controlo = fread(vetorPortateis, sizeof(tipoPortatil), quantPorts, fich);
            if (controlo != quantPorts)
            {
                printf("\nERRO: Falha na leitura dos dados\n");
                quantPorts = 0;
            }
        }

        fclose(fich);
    }

    return quantPorts;
}
