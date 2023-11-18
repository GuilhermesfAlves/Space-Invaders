#include "../headers/ship.h"
#include <stdlib.h>

ship* add_ship(){
    ship* new_ship;

    if(!(new_ship = (ship*) malloc(sizeof(ship))))
        return NULL;

    new_ship -> life = SHIP_INICIAL_LIFES;
    new_ship -> pos_x = 0;
	new_ship -> pos_y = 0;
    new_ship -> exploded = 0;
    new_ship -> power_up_type = 0;
    new_ship -> power_up_eff = 0;
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