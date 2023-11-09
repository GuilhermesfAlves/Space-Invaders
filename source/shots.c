#include "../headers/shots.h"
 #include <stdio.h>
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
		list -> first = (shot*) current -> next;

	free(current);
	return (previous)? (shot*) previous: list -> first;
}

void clean_shots(shot_sentinel *list){
	shot *p;
	shot *q;

	p = (shot*) list -> first;
	q = NULL;
	
	while (p)
		p = destroy_shot(p, q, list);
}

void update_shots(shot_sentinel* shot_list, short lim_y){
	shot* previous = NULL;
	char alt;

	for (shot* shot_aux = shot_list -> first; shot_aux; ){
		alt = 0;
		shot_aux -> pos_y += SHOT_MOVE*shot_aux -> trajectory;

		if (shot_aux -> pos_y*shot_aux -> trajectory > lim_y*shot_aux -> trajectory){
			alt = 1;
			shot_aux = destroy_shot(shot_aux, previous, shot_list);
		}

		if ((!previous) || (shot_list -> first == shot_aux))
			previous = shot_aux;
		else if (previous)
			previous = (shot*) previous -> next;
		if ((shot_aux) && (!alt))
			shot_aux = (shot*) shot_aux -> next;
	}
}