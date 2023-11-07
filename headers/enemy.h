#ifndef __SI_ENEMY__
#define __SI_ENEMY__

#include "shots.h"

typedef struct{
	enum {EASY, MEDIUM, HARD} type;
	int pos_x;
	int pos_y;
	unsigned char exploded;
	ALLEGRO_BITMAP** img1;
	ALLEGRO_BITMAP** img2;
} enemy;

shot* enemy_straight_shoot(shot_sentinel *list, enemy *shooter);
enemy* add_enemy(int type);
void destroy_enemy(enemy* enemy);

#endif