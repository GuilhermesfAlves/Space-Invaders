#ifndef __SI_SHOTS__
#define __SI_SHOTS__

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1
#define STAY 0
#define SHOT_MOVE 11
#define ROW_SPACE 32
#include <stdlib.h>

#include "allegro_headers.h"

enum type_shooter {SHIP, EASY, MEDIUM, HARD, SUPER};

typedef struct shot{
	int pos_x;
	int pos_y;
	char type;
	struct shot *next;
	struct shot *prev;
	char trajectory_x;
	char trajectory_y;
	unsigned char damage;
	ALLEGRO_BITMAP** img;
}shot;

typedef struct{
	shot *first;
	shot *last;
} shot_sentinel;

//cria um shot e insere ele numa shot_list
shot* straight_shoot(shot_sentinel *list, unsigned char damage, char trajectory_x, char trajectory_y, short pos_x, short pos_y, unsigned char type);
//cria uma shot_list 
shot_sentinel* create_shotlist();
//limpa todos os tiros em uma shot_list
void clean_shots(shot_sentinel *list);
//destroi uma shot_list
void destroy_shot_list(shot_sentinel *list);
//destroi um tiro de um shot_list
shot* destroy_shot(shot* current, shot_sentinel *list);
//avança todos os tiros para sua direção 
void update_shots(shot_sentinel* shot_list, short lim_y, short max_x, short min_x);
//confere se há algum tiro em uma shot_list que esteja à uma distância menor que ROW_SPACE
int has_shot_in_row(shot_sentinel* shot_list, short pos_x);

#endif //__SHOTS__