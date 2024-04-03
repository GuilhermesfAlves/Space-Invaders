#ifndef __SI_POWER_UP__
#define __SI_POWER_UP__

#include "allegro_headers.h"

#define FALL_MOVE 3
#define QTD_POWER_UP_TYPES 1
#define POWER_UP_LIFETIME 420 // equal to 7 seconds

enum power_up_enums{NONE, SHIELD};

//node of power ups
typedef struct power_up{
    int pos_x;
    int pos_y;
    ALLEGRO_BITMAP* img;
    int type;
    struct power_up* next;
    struct power_up* previous;
}power_up;

//list of power ups
typedef struct{
    power_up* first;
    power_up* last;
}power_up_list;

//Criação da lista de power_ups
power_up_list* create_power_up_list();
//Destuição de uma power_up_list
void destroy_power_up_list(power_up_list* power_up_list);

//criação de um power_up em uma lista
power_up* add_power_up(char type, int pos_x, int pos_y, power_up_list* power_up_list);
//destruição de um power_up de uma power_up_list
power_up* destroy_power_up(power_up* power_up, power_up_list* power_up_list);

#endif //__SI_POWER_UP__