#ifndef __SI_ENEMY__
#define __SI_ENEMY__

#include "shots.h"

typedef struct{
	enum {EASY, MEDIUM, HARD} type;
	int pos_x;
	int pos_y;
	unsigned char exploded;
	ALLEGRO_BITMAP** alive;
	ALLEGRO_BITMAP** dead;
} enemy;

enemy* add_enemy(int type);
void* destroy_enemy(enemy* enemy);
void two_enemy_shots(int pos_x, int pos_y, short lines, short rows, enemy*** map, shot_sentinel* shot_list);

#endif