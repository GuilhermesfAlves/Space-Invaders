#ifndef __ENEMY__
#define __ENEMY__

#include "shots.h"

typedef struct{
	enum {EASY, MEDIUM, HARD} type;
	int pos_x;
	int pos_y;
} enemy;

shot* enemy_straight_shoot(space *board, shot_sentinel *list, enemy *shooter);
enemy* add_enemy(int pos_y, int pos_x, int type);
void remove_enemy(space *board, int i, int j);

#endif