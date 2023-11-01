#ifndef __ENEMY__
#define __ENEMY__

#include "shots.h"

typedef struct enemy{
	enum {EASY, MEDIUM, HARD} type;
	int pos_x;
	int pos_y;
} enemy;

shot_t* enemy_straight_shoot(space *board, shot_sentinel *list, enemy *shooter);
int add_enemy(space *board, int pos_y, int pos_x, int type);
int remove_enemy(space *board, int pos_y, int pos_x);

#endif