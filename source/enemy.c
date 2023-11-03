#include "../headers/enemy.h"


//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot* straight_shoot(space *board, shot_sentinel *list, enemy *shooter){
	shot* new;

	if (board -> max_y < shooter -> pos_y + DOWN)
		return NULL;
		
	if (!(new = (shot*) malloc(sizeof(shot))))
        return NULL;

	new -> pos_x = shooter -> pos_x;
	new -> pos_y = shooter -> pos_y + DOWN;
	new -> next = NULL;
	new -> trajectory = DOWN;

	if (list -> last)
		list -> last -> next = new;
	list -> last = new; 
	if (!list -> first)
		list -> first = new;

	return new;	
}

//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
enemy* add_enemy(int pos_y, int pos_x, int type){
	enemy* new_enemy;

	if (!(new_enemy = malloc(sizeof(enemy))))
		return 0;

	new_enemy -> type = type;
	new_enemy -> pos_x = pos_x;
	new_enemy -> pos_y = pos_y;

	return new_enemy;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
void remove_enemy(space *board, int pos_y, int pos_x){

	free(board -> map[pos_y][pos_x]);
}
