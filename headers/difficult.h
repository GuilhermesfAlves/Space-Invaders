#ifndef __SI_DIFFICULT__
#define __SI_DIFFICULT__
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
// #include <time.h>
#include <stdio.h>

#define MAX_DIFFICULTIES 4
#define QTD_P_HISTORIC 10

typedef struct{
    int points;
    char* data;
    char* time;
}historic;

typedef struct{
    char* name;
    char type;
    char* arq;
    historic historic[QTD_P_HISTORIC];
}difficulties;

typedef struct{
    unsigned char show;
    unsigned char actual;
    difficulties vec[MAX_DIFFICULTIES];
}difficult;

void get_historic(difficulties* difficulties);

difficult* add_difficult(unsigned char actual);
void destroy_difficult(difficult* difficult);

char last_used_difficult();
void save_last_used_difficult(unsigned char actual);

#endif //__DIFFICULT__