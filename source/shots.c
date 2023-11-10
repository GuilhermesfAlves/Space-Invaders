#include "../headers/shots.h"

shot_sentinel* create_shotlist(void){
	shot_sentinel* list; 
	
	if (!(list = (shot_sentinel*) malloc (sizeof(shot_sentinel)))) 
		return NULL;
	
	list -> first = NULL;
	list -> last  = NULL;
	
	return list;
}

shot* straight_shoot(shot_sentinel *list, unsigned char damage, char trajectory, short pos_x, short pos_y, unsigned char type){
	shot* new_shot;

	if ((type != 2) && (has_shot_in_row(list, pos_x)))
		return NULL;
		
	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;

	new_shot -> pos_x = pos_x;
	new_shot -> pos_y = pos_y;
	new_shot -> next = NULL;
	new_shot -> type = type;
	new_shot -> damage = damage;
	new_shot -> trajectory = trajectory;
	new_shot -> img = NULL;

	if (list -> last)
		list -> last -> next = (struct shot*) new_shot;
	list -> last = new_shot;
	if (!list -> first)
		list -> first = new_shot;

	return new_shot;
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

	p = list -> first;
	
	while (p)
		p = destroy_shot(p, NULL, list);
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

int has_shot_in_row(shot_sentinel* shot_list, short pos_x){

	for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = (shot*) shot_aux -> next)
		if ((shot_aux -> pos_x + ROW_SPACE > pos_x) && (shot_aux -> pos_x - ROW_SPACE < pos_x))
			return 1;
	
	return 0;
}