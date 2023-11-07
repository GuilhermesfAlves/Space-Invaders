#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"

#define SHIP_LIFES 3

typedef struct{
    int life;
    int pos_x;
    int pos_y;
    unsigned char move;
    ALLEGRO_BITMAP** img;
    unsigned char can_shoot;
}ship;

shot* ship_straight_shoot(shot_sentinel *list, ship *shooter);

ship* add_ship();
void destroy_ship(ship* ship);

#endif //__SHIP__