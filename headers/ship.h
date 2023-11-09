#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"

#define ROW_SPACE 15
#define SHIP_LIFES 3

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