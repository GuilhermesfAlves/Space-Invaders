#include "../headers/enemy.h"
#include <stdio.h>
//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
enemy* add_enemy(int type){
	enemy* new_enemy;

	if (!(new_enemy = (enemy*) malloc(sizeof(enemy))))
		return NULL;

	new_enemy -> type = type;
	new_enemy -> pos_x = 0;
	new_enemy -> pos_y = 0;
	new_enemy -> exploded = 0;
	new_enemy -> alive = NULL;
	new_enemy -> dead = NULL;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void* destroy_enemy(enemy* enemy){

	free(enemy);
	return NULL;
}
