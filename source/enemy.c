#include "../headers/enemy.h"
#include <math.h>
#include <stdio.h>

//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
enemy* add_enemy(int type, char dir){
	enemy* new_enemy;

	if (!(new_enemy = (enemy*) malloc(sizeof(enemy))))
		return NULL;

	new_enemy -> type = type - 1;
	new_enemy -> pos_x = 0;
	new_enemy -> pos_y = 0;
	new_enemy -> exploded = 0;
	new_enemy -> alive = NULL;
	new_enemy -> dead = NULL;
	new_enemy -> dir = dir;
	new_enemy -> points = (type == HARD)? 4*10: (type == SUPER)? 150: type*10;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void* destroy_enemy(enemy* enemy){

	free(enemy);
	return NULL;
}

void two_enemy_shots(int pos_x, int pos_y, short lines, short rows, enemy*** map, shot_sentinel* shot_list){
	enemy* closer[2] = {NULL, NULL};
	float distance;
	float distance_closer;

	for (int e = 0; e < 2; e++){
		for (int i = 0; i < lines; i++){
			for (int j = 0; j < rows; j++){
				if ((!map[i][j]) || (map[i][j] -> exploded))
					continue;

				if (!closer[e]){
					closer[e] = map[i][j];
					distance_closer = sqrt(pow(map[i][j] -> pos_x - pos_x, 2) + pow(map[i][j] -> pos_y - pos_y, 2));
				}
				distance = sqrt(pow(map[i][j] -> pos_x - pos_x, 2) + pow(map[i][j] -> pos_y - pos_y, 2));
				
				if ((distance < distance_closer) && ((e == 0) || (closer[0] != map[i][j]))){
					closer[e] = map[i][j];
					distance_closer = distance;
				}
			}
		}
	}

	straight_shoot(shot_list, (closer[0] -> type == HARD)? 2:1, STAY, DOWN, closer[0] -> pos_x, closer[0] -> pos_y, closer[0] -> type + 1);
	straight_shoot(shot_list, (closer[1] -> type == HARD)? 2:1, STAY, DOWN, closer[1] -> pos_x, closer[1] -> pos_y, closer[1] -> type + 1);
}