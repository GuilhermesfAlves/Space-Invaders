#ifndef __SI_SPACE__
#define __SI_SPACE__

#include <stdlib.h>
#include "enemy.h"
#include "ship.h"
#include "obstacles.h"

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

#endif