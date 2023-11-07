#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"

#define SHIP_LIFES 3

typedef struct{
    int life;
    int pos_x;
    int pos_y;
    shot* shots;
    unsigned char move;
    ALLEGRO_BITMAP** img;
}ship;

shot* ship_straight_shoot(ship *ship);
void* destroy_ship_shot(ship* ship);
ship* add_ship();
void destroy_ship(ship* ship);

#endif //__SHIP__