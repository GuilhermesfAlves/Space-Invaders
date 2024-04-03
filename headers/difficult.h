#ifndef __SI_DIFFICULT__
#define __SI_DIFFICULT__
#include "allegro_headers.h"

#define MAX_DIFFICULTIES 4
#define QTD_P_HISTORIC 10

enum diff_mode {Diff_Easy, Diff_Normal, Diff_Hard, Diff_Extreme};

//para cada contagem em um histórico, há a pontuação, a data e a hora
typedef struct{
    int points;
    char data[10];
    char time[8];
}historic;

//para cada dificuldade há um certo arquivo, tipo, nome e histórico de jogos
typedef struct{
    char* name;
    char type;
    char* arq;
    historic historic[QTD_P_HISTORIC];
}difficulties;

//estrutura maior que contém todas as dificuldades, qual deve ser a atual e se mostra-se o histórico
typedef struct{
    unsigned char show;
    unsigned char current;
    difficulties vec[MAX_DIFFICULTIES];
}difficult;

//escreve o histórico em um determinado arquivo
void write_historic(difficulties* difficulties);
//coloca um novo jogo histórico de uma determinada dificuldade
void push_to_historic(int points, difficulties* difficulties);
//lê o histórico armazenado de uma certa dificuldade
void get_historic(difficulties* difficulties);

//cria todas as dificuldades
difficult* add_difficult(unsigned char current);
//destrói uma todas as dificuldades
void destroy_difficult(difficult* difficult);

//carrega qual foi a última dificuldade usada 
char last_used_difficult();
//salva qual foi a última dificuldade usada
void save_last_used_difficult(unsigned char current);

#endif //__DIFFICULT__