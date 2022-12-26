#include <stdio.h>
#include "gestaoPortateis.h"


float contas(tipoPortatil vetorAlunos[], int quantAlunos, int *quantAvaliados)
{
    int quantPositivas = 0, i;
    float percPositivas = 0;

    *quantAvaliados = 0;

    for(i=0; i < quantAlunos; i++)
    {
        if (vetorAlunos[i].valorEquipamento != -1)
        {
            (*quantAvaliados)++;

            if (vetorAlunos[i].valorEquipamento >= RESIDENCIAS/2)
            {
                quantPositivas++;
            }
        }
    }

    if (*quantAvaliados != 0)
    {
        percPositivas = quantPositivas * 100.0 / *quantAvaliados;
    }

    return percPositivas;
}

void gravaFicheiroTexto(tipoPortatil vetorAlunos[], int quantAlunos)
{
    FILE *fich;
    int i;

    fich = fopen("dadosAlunos.txt", "w");
    if (fich == NULL)
    {
        printf("\nERRO: falha na abertura do ficheiro\n");
    }
    else
    {
        for (i=0; i < quantAlunos; i++)
        {
            fprintf(fich, "\n\tNr.: %d\n", vetorAlunos[i].num);
            fprintf(fich, "\tNome: %s\n", vetorAlunos[i].designacao);
            if (vetorAlunos[i].estado == -1)
            {
                fprintf(fich, "\tAluno nao avaliado\n");
            }
            else
            {
                fprintf(fich, "\tData: %02d-%02d-%d", vetorAlunos[i].dataAquisicao.dia, vetorAlunos[i].dataAquisicao.mes, vetorAlunos[i].dataAquisicao.ano);
                fprintf(fich, "\n\tNota Final: %d\n", vetorAlunos[i].estado);
            }
        }
        fclose(fich);
    }
}



void lerFicheiroBinarioV2(tipoPortatil vetorAlunos[], int *quantAlunos)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosAlunos.bin", "rb");

    if (fich == NULL)
    {
        printf("\nERRO: Falha na abertura do ficheiro\n");
    }
    else
    {
        //controlo = fread(&*quantAlunos, sizeof(int), 1, fich);
        controlo = fread(quantAlunos, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na leitura dos dados\n");
        }
        else
        {
            controlo = fread(vetorAlunos, sizeof(tipoPortatil), *quantAlunos, fich);
            if (controlo != *quantAlunos)
            {
                printf("\nERRO: Falha na leitura dos dados\n");
                *quantAlunos = 0;
            }
            else
            {
                printf("\n\nLeitura efetuada com sucesso\n\n");
            }
        }

        fclose(fich);
    }

}



int lerFicheiroBinario(tipoPortatil vetorAlunos[], int quantAlunos)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosAlunos.bin", "rb");

    if (fich == NULL)
    {
        printf("\nERRO: Falha na abertura do ficheiro\n");
    }
    else
    {
        controlo = fread(&quantAlunos, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na leitura dos dados\n");
        }
        else
        {
            controlo = fread(vetorAlunos, sizeof(tipoPortatil), quantAlunos, fich);
            if (controlo != quantAlunos)
            {
                printf("\nERRO: Falha na leitura dos dados\n");
                quantAlunos = 0;
            }
            else
            {
                printf("\n\nLeitura efetuada com sucesso\n\n");
            }
        }

        fclose(fich);
    }

    return quantAlunos;
}



void gravaFicheiroBinario(tipoPortatil vetorAlunos[], int quantAlunos)
{
    FILE *fich;
    int controlo;

    fich = fopen("dadosAlunos.bin", "wb");

    if (fich == NULL)
    {
        printf("\nERRO: Falha na abertura do ficheiro\n");
    }
    else
    {
        controlo = fwrite(&quantAlunos, sizeof(int), 1, fich);
        if (controlo != 1)
        {
            printf("\nERRO: Falha na gravacao dos dados\n");
        }
        else
        {
            controlo = fwrite(vetorAlunos, sizeof(tipoPortatil), quantAlunos, fich);
            if (controlo != quantAlunos)
            {
                printf("\nERRO: Falha na gravacao dos dados\n");
            }
            else
            {
                printf("\n\nGravacao efetuada com sucesso\n\n");
            }
        }

        fclose(fich);
    }

}

/*
void lerNotas(tipoPortatil vetorAlunos[], int quantAlunos)
{
    int i;

    if (quantAlunos == 0)
    {
        printf("ATENCAO: nao existem alunos inscritos\n");
    }
    else
    {
        for (i=0; i < quantAlunos; i++)
        {
            if (vetorAlunos[i].estado == -1)
            {
                printf("\nAluno (%d) %s", vetorAlunos[i].num, vetorAlunos[i].designacao);
                vetorAlunos[i].estado = lerInteiro("\nInsira nota do aluno", 0, RESIDENCIAS);
                vetorAlunos[i].dataAquisicao = lerData("Data Aquisicao: ");
            }
        }
    }
}
*/

void mostrarUmPortatil(tipoPortatil aluno)
{
    printf("\n\tNr.: %d\n", aluno.num);
    printf("\tDesignacao: %s\n", aluno.designacao);
    printf("\n\tProcessador.: %d\n", aluno.processador);
    printf("\n\tRAM.: %d\n", aluno.ram);
    printf("\n\tEstado.: %d\n", aluno.estado);
    printf("\n\tLocalizacao.: %d\n", aluno.localizacao);
    printf("\tData: ");
    escreverData(aluno.dataAquisicao);
    printf("\n\tValor Equipamento: %d\n", aluno.valorEquipamento);

}

void mostrarTodosPortateis(tipoPortatil vetorPortateis[], int quantPortateis)
{
    int i;

    printf("\n---- LISTAGEM dos ALUNOS -----\n");
    for (i=0; i < quantPortateis; i++)
    {
        printf("\n\nPortatil: %d", i+1);
        mostrarUmPortatil(vetorPortateis[i]);
    }
}

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
            vetorPortateis[*quantPortateis].num = lerDadosEstudante(vetorPortateis[*quantPortateis].designacao);
            pos = procuraEstudante(vetorPortateis[*quantPortateis].num, vetorPortateis, *quantPortateis);
            if (pos != -1) // significa que o aluno já existe no vetor
            {
                printf("\nERRO: o aluno ja se encontra inscrito\n");
                opcao=lerInteiro("Quer inserir outro aluno (1-Sim, 0-Nao)", 0, 1);
            }
            else
            {
                vetorPortateis[*quantPortateis].estado = -1; // indicador de que o aluno ainda não foi avaliado
                vetorPortateis[*quantPortateis].totalAvarias = 0;
                (*quantPortateis)++;
                opcao = 0;
            }
        }
        while(opcao == 1);
    }
}

int lerDadosPortatil(char nome[])
{
    int numPortatil;

    numPortatil = lerInteiro("\nNr. Aluno", RESIDENCIAS, CAMPUS5);
    lerString("Nome do aluno: ", nome, MAXSTRING);

    return numPortatil;
}

/* 2ª versão
void lerDadosEstudante(tipoEstudante *aluno)
{
    aluno->num = lerInteiro("Nr. Aluno", MIN_NUMALUNO, MAX_NUMALUNO);
    lerString("Nome do aluno: ", aluno->nome, MAXSTRING);
}
*/

/* 3ª versão
tipoEstudante lerDadosEstudante(tipoEstudante aluno)
{
    aluno.num = lerInteiro("Nr. Aluno", MIN_NUMALUNO, MAX_NUMALUNO);
    lerString("Nome do aluno: ", aluno.nome, MAXSTRING);

    return aluno;
}
*/

int lerQuantidadeEstudantes(void)
{
    int num;

    num = lerInteiro("\nIndique a quantidade de alunos inscritos", 0, MAXPORTATEIS);

    return num;
}
