#include "../headers/game.h"
#include <stdio.h>

game* add_game(unsigned char difficult, set_theme *theme, ALLEGRO_DISPLAY_MODE *disp_mode){
    game* new_game;

    if(!(new_game = (game*) malloc(sizeof(game))))
        return NULL;

    new_game -> limits.min_width = disp_mode -> width*0.026041667;
    new_game -> limits.min_height = disp_mode -> height*0.055555556;
    new_game -> limits.max_width = disp_mode -> width*0.973958333;
    new_game -> limits.max_height = disp_mode -> height*0.944444444;
    new_game -> difficult = difficult;
    new_game -> joystick = add_joystick();
    new_game -> points = 0;
    new_game -> theme = theme;
    new_game -> space = create_space(difficult, new_game -> limits);

    return new_game;
}

void destroy_game(game* game){

    destroy_joystick(game -> joystick);
    destroy_space(game -> space);
    free(game);
}

void update_game(game* game, unsigned int frame){
    
    get_exploded(game -> space -> map, game -> space -> lines, game -> space -> rows);
    if (game -> space -> ship -> exploded)
        game -> space -> ship -> exploded++;
    game -> space -> super_alien = get_explod(game -> space -> super_alien);
    if (game -> space -> shot_list -> first){
        update_shots(game -> space -> shot_list, game -> limits.max_height, game -> limits.max_width, game -> limits.min_width);
        hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> shot_list);
        hit_ship(game -> space -> ship, game -> space -> shot_list);
    }
    update_shots(game -> space -> ship -> shots, game -> limits.min_height,  game -> limits.max_width, game -> limits.min_width);
    game -> points += hit_aliens(game -> space -> map, game -> space -> lines, game -> space -> rows, game -> space -> ship -> shots);
    hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> ship -> shots);
    hit_shots(game -> space -> ship -> shots, game -> space -> shot_list);
    game -> points += hit_alien(game -> space -> super_alien, game -> space -> ship -> shots);
    if (frame % 120 == 0)
        two_enemy_shots(game -> space -> ship -> pos_x, game -> space -> ship -> pos_y, game -> space -> lines, game -> space -> rows, game -> space -> map, game -> space -> shot_list);
    if (game -> space -> super_shot -> first){
        update_shots(game -> space -> super_shot, game -> limits.max_height, game -> limits.max_width, game -> limits.min_width);
        hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> super_shot);
        hit_shots(game -> space -> super_shot, game -> space -> ship -> shots);
        hit_ship(game -> space -> ship, game -> space -> super_shot);
    }
}

void start_alien_position(space* space, limits limits){
    int between_x = (limits.max_width*0.65 - limits.min_width)/(space -> rows);
    int between_y = (limits.max_height*0.5 - limits.min_height)/(space -> lines);
	
    for (int i = 0; i < space -> lines; i++) 
		for (int j = 0; j < space -> rows; j++){
			space -> map[i][j] -> pos_x = limits.min_width + between_x/2 + j*between_x;
            space -> map[i][j] -> pos_y =  limits.min_height + 30 + between_y/2 + i*between_y;
		}
}

void start_obstacles_position(space* space, limits limits){
    int between_x = (limits.max_width - limits.min_width)/space -> qtd_obstacles;

    for (int i = 0; i < space -> qtd_obstacles; i++){
        space -> obstacles[i] -> pos_x = between_x*i + between_x/2 + 50;
        space -> obstacles[i] -> pos_y = (limits.max_height - limits.min_height)*0.75;
    }
}

void start_ship_position(ship* ship, limits limits){

    ship -> pos_x = (limits.max_width + limits.min_width)/2;
    ship -> pos_y = limits.max_height*0.97;
}

void start_objects_position(game* game){

    start_alien_position(game -> space, game -> limits);
    start_obstacles_position(game -> space, game -> limits);
    start_ship_position(game -> space -> ship, game -> limits);
}
