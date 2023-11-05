#include "../headers/enemy.h"
#include <stdio.h>

//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot* straight_shoot(shot_sentinel *list, enemy *shooter){
	shot* new;

	if (!(new = (shot*) malloc(sizeof(shot))))
        return NULL;

	new -> pos_x = shooter -> pos_x;
	new -> pos_y = shooter -> pos_y + DOWN;
	new -> next = NULL;
	new -> trajectory = DOWN;
	new -> img1 = NULL;
	new -> img2 = NULL;

	if (list -> last)
		list -> last -> next = (struct shot*) new;
	list -> last = new; 
	if (!list -> first)
		list -> first = new;

	return new;	
}

//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
enemy* add_enemy(int pos_y, int pos_x, int type){
	enemy* new_enemy;

	if (!(new_enemy = (enemy*) malloc(sizeof(enemy))))
		return NULL;

	printf("enemy\n");
	new_enemy -> type = type;
	new_enemy -> pos_x = pos_x;
	new_enemy -> pos_y = pos_y;
	new_enemy -> exploded = 0;
	new_enemy -> img1 = NULL;
	new_enemy -> img2 = NULL;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void* destroy_enemy(enemy* enemy){

	al_destroy_bitmap(enemy -> img1);
	al_destroy_bitmap(enemy -> img2);
	free(enemy);
	return NULL;
}
