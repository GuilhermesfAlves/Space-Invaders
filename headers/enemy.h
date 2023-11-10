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

enemy* add_enemy(int type);
enemy* destroy_enemy(enemy* enemy);

#endif