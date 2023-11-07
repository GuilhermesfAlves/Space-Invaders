#include "../headers/ship.h"

shot* ship_straight_shoot(shot_sentinel *list, ship *ship){
	shot* new_shot;

	if (ship -> can_shoot)
		return NULL;

	if (!(new_shot = (shot*) malloc(sizeof(shot))))
        return NULL;
	new_shot -> pos_x = ship -> pos_x;
	new_shot -> pos_y = ship -> pos_y + UP - al_get_bitmap_height(*(ship) -> img)/2;
	new_shot -> next = NULL;
	new_shot -> trajectory = UP;
	new_shot -> type = SHIP_SHOT;
	new_shot -> img1 = NULL;
	new_shot -> img2 = NULL;
	ship -> can_shoot = 0;

	if (list -> last)
		list -> last -> next = (struct shot*) new_shot;
	list -> last = new_shot; 
	if (!list -> first)
		list -> first = new_shot;

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

    return new_ship;
}

void destroy_ship(ship* ship){
    
    free(ship);
}