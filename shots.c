#include "shots.h"
#include <stdlib.h>

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
shot_t* remove_shot(shot_t* current, shot_t* previous, shot_sentinel *list){
	
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
	shot_t *p;
	shot_t *q;

	p = (shot_t*) list -> first;
	q = NULL;
	
	while (p)
		p = remove_shot(p, q, list);
}

//IMPLEMENTAR!
//Os tiros presentes no tabuleiro devem ser atualizados
//  Se o tiro acertar um alvo, ou sair do tabuleiro, ele deve ser removido da lista
//  Caso contrário, ele deve "andar" uma casa (sqm) à frente
void update_shots(space *board, shot_sentinel *list){
	shot_t* prev;
	shot_t* aux;
	int i = 0;

	aux = list -> first;
	prev = NULL;

	while (aux){
		if ((aux -> position_y + DOWN > board -> max_y)\
		 || (board -> map[aux -> position_y + DOWN][aux -> position_x].type == OBSTACLE)\
		 || (board -> map[aux -> position_y + DOWN][aux -> position_x].type == SHIP))
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
