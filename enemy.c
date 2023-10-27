#include <stdlib.h>
#include "enemy.h"


//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot_t* straight_shoot(space *board, shot_sentinel *list, enemy *shooter){
	shot_t* new;

	if (board -> max_y < shooter -> position_y + 1)
		return NULL;
		
	if (board -> map[shooter -> position_y + 1][shooter -> position_x].entity)
		return NULL;
		
	if (!(new = (shot_t*) malloc(sizeof(shot_t))))
        return NULL;
	new -> position_x = shooter -> position_x;
	new -> position_y = shooter -> position_y + 1;
	new -> next = NULL;
	new -> trajectory = 0;

	if (list -> last)
		list -> last -> next = new;
	list -> last = new; 
	if (!list -> first)
		list -> first = new;

	return new;	
}

//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo
int add_enemy(space *board, int position_y, int position_x){
	enemy* new;

	if ((position_x > board -> max_x) || (position_x < 1))
		return 0;
	if ((position_y > board -> max_y) || (position_y < 1))
		return 0;

	if (!(new = malloc(sizeof(enemy))))
		return 0;

	new -> position_x = position_x;
	new -> position_y = position_y;

	board -> map[position_y][position_x].entity = new;
	board -> map[position_y][position_x].type = ENEMY;
	return 1;
}

//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo
int remove_enemy(space *board, int position_y, int position_x){

	if ((position_x > board -> max_x) || (position_x < 0))
		return 0;
	if ((position_y > board -> max_y) || (position_y < 0))
		return 0;

	free(board -> map[position_y][position_x].entity);

	return 1;
}
