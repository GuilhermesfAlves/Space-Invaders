#include "../headers/enemy.h"
#include <math.h>
#include <stdio.h>

//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
enemy* add_enemy(int type, char dir){
	enemy* new_enemy;

	if ((type < 0) || (type > SUPER))
		return NULL;

	if (!(new_enemy = (enemy*) malloc(sizeof(enemy))))
		return NULL;

	new_enemy -> type = type - 1;
	new_enemy -> pos_x = 0;
	new_enemy -> pos_y = 0;
	new_enemy -> exploded = 0;
	new_enemy -> power_up = 0;
	new_enemy -> alive_img = NULL;
	new_enemy -> dead_img = NULL;
	new_enemy -> shot_img = NULL;
	new_enemy -> death_s = NULL;
	new_enemy -> dir = dir;
	new_enemy -> points = (type == HARD)? 4*10: (type == SUPER)? ((rand() % 2) + 1)*150: type*10;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void* destroy_enemy(enemy* enemy){

	al_destroy_sample(enemy -> death_s);
	free(enemy);
	return NULL;
}

int already_shooten(enemy* new, enemy** shooten){

	for (int i = 0; (i < ENEMIES_TO_SHOOT) && (shooten[i]); i++)
		if (new == shooten[i])
			return 1;

	return 0;
}

void enemy_shots(int pos_x, int pos_y, short lines, short rows, enemy*** map, shot_sentinel* shot_list){
	enemy** closer;
	float distance;
	float distance_closer;

	if (!(closer = (enemy**) calloc(ENEMIES_TO_SHOOT, sizeof(enemy*))))
		return;

	for (int e = 0; e < ENEMIES_TO_SHOOT; e++){
		distance_closer = 5000;
		for (int i = 0; i < lines; i++){
			for (int j = 0; j < rows; j++){
				if ((!map[i][j]) || (map[i][j] -> exploded) || (already_shooten(map[i][j], closer)))
					continue;

				distance = sqrt(pow(map[i][j] -> pos_x - pos_x, 2) + pow(map[i][j] -> pos_y - pos_y, 2));

				if ((!closer[e]) || (distance < distance_closer) && ((map[i][j] -> type + 1 == HARD) || (((map[i][j] -> type + 1 == MEDIUM) || (i == lines - 1) || (!map[i + 1][j])) && (!has_shot_in_row(shot_list, map[i][j] -> pos_x))))){
					closer[e] = map[i][j];
					distance_closer = distance;
				}
			}
		}
	}
	shot* shot;
	for (int i = 0; (i < ENEMIES_TO_SHOOT) && (closer[i]); i++){
		shot = straight_shoot(shot_list, (closer[i] -> type == HARD)? 2:1, STAY, DOWN, closer[i] -> pos_x, closer[i] -> pos_y, closer[i] -> type + 1);
		if (shot)
			shot -> img = closer[i] -> shot_img;
	}
	free(closer);
}