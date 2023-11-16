#include "../headers/power_up.h"

power_up_list* create_power_up_list(){
    power_up_list* new_power_up_list;

    if (!(new_power_up_list = (power_up_list*) malloc(sizeof(power_up_list))))
        return NULL;

    new_power_up_list -> first = NULL;
    new_power_up_list -> last = NULL;

    return new_power_up_list;
}

void destroy_power_up_list(power_up_list* power_up_list){

    for (power_up* aux_power_up = power_up_list -> first; aux_power_up; aux_power_up = aux_power_up -> next)
        destroy_power_up(aux_power_up, power_up_list);
}

power_up* add_power_up(char type, int pos_x, int pos_y, power_up_list* power_up_list){
    power_up* new_power_up;
    
    if (!(new_power_up = (power_up*) malloc(sizeof(power_up))))
        return NULL;

    new_power_up -> img = NULL;
    new_power_up -> pos_x = pos_x;
    new_power_up -> pos_y = pos_y + 20;
    new_power_up -> type = type;
    new_power_up -> next = NULL;
    new_power_up -> previous = power_up_list -> last;

	if (power_up_list -> last)
		power_up_list -> last -> next = new_power_up;
	power_up_list -> last = new_power_up;
	if (!power_up_list -> first)
		power_up_list -> first = new_power_up;

    return new_power_up;
}

power_up* destroy_power_up(power_up* current, power_up_list* power_up_list){
    power_up* tmp;

    if (power_up_list -> first == current)
        power_up_list -> first = current -> next;
    if (power_up_list -> last == current)
        power_up_list -> last = current -> previous;

    if (current -> previous)
        current -> previous -> next = current -> next;
    if (current -> next)
        current -> next -> previous = current -> previous;

    tmp = current;
    current = current -> next;
    free(tmp);

    return current;
}