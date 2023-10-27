#include "ship.h"

//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente
shot_t* ship_straight_shoot(space *board, shot_sentinel *list, ship_t *ship){
	shot_t* new_shot;
		
	if (board -> map[ship -> pos_y + 1][ship -> pos_x].entity)
		return NULL;
		
	if (!(new_shot = (shot_t*) malloc(sizeof(shot_t))))
        return NULL;
	new_shot -> position_x = ship -> pos_x;
	new_shot -> position_y = ship -> pos_y - 1;
	new_shot -> next = NULL;
	new_shot -> trajectory = 0;

	if (list -> last)
		list -> last -> next = new_shot;
	list -> last = new_shot; 
	if (!list -> first)
		list -> first = new_shot;

	return new_shot;	
}

ship_t* add_ship(int pos_x){
    ship_t* new_ship;

    if(!(new_ship = (ship_t*) malloc(sizeof(ship_t))))
        return NULL;

    new_ship -> life = 3;
    new_ship -> pos_x = pos_x;
    new_ship -> move.left = 0;
    new_ship -> move.right = 0;

    return new_ship;
}

void remove_ship(ship_t* ship){
    
    free(ship);
}