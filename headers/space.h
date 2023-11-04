#ifndef __SI_SPACE__
#define __SI_SPACE__

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1
#define STAY 0
#include <stdlib.h>
#include "enemy.h"
#include "ship.h"
#include "obstacles.h"

typedef struct {
	enemy ***map;
	int max_x;
	int max_y;
	ship *ship;
	obstacles *obstacles;
} space;

space* create_board(int max_y, int max_x, int enemy_lines);
void clean_board(space *board);
void destroy_board(space *board);

int in_limits(space* board, int pos_y, int pos_x);

#endif
