#ifndef __DIFICULT__
#define __DIFICULT__
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdio.h>

#define MAX_DIFICULTIES 4

typedef struct{
    char* name;
    enum {Easy, Normal, Hard, Extreme} type;
    FILE* arq;
    historic_node* node;
}dificulties;

typedef struct{
    unsigned char show;
    unsigned char actual;
    dificulties* vec[];
}dificult;

typedef struct{
    historic_node* next;
    int points;
    char* data;
}historic_node;

historic_node* start_node(int points);
void node_destroy(historic_node* node);
historic_node* get_historic(FILE* arq);

dificult* start_dificult();
void dificult_destroy(dificult* dificult);

#endif //__DIFICULT__