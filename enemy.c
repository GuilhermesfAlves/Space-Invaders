#include <stdlib.h>
#include "enemy.h"

int enemy_move(space *board, enemy *alien, int move_y, int move_x){
	int pos_x = alien -> pos_x;
	int pos_y = alien -> pos_y;

	if (board -> map[pos_y][pos_x].type != ENEMY)
		return STAY;

	if ((move_x == 0) && (move_y == 0))
		return STAY;

	if ((move_x) && in_limits(board, pos_y, pos_x + move_x)){
		board -> map[pos_y][pos_x + move_x].entity = board -> map[pos_y][pos_x].entity;
		board -> map[pos_y][pos_x + move_x].type = ENEMY;
		alien -> pos_x = pos_x + move_x;
		return (move_x > 0)? LEFT: RIGHT;
	}
	if ((move_y) && (in_limits(board, pos_y + move_y, pos_x))){
		board -> map[pos_y + move_y][pos_x].entity = board -> map[pos_y][pos_x].entity;
		board -> map[pos_y + move_y][pos_x].type = ENEMY;
		alien -> pos_y = pos_y + move_y;
		return (move_y > 0)? UP: DOWN;
	}
	board -> map[pos_x][pos_y].entity = NULL;
	board -> map[pos_x][pos_y].type = VACUUM;
}

//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot_t* straight_shoot(space *board, shot_sentinel *list, enemy *shooter){
	shot_t* new;

	if (board -> max_y < shooter -> pos_y + DOWN)
		return NULL;
		
	if (board -> map[shooter -> pos_y + DOWN][shooter -> pos_x].entity)
		return NULL;
		
	if (!(new = (shot_t*) malloc(sizeof(shot_t))))
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
int add_enemy(space *board, int pos_y, int pos_x){
	enemy* new;

	if (!in_limits(board,pos_y,pos_x))
		return 0;

	if (!(new = malloc(sizeof(enemy))))
		return 0;

	new -> pos_x = pos_x;
	new -> pos_y = pos_y;

	board -> map[pos_y][pos_x].entity = new;
	board -> map[pos_y][pos_x].type = ENEMY;
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
