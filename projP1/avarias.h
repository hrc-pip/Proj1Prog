#ifndef AVARIAS_C_INCLUDED
#define AVARIAS_C_INCLUDED


#define MINANO 2000
#define MAXANO 2100

#define MAXPORTATEIS 30
#define I3 1
#define I5 2
#define I7 3
#define MAXRAM 64
#define RESIDENCIAS 0
#define CAMPUS1 1
#define CAMPUS2 2
#define CAMPUS5 3
#define TEMPORARIA 1
#define PERMANENTE 2



tipoData lerdataavaria (char mensagem[]);
void escreverdataavaria(tipoData);

typedef struct
{
    int num;
    int processador;
    int ram;
    int localizacao;
    tipoData dataavaria;
    int valorequipamento;
    int tipoavaria;
}tipoportatil;


void limparBuffer(void);






#endif // AVARIAS_C_INCLUDED
