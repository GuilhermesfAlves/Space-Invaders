#ifndef __SI_DIFFICULT__
#define __SI_DIFFICULT__
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdio.h>

#define MAX_DIFFICULTIES 4

typedef struct{
    struct historic_node* next;
    int points;
    char* data;
}historic_node;

typedef struct{
    char* name;
    enum {Easy, Normal, Hard, Extreme} type;
    FILE* arq;
    historic_node* node;
}difficulties;

typedef struct{
    unsigned char show;
    unsigned char actual;
    difficulties* vec[];
}difficult;

historic_node* start_node(int points);
void destroy_node(historic_node* node);
historic_node* get_historic(FILE* arq);

difficult* start_difficult();
void destroy_difficult(difficult* difficult);

#endif //__DIFFICULT__