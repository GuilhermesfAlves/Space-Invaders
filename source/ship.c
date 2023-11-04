#include "../headers/ship.h"

shot* ship_straight_shoot(space *board, shot_sentinel *list, ship *ship){
	shot* new_shot;
		
	//if (board -> map[ship -> pos_y + UP][ship -> pos_x].entity)
		return NULL;
		
	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;
	new_shot -> pos_x = ship -> pos_x;
	new_shot -> pos_y = ship -> pos_y + UP;
	new_shot -> next = NULL;
	new_shot -> trajectory = UP;

	if (list -> last)
		list -> last -> next = new_shot;
	list -> last = new_shot; 
	if (!list -> first)
		list -> first = new_shot;

	return new_shot;	
}

ship* add_ship(int pos_x, int pos_y){
    ship* new_ship;

    if(!(new_ship = (ship*) malloc(sizeof(ship))))
        return NULL;

    new_ship -> life = 3;
    new_ship -> pos_x = pos_x;
	new_ship -> pos_y = pos_y;
    new_ship -> move = 0;

    return new_ship;
}

void destroy_ship(ship* ship){
    
    free(ship);
}