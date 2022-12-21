#ifndef GESTAOPORTATEIS_H_INCLUDED
#define GESTAOPORTATEIS_H_INCLUDED

#define MAXANO 2099
#define MINANO 2021

typedef struct{
    int dia, mes, ano;
}tipodata;


tipodata lerdata (char msg []);
void limparbuffer(void);
int numidentificador();


#endif // GESTAOPORTATEIS_H_INCLUDED



