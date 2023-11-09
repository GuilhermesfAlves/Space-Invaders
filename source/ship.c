#include "../headers/ship.h"

shot* ship_straight_shoot(ship *ship){
	shot* new_shot;

	if (shot_in_row(ship))
		return NULL;
	
	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;

	new_shot -> pos_x = ship -> pos_x;
	new_shot -> pos_y = ship -> pos_y;
	new_shot -> next = NULL;
	new_shot -> type = SHIP_SHOT;
	new_shot -> damage = 1;
	new_shot -> trajectory = UP;
	new_shot -> img1 = NULL;
	new_shot -> img2 = NULL;

	if (ship -> shots -> last)
		ship -> shots -> last -> next = (struct shot*) new_shot;
	ship -> shots -> last = new_shot; 
	if (!ship -> shots -> first)
		ship -> shots -> first = new_shot;

	return new_shot;	
}

ship* add_ship(){
    ship* new_ship;

    if(!(new_ship = (ship*) malloc(sizeof(ship))))
        return NULL;

    new_ship -> life = SHIP_LIFES;
    new_ship -> pos_x = 0;
	new_ship -> pos_y = 0;
    new_ship -> move = 0;
	new_ship -> img = NULL;
	new_ship -> shots = create_shotlist();

    return new_ship;
}

void destroy_ship(ship* ship){
    
    free(ship);
}

int shot_in_row(ship* ship){

	for (shot* shot_aux = ship -> shots -> first; shot_aux; shot_aux = (shot*) shot_aux -> next)
		if ((shot_aux -> pos_x + ROW_SPACE > ship -> pos_x) && (shot_aux -> pos_x - ROW_SPACE < ship -> pos_x))
			return 1;
	
	return 0;
}