#ifndef __SI_SHOTS__
#define __SI_SHOTS__

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1
#define STAY 0
#define SHOT_MOVE 11
#define ROW_SPACE 35
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


typedef struct{
	int pos_x;
	int pos_y;
	enum {SHIP_SHOT, ALIEN0_SHOT, ALIEN1_SHOT, ALIEN2_SHOT} type;
	struct shot *next;
	char trajectory;
	unsigned char damage;
	ALLEGRO_BITMAP** img1;
	ALLEGRO_BITMAP** img2;
}shot;

typedef struct{
	shot *first;
	shot *last;
} shot_sentinel;

shot* straight_shoot(shot_sentinel *list, unsigned char damage, char trajectory, short pos_x, short pos_y, unsigned char type);
shot_sentinel* create_shotlist(void);
void clean_shots(shot_sentinel *list);
shot* destroy_shot(shot* current, shot* previous, shot_sentinel *list);
void update_shots(shot_sentinel* shot_list, short lim_y);
int has_shot_in_row(shot_sentinel* shot_list, short pos_x);

#endif //__SHOTS__