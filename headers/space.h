#ifndef __SI_SPACE__
#define __SI_SPACE__

#include "enemy.h"
#include "ship.h"
#include "obstacles.h"
#include "difficult.h"
#include "power_up.h"

#define ALIEN_STEP 30
#define SUPER_ALIEN_STEP 4

typedef struct{
    int min_width;
    int max_width;
    int min_height;
    int max_height;
}limits;

typedef struct {
	char rows;
	char lines;
	ship *ship;
	enemy ***map;
	enemy* super_alien;
	obstacles **obstacles;
	shot_sentinel* shot_list;
	shot_sentinel* super_shot;
	unsigned char qtd_obstacles;
	power_up_list* power_up_list;
} space;

space* generate_space(int max_y, int max_x);
int set_formation(char* rows, char* lines, char* difficult, unsigned char* qtd_obstacles, char* qtd_power_ups, char* vec_y, char *blanck_row);
void add_aliens(space* space, char* vec, char* blank_row);
space* create_space(unsigned char difficult, limits limits);
void clean_space(space *space);
void destroy_space(space *space);

int move_aliens(space* space, limits limits, int mov_x);
int has_alien(space* space);

enemy* get_explod(enemy* enemy);
void get_exploded(space* space);
void hit_obstacles(obstacles** obstacles, unsigned char qtd_obstaclees, shot_sentinel* shot_list);
short hit_alien(enemy* enemy, shot_sentinel* shot_list);
short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows, shot_sentinel* shot_list);
void hit_shots(shot_sentinel* ship_list, shot_sentinel* enemy_list);
void hit_ship(ship* ship, shot_sentinel* shot_list);

void set_random_power_ups(enemy*** map, int lines, int rows, int power_up_qtd);
void ship_got_power_up(space* space);

#endif