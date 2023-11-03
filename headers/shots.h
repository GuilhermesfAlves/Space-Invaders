#ifndef __SHOTS__
#define __SHOTS__

#include "space.h"

typedef struct{
	int pos_x;
	int pos_y;
	int trajectory;
	shot *next;
}shot;

typedef struct{
	shot *first;
	shot *last;
} shot_sentinel;

shot_sentinel* create_shotlist(void);
void clean_shots(shot_sentinel *list);
shot* remove_shot(shot* current, shot* previous, shot_sentinel *list);
// void update_shots(space *board, shot_sentinel *list);

#endif //__SHOTS__