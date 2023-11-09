#ifndef __SI_SPACE__
#define __SI_SPACE__

#include <stdlib.h>
#include "enemy.h"
#include "ship.h"
#include "obstacles.h"

#define ALIEN_STEP 20

typedef struct{
    int min_width;
    int max_width;
    int min_height;
    int max_height;
}limits;

typedef struct {
	int rows;
	int lines;
	ship *ship;
	enemy ***map;
	obstacles **obstacles;
	shot_sentinel* shot_list;
	unsigned char qtd_obstacles;
} space;

space* generate_board(int max_y, int max_x);
space* create_board(unsigned char difficult, limits limits);
void clean_board(space *board);
void destroy_board(space *board);

int move_aliens(space* space, limits limits, int mov_x);

void hit_obstacles(obstacles** obstacles, unsigned char qtd_obstaclees, shot_sentinel* shot_list);
short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows, shot_sentinel* shot_list);
void hit_shots(shot_sentinel* ship_list, shot_sentinel* enemy_list);
void hit_ship(ship* ship, shot_sentinel* shot_list);

#endif