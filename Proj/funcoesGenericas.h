#ifndef FUNCOESGENERICAS_H_INCLUDED
#define FUNCOESGENERICAS_H_INCLUDED

#define MIN_ANO 2000
#define MAX_ANO 2100

typedef struct{
    int dia, mes, ano;
} tipoData;

tipoData lerData(char msg[]);
void escreverData(tipoData data);
float lerFloat (char msg[], float limMin, float limMax);
int lerInteiro (char msg[], int limMin, int limMax);
void lerString (char msg[], char texto[], int tamMax);
void limparBuffer(void);

#endif // FUNCOESGENERICAS_H_INCLUDED
