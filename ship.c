#include "ship.h"

void ship_move(space *board, ship_t* ship){

	if (board -> map[ship -> pos_x][ship -> pos_y].type != SHIP)
		return;

	if ((ship -> move != 0) && (in_limits(board, ship -> pos_y, ship -> pos_x + ship -> move))){
		board -> map[ship -> pos_x + ship -> move][ship -> pos_y].entity = board -> map[ship -> pos_x][ship -> pos_y].entity;
		board -> map[ship -> pos_x + ship -> move][ship -> pos_y].type = SHIP;
		board -> map[ship -> pos_x][ship -> pos_y].entity = NULL;
		board -> map[ship -> pos_x][ship -> pos_y].type = VACUUM;
		ship -> move += (ship -> move > 0)? -1: 1;
	}
}

shot_t* ship_straight_shoot(space *board, shot_sentinel *list, ship_t *ship){
	shot_t* new_shot;
		
	if (board -> map[ship -> pos_y + UP][ship -> pos_x].entity)
		return NULL;
		
	if (!(new_shot = (shot_t*) malloc(sizeof(shot_t))))
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

ship_t* add_ship(int pos_x, int pos_y){
    ship_t* new_ship;

    if(!(new_ship = (ship_t*) malloc(sizeof(ship_t))))
        return NULL;

    new_ship -> life = 3;
    new_ship -> pos_x = pos_x;
	new_ship -> pos_y = pos_y;
    new_ship -> move = 0;

    return new_ship;
}

void remove_ship(ship_t* ship){
    
    free(ship);
}