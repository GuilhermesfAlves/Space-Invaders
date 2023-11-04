#ifndef __SI_SPACE__
#define __SI_SPACE__

#include <stdlib.h>
#include "enemy.h"
#include "ship.h"
#include "obstacles.h"

typedef struct{
    int min_height;
    int max_height;
    int min_width;
    int max_width;
}limits;

typedef struct {
	enemy ***map;
	int rows;
	int lines;
	ship *ship;
	obstacles *obstacles;
} space;

space* generate_board(int max_y, int max_x);
space* create_board(unsigned char difficult, limits limits);
void clean_board(space *board);
void destroy_board(space *board);

int in_limits(space* board, int pos_y, int pos_x);

#endif