#include <stdio.h>
#include "gestaoAlunos.h"


float contas(tipoEstudante vetorAlunos[], int quantAlunos, int *quantAvaliados)
{
    int quantPositivas = 0, i;
    float percPositivas = 0;

    *quantAvaliados = 0;

    for(i=0; i < quantAlunos; i++)
    {
        if (vetorAlunos[i].notaFinal != -1)
        {
            (*quantAvaliados)++;

            if (vetorAlunos[i].notaFinal >= MAXNOTA/2)
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

void gravaFicheiroTexto(tipoEstudante vetorAlunos[], int quantAlunos)
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
            fprintf(fich, "\tNome: %s\n", vetorAlunos[i].nome);
            if (vetorAlunos[i].notaFinal == -1)
            {
                fprintf(fich, "\tAluno nao avaliado\n");
            }
            else
            {
                fprintf(fich, "\tData: %02d-%02d-%d", vetorAlunos[i].dataAvaliacao.dia, vetorAlunos[i].dataAvaliacao.mes, vetorAlunos[i].dataAvaliacao.ano);
                fprintf(fich, "\n\tNota Final: %d\n", vetorAlunos[i].notaFinal);
            }
        }
        fclose(fich);
    }
}



void lerFicheiroBinarioV2(tipoEstudante vetorAlunos[], int *quantAlunos)
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
            controlo = fread(vetorAlunos, sizeof(tipoEstudante), *quantAlunos, fich);
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



int lerFicheiroBinario(tipoEstudante vetorAlunos[], int quantAlunos)
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
            controlo = fread(vetorAlunos, sizeof(tipoEstudante), quantAlunos, fich);
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



void gravaFicheiroBinario(tipoEstudante vetorAlunos[], int quantAlunos)
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
            controlo = fwrite(vetorAlunos, sizeof(tipoEstudante), quantAlunos, fich);
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


void lerNotas(tipoEstudante vetorAlunos[], int quantAlunos)
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
            if (vetorAlunos[i].notaFinal == -1)
            {
                printf("\nAluno (%d) %s", vetorAlunos[i].num, vetorAlunos[i].nome);
                vetorAlunos[i].notaFinal = lerInteiro("\nInsira nota do aluno", 0, MAXNOTA);
                vetorAlunos[i].dataAvaliacao = lerData("Data Avaliacao: ");
            }
        }
    }
}


void mostrarUmAluno(tipoEstudante aluno)
{
    printf("\n\tNr.: %d\n", aluno.num);
    printf("\tNome: %s\n", aluno.nome);
    if (aluno.notaFinal == -1)
    {
        printf("\tAluno nao avaliado\n");
    }
    else
    {
        printf("\tData: ");
        escreverData(aluno.dataAvaliacao);
        printf("\n\tNota Final: %d\n", aluno.notaFinal);
    }
}

void mostrarTodosAlunos(tipoEstudante vetorAlunos[], int quantAlunos)
{
    int i;

    printf("\n---- LISTAGEM dos ALUNOS -----\n");
    for (i=0; i < quantAlunos; i++)
    {
        printf("\n\nALUNO: %d", i+1);
        mostrarUmAluno(vetorAlunos[i]);
    }
}

int procuraEstudante (int numAluno, tipoEstudante vetorAlunos[], int quantAlunos)
{
    int i, pos=-1;

    for (i=0; i < quantAlunos; i++)
    {
        if (numAluno == vetorAlunos[i].num)
        {
            pos = i;
            i=quantAlunos;
        }
    }

    return pos;
}


void acrescentaAluno (tipoEstudante vetorAlunos[], int *quantAlunos)
{
    int pos, opcao=0;

    if (*quantAlunos == MAXALUNOS)
    {
        printf("\nATENCAO: impossivel inscrever mais mais. Lotacao esgota\n ");
    }
    else
    {
        do
        {
            vetorAlunos[*quantAlunos].num = lerDadosEstudante(vetorAlunos[*quantAlunos].nome);
            pos = procuraEstudante(vetorAlunos[*quantAlunos].num, vetorAlunos, *quantAlunos);
            if (pos != -1) // significa que o aluno já existe no vetor
            {
                printf("\nERRO: o aluno ja se encontra inscrito\n");
                opcao=lerInteiro("Quer inserir outro aluno (1-Sim, 0-Nao)", 0, 1);
            }
            else
            {
                vetorAlunos[*quantAlunos].notaFinal = -1; // indicador de que o aluno ainda não foi avaliado
                vetorAlunos[*quantAlunos].totalReservas = 0;
                (*quantAlunos)++;
                opcao = 0;
            }
        }
        while(opcao == 1);
    }
}

int lerDadosEstudante(char nome[])
{
    int numAluno;

    numAluno = lerInteiro("\nNr. Aluno", MIN_NUMALUNO, MAX_NUMALUNO);
    lerString("Nome do aluno: ", nome, MAXSTRING);

    return numAluno;
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

    num = lerInteiro("\nIndique a quantidade de alunos inscritos", 0, MAXALUNOS);

    return num;
}
