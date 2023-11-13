#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"

#define SHIP_MOVE 5
#define SHIP_INICIAL_LIFES 3
#define SHIP_MAX_LIFES 5

typedef struct{
    int life;
    int pos_x;
    int pos_y;
    unsigned char move;
    shot_sentinel* shots;
    ALLEGRO_BITMAP** img;
}ship;

shot* ship_straight_shoot(ship *ship);
ship* add_ship();
void destroy_ship(ship* ship);
int shot_in_row(ship* ship);

#endif //__SHIP__