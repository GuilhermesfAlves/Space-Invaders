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

shot* straight_shoot(shot_sentinel *list, unsigned char damage, char trajectory, short pos_x, short pos_y, unsigned char type){
	shot* new_shot;

	if ((type != ALIEN2_SHOT) && (has_shot_in_row(list, pos_x)))
		return NULL;
		
	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;

	new_shot -> pos_x = pos_x;
	new_shot -> pos_y = pos_y;
	new_shot -> next = NULL;
	new_shot -> prev = list -> last;
	new_shot -> type = type;
	new_shot -> damage = damage;
	new_shot -> trajectory = trajectory;
	new_shot -> img = NULL;

	if (list -> last)
		list -> last -> next = new_shot;
	list -> last = new_shot;
	if (!list -> first)
		list -> first = new_shot;

	return new_shot;
}


//IMPLEMENTAR!
//	Remove os tiros da lista
shot* destroy_shot(shot* current, shot_sentinel *list){
	shot* temp;

	if (list -> first == current)
		list -> first = current -> next;
	if (list -> last == current)
		list -> last = current -> prev;

	if (current -> prev)
		current -> prev -> next = current -> next;
	if (current -> next)
		current -> next -> prev = current -> prev;

	temp = current;
	current = current -> next;
	free(temp);

	return current;
}

void clean_shots(shot_sentinel *list){

	for (shot* p = list -> first; p; p = (shot*) p -> next)
		destroy_shot(p, list);
}

void update_shots(shot_sentinel* shot_list, short lim_y){

	for (shot* shot_aux = shot_list -> first; shot_aux; ){
		shot_aux -> pos_y += SHOT_MOVE*shot_aux -> trajectory;

		if (shot_aux -> pos_y*shot_aux -> trajectory > lim_y*shot_aux -> trajectory)
			shot_aux = destroy_shot(shot_aux, shot_list);
		else
			shot_aux = shot_aux -> next;
	}
}

int has_shot_in_row(shot_sentinel* shot_list, short pos_x){

	for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = shot_aux -> next)
		if ((shot_aux -> pos_x + ROW_SPACE > pos_x) && (shot_aux -> pos_x - ROW_SPACE < pos_x))
			return 1;
	
	return 0;
}