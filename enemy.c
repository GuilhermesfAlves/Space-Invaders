#include <stdlib.h>
#include <stdio.h>
#include "enemy.h"

shot_sentinel* create_shotlist(void){
	shot_sentinel* list; 
	
	if (!(list = (shot_sentinel*) malloc (sizeof(shot_sentinel)))) 
		return NULL;
	
	list -> first = NULL;
	list -> last  = NULL;
	
	return list;
}

//IMPLEMENTAR!
//	Remove os tiros da lista
shot* remove_shot(shot* current, shot* previous, shot_sentinel *list){
	
	if (current == list -> last)
		list -> last = previous;

	if (previous)
		previous -> next = current -> next;
	else
		list -> first = current -> next;

	free(current);
	return (previous)? previous -> next: list -> first;
}

void clean_shots(shot_sentinel *list){
	shot *p;
	shot *q;

	p = (shot*) list -> first;
	q = NULL;
	
	while (p)
		p = remove_shot(p, q, list);
}

//IMPLEMENTAR!
//Os tiros presentes no tabuleiro devem ser atualizados
//  Se o tiro acertar um alvo, ou sair do tabuleiro, ele deve ser removido da lista
//  Caso contrário, ele deve "andar" uma casa (sqm) à frente
void update_shots(space *board, shot_sentinel *list){
	shot* prev;
	shot* aux;
	int i = 0;

	aux = list -> first;
	prev = NULL;

	while (aux){
		if ((aux -> position_y + 1 > board -> max_y)\
		 || (board -> map[aux -> position_y + 1][aux -> position_x].type == OBSTACLE)\
		 || (board -> map[aux -> position_y + 1][aux -> position_x].type == SHIP))
			aux = remove_shot(aux, prev, list);
		
		else{
			aux -> position_y++;
			aux = aux -> next;
		}

		if ((!prev) && (list -> first != aux))
			prev = list -> first;
		else if (prev)
			prev = prev -> next;
		
		i++;
	}
}

//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot* straight_shoot(space *board, shot_sentinel *list, enemy *shooter){
	shot* new;

	if (board -> max_y < shooter -> position_y + 1){
		fprintf(stderr, "excede limite, tiro não cabe no mapa\n");
		exit(2);
	}

	if (board -> map[shooter -> position_y + 1][shooter -> position_x].entity)
		return NULL;
		
	if (!(new = (shot*) malloc(sizeof(shot)))){
		fprintf(stderr,"erro");
		exit(1);
	}
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
