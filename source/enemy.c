#include "../headers/enemy.h"
#include <stdio.h>

//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot* straight_shoot(shot_sentinel *list, enemy *shooter){
	shot* new_shot;

	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;

	new_shot -> pos_x = shooter -> pos_x;
	new_shot -> pos_y = shooter -> pos_y + DOWN;
	new_shot -> next = NULL;
	new_shot -> trajectory = DOWN;
	new_shot -> type = (shooter -> type == 2)? ALIEN2_SHOT: ALIEN0_SHOT;
	new_shot -> img1 = NULL;
	new_shot -> img2 = NULL;

	if (list -> last)
		list -> last -> next = (struct shot*) new_shot;
	list -> last = new_shot; 
	if (!list -> first)
		list -> first = new_shot;

	return new_shot;	
}

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
	new_enemy -> img1 = NULL;
	new_enemy -> img2 = NULL;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void destroy_enemy(enemy* enemy){

	free(enemy);
}
