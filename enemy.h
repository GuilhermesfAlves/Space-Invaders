#ifndef __ENEMY__
#define __ENEMY__

#include "shots.h"

typedef struct enemy{
	int position_x;
	int position_y;
} enemy;

shot_t* enemy_straight_shoot(space *board, shot_sentinel *list, enemy *shooter);
int add_enemy(space *board, int position_y, int position_x);
int remove_enemy(space *board, int position_y, int position_x);

#endif