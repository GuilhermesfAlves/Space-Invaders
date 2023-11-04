#ifndef __SI_SHIP__
#define __SI_SHIP__

#include <stdlib.h>
#include "shots.h"
#include "space.h"

typedef struct{
    int life;
    unsigned char move;
    int pos_x;
    int pos_y;
}ship;

shot* ship_straight_shoot(space *board, shot_sentinel *list, ship *shooter);

ship* add_ship(int pos_x, int pos_y);
void destroy_ship(ship* ship);

#endif //__SHIP__