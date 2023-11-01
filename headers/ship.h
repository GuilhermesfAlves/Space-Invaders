#ifndef __SHIP__
#define __SHIP__

#include <stdlib.h>
#include "shots.h"

typedef struct ship{
    int life;
    short move;
    int pos_x;
    int pos_y;
}ship_t;

shot_t* ship_straight_shoot(space *board, shot_sentinel *list, ship_t *shooter);

ship_t* add_ship(int pos_x, int pos_y);
void remove_ship(ship_t* ship);

#endif //__SHIP__