#ifndef __SHOTS__
#define __SHOTS__

#include "space.h"

typedef struct shot{
	int pos_x;
	int pos_y;
	int trajectory;
	struct shot *next;
}shot_t;

typedef struct shot_sentinel{
	shot_t *first;
	shot_t *last;
} shot_sentinel;

shot_sentinel* create_shotlist(void);
void clean_shots(shot_sentinel *list);
shot_t* remove_shot(shot_t* current, shot_t* previous, shot_sentinel *list);
void update_shots(space *board, shot_sentinel *list);

#endif //__SHOTS__