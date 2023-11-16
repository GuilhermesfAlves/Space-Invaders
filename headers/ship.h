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
    unsigned char exploded;
    unsigned char power_up_type;
    short int power_up_eff;
    shot_sentinel* shot_list;
    ALLEGRO_BITMAP** alive_img;
    ALLEGRO_BITMAP** dead_img;
    ALLEGRO_BITMAP** shot_img;
    ALLEGRO_SAMPLE* shoot_s;
    ALLEGRO_SAMPLE* death_s;
}ship;

shot* ship_straight_shoot(ship *ship);
ship* add_ship();
void destroy_ship(ship* ship);
int shot_in_row(ship* ship);

#endif //__SHIP__