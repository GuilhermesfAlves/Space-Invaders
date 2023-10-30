#ifndef __ENEMY__
#define __ENEMY__

#include "shots.h"

typedef struct enemy{
	int pos_x;
	int pos_y;
} enemy;

int enemy_move(space *board, enemy *alien, int move_y, int move_x);

shot_t* enemy_straight_shoot(space *board, shot_sentinel *list, enemy *shooter);
int add_enemy(space *board, int pos_y, int pos_x);
int remove_enemy(space *board, int pos_y, int pos_x);

#endif