#include <stdio.h>
#include <string.h>

#include "gestaoportateis.h"


// =====================================================================================
void percentagemProcessador(tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int i, somai3 = 0, somai5 = 0, somai7 = 0;
    if(quantidadePortateis != 0)
    {      
        for(i = 0; i < quantidadePortateis; i++)
        {
            switch(vetorPortateis[i].processador)
            {
                case I3:
                    somai3++;  // conta quantos I3 tem nos portateis existentes
                    break;

                case I5:
                    somai5++;  // conta quantos I5 tem nos portateis existentes
                    break;

                case I7:
                    somai7++;  // conta quantos I7 tem nos portateis existentes
                    break;
            }
        }
        printf("\n Quantidade de Portateis: %d \n", quantidadePortateis);
        printf("\n\tPortateis com I3.: %d%%", (somai3*100) / quantidadePortateis);
        printf("\n\tPortateis com I5.: %d%%", (somai5*100) / quantidadePortateis);  // faz o calculo da percentagem e exibe no ecrã
        printf("\n\tPortateis com I7.: %d%%", (somai7*100) / quantidadePortateis);
    }
    else
    {
        printf("\n\tAviso: nao exitem  portateis inseridos!");
    }
    
}


// =====================================================================================
void mostrarUmPortatil(tipoPortatil portatil)
{
    printf("\n\tNr.: %d\n", portatil.num);
    printf("\tDesignacao.: %s\n", portatil.designacao);

    switch(portatil.processador)
    {
    case I3:
        printf("\tProcessador.: I3\n");
        break;
    case I5:
        printf("\tProcessador.: I5\n");
        break;
    case I7:
        printf("\tProcessador.: I7\n");
        break;
    }


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

    printf("\tData.: ");
    escreverData(portatil.dataAquisicao);
    printf("\n\tValor Equipamento.: %d\n", portatil.valorEquipamento);
    printf("\tTotal Avarias.: %d\n", portatil.quantTotalAvarias);
    printf("\tTotal Requisicoes.: %d\n", portatil.quantTotalRequisicao);

}


// =====================================================================================
int procuraPortatil(int numPortatil, tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int i, pos=-1;

    for (i = 0; i < quantidadePortateis; i++)
    {
        if (numPortatil == vetorPortateis[i].num)  // procura o portátil pela chave primária
        {
            pos = i;
            i = quantidadePortateis;
        }
    }

    return pos;
}


// =====================================================================================
tipoPortatil lerDadosPortatil(tipoPortatil port)
{

    lerString("Designacao: ", port.designacao, MAXSTRING);
    port.processador = lerInteiro("Processador (1-i3 | 2-i5 | 3-i7) ", I3, I7);
    port.ram = lerInteiro("RAM ",4, MAXRAM);
    port.localizacao = lerInteiro("Localizacao (0-RESIDENCIAS, 1-CAMPUS1, 2-CAMPUS2, 3-CAMPUS5)", RESIDENCIAS, CAMPUS5);
    port.dataAquisicao = lerData("Data de Aquisicao (dd-mm-aaaa): ");
    port.valorEquipamento = lerInteiro("Valor do Portatil", 0, 99999);

    return port;
}


// =====================================================================================
void acrescentaPortatil (tipoPortatil vetorPortateis[], int *quantidadePortateis)
{
    int pos, opcao=0;

    if (*quantidadePortateis == MAXPORTATEIS)
    {
        printf("\nATENCAO: impossivel adicionar mais portateis. Lotacao esgota\n ");
    }
    else
    {
        do
        {
            vetorPortateis[*quantidadePortateis].num = lerInteiro("\nNr. Portatil", 0, MAXPORTATEIS);



            pos = procuraPortatil(vetorPortateis[*quantidadePortateis].num, vetorPortateis, *quantidadePortateis);



            if (pos != -1) // significa que o portatil já existe no vetor
            {
                printf("\nERRO: o portatil ja se encontra inscrito\n");
                opcao = lerInteiro("Quer inserir outro portatil (1 - Sim, 0 - Nao)", 0, 1);
            }
            else
            {

                vetorPortateis[*quantidadePortateis] = lerDadosPortatil(vetorPortateis[*quantidadePortateis]);

                vetorPortateis[*quantidadePortateis].estado = DISPONIVEL; // o portatil é inserido disponivel
                vetorPortateis[*quantidadePortateis].quantTotalRequisicao = 0;
                vetorPortateis[*quantidadePortateis].quantTotalAvarias = 0;
                vetorPortateis[*quantidadePortateis].quantTotalDiasRequisitados = 0;


                (*quantidadePortateis)++;
                opcao = 0;
            }
        }
        while(opcao == 1);

    }
}


// =====================================================================================
int quantidadePortateisDisponiveis(tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int quantDispo = 0, i;
    for(i = 0; i < quantidadePortateis; i++)
    {
        if(vetorPortateis[i].estado == DISPONIVEL)
        {
            quantDispo++; // soma somente se o portatil estiver disponivel
        }
    }
    return quantDispo;
}


// =====================================================================================
void alteraLocalizacao(tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    int num, posPort;
    if(quantidadePortateis != 0)
    {

        num = lerInteiro("\nNr. Portatil", 0, MAXPORTATEIS);

        posPort = procuraPortatil(num, vetorPortateis, quantidadePortateis);
        if( posPort != -1)
        {
            if(vetorPortateis[num].estado == DISPONIVEL)  // só altera a localização se o portátil estiver disponível
            {
                vetorPortateis[num].localizacao = lerInteiro("Localizacao (0 - RESIDENCIAS, 1 - CAMPUS1, 2 - CAMPUS2, 3 - CAMPUS5)", RESIDENCIAS, CAMPUS5);

                printf("Localizacao alterada com sucesso!!");
            }
            else
            {
                printf("O portatil nao esta disponivel para ser alterado");
            }
            
        } else {
            printf("\n\tERRO!! Nao existe nenhum portatil com este numero");
        }
    }
    else
    {
        printf("\nERRO!! Nao existem portateis");
    }

}


// =====================================================================================
void gravaFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantidadePortateis)
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
        controlo = fwrite(&quantidadePortateis, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na gravacao dos dados\n");
        }
        else
        {
            controlo = fwrite(vetorPortateis, sizeof(tipoPortatil), quantidadePortateis, fich);
            if (controlo != quantidadePortateis)
            {
                printf("\nERRO: Falha na gravacao dos dados\n");
            }
        }

        fclose(fich);
    }

}


// =====================================================================================
int lerFicheiroBinarioPortatil(tipoPortatil vetorPortateis[], int quantidadePortateis)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosPortateis.bin", "rb");

    if (fich == NULL)
    {
        quantidadePortateis = 0;
    }
    else
    {
        controlo = fread(&quantidadePortateis, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na leitura dos dados\n");
        }
        else
        {
            controlo = fread(vetorPortateis, sizeof(tipoPortatil), quantidadePortateis, fich);
            if (controlo != quantidadePortateis)
            {
                printf("\nERRO: Falha na leitura dos dados\n");
                quantidadePortateis = 0;
            }
        }

        fclose(fich);
    }

    return quantidadePortateis;
}
