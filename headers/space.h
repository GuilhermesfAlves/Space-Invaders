#ifndef __SPACE__
#define __SPACE__

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1
#define STAY 0

#include <stdlib.h>

typedef struct {
	void *entity;
	enum {VACUUM, ENEMY, OBSTACLE, SHIP} type;
} sqm;

typedef struct {
	sqm **map;
	int max_x;
	int max_y;
} space;

space* create_board(int max_y, int max_x, int enemy_lines);
void clean_board(space *board);
void destroy_board(space *board);

int in_limits(space* board, int pos_y, int pos_x);

#endif
