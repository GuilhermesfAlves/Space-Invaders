#include "../headers/ship.h"

shot* ship_straight_shoot(ship *ship){
	shot* new_shot;

	if (ship -> shots)
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

	return new_shot;	
}

void* destroy_ship_shot(ship* ship){

	free(ship -> shots);
	ship -> shots = NULL;
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