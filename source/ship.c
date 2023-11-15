#include "../headers/ship.h"


ship* add_ship(){
    ship* new_ship;

    if(!(new_ship = (ship*) malloc(sizeof(ship))))
        return NULL;

    new_ship -> life = SHIP_INICIAL_LIFES;
    new_ship -> pos_x = 0;
	new_ship -> pos_y = 0;
    new_ship -> move = 0;
    new_ship -> exploded = 0;
	new_ship -> alive_img = NULL;
    new_ship -> dead_img = NULL;
    new_ship -> shot_img = NULL;
    new_ship -> death_s = NULL;
    new_ship -> shoot_s = NULL;
	new_ship -> shot_list = create_shotlist();

    return new_ship;
}

void destroy_ship(ship* ship){
    
    al_destroy_sample(ship -> death_s);
    al_destroy_sample(ship -> shoot_s);
	clean_shots(ship -> shot_list);
    free(ship);
}

int shot_in_row(ship* ship){

	for (shot* shot_aux = ship -> shot_list -> first; shot_aux; shot_aux = (shot*) shot_aux -> next)
		if ((shot_aux -> pos_x + ROW_SPACE > ship -> pos_x) && (shot_aux -> pos_x - ROW_SPACE < ship -> pos_x))
			return 1;
	
	return 0;
}