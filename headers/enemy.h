#ifndef __SI_ENEMY__
#define __SI_ENEMY__

#include "shots.h"

#define ENEMIES_TO_SHOOT 2

typedef struct{
	char type;
	int pos_x;
	int pos_y;
	char dir;
	short points;
	char power_up;
	unsigned char exploded;
	ALLEGRO_BITMAP** alive_img;
	ALLEGRO_BITMAP** dead_img;
	ALLEGRO_BITMAP** shot_img;
	ALLEGRO_SAMPLE* death_s;
} enemy;

enemy* add_enemy(int type, char dir);
void* destroy_enemy(enemy* enemy);
void two_enemy_shots(int pos_x, int pos_y, short lines, short rows, enemy*** map, shot_sentinel* shot_list);

#endif