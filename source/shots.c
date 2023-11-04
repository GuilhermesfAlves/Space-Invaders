#include "../headers/shots.h"

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
shot* destroy_shot(shot* current, shot* previous, shot_sentinel *list){
	
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
// void update_shots(space *board, shot_sentinel *list){
// 	shot* prev;
// 	shot* aux;
// 	int i = 0;

// 	aux = list -> first;
// 	prev = NULL;

// 	while (aux){
// 		if (aux -> pos_y + aux -> trajectory > board -> max_y)
// 			aux = remove_shot(aux, prev, list);
// 		else if (board -> map[aux -> pos_y + aux -> trajectory][aux -> pos_x].type == OBSTACLE){
// 			// board -> map[aux -> pos_y + aux -> trajectory][aux -> pos_x].type DIMINUI A VIDA
// 			//CONFERE SE AINDA HÁ VIDA
// 			aux = remove_shot(aux, prev, list);
// 		}
// 		else if (board -> map[aux -> pos_y + aux -> trajectory][aux -> pos_x].type == SHIP){
// 			//board -> map[aux -> pos_y + aux -> trajectory][aux -> pos_x].entity DIMINUI VIDA
// 			//CONFERE SE AINDA HÁ VIDA
// 			aux = remove_shot(aux, prev, list);
// 		}
// 		else{
// 			aux -> pos_y++;
// 			aux = aux -> next;
// 		}

// 		if ((!prev) && (list -> first != aux))
// 			prev = list -> first;
// 		else if (prev)
// 			prev = prev -> next;
		
// 		i++;
// 	}
// }
