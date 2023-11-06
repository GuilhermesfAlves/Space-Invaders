#ifndef __SI_SHOTS__
#define __SI_SHOTS__

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1
#define STAY 0
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


typedef struct{
	int pos_x;
	int pos_y;
	int trajectory;
	struct shot *next;
	ALLEGRO_BITMAP** img1;
	ALLEGRO_BITMAP** img2;
}shot;

typedef struct{
	shot *first;
	shot *last;
} shot_sentinel;

shot_sentinel* create_shotlist(void);
void clean_shots(shot_sentinel *list);
shot* destroy_shot(shot* current, shot* previous, shot_sentinel *list);
// void update_shots(space *board, shot_sentinel *list);

#endif //__SHOTS__