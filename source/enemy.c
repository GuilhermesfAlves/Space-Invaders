#include "../headers/enemy.h"


//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot* straight_shoot(space *board, shot_sentinel *list, enemy *shooter){
	shot* new;

	if (board -> max_y < shooter -> pos_y + DOWN)
		return NULL;
		
	if (board -> map[shooter -> pos_y + DOWN][shooter -> pos_x].entity)
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
int add_enemy(space *board, int pos_y, int pos_x, int type){
	enemy* new;

	if (!in_limits(board,pos_y,pos_x))
		return 0;

	if (!(new = malloc(sizeof(enemy))))
		return 0;

	new -> type = type;
	new -> pos_x = pos_x;
	new -> pos_y = pos_y;

	board -> map[pos_y][pos_x].entity = new;
	//board -> map[pos_y][pos_x].type = ENEMY;
	return 1;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
int remove_enemy(space *board, int pos_y, int pos_x){

	if (!in_limits(board, pos_y, pos_x))
		return 0;

	free(board -> map[pos_y][pos_x].entity);

	return 1;
}
