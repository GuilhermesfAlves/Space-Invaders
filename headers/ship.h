#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"

typedef struct{
    int life;
    unsigned char move;
    int pos_x;
    int pos_y;
    ALLEGRO_BITMAP** img;
}ship;

shot* ship_straight_shoot(shot_sentinel *list, ship *shooter);

ship* add_ship(int pos_x, int pos_y);
void destroy_ship(ship* ship);

#endif //__SHIP__