#include "../headers/game.h"
#include <stdlib.h>
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
    new_game -> tick_rate = BASE_TICK_RATE - difficult*20;

    return new_game;
}

void destroy_game(game* game){

    destroy_joystick(game -> joystick);
    destroy_space(game -> space);
    free(game);
}

void update_game(game* game, unsigned int frame){
    
    if ((frame / 600 % 2) && (game -> tick_rate > BASE_TICK_RATE - game -> difficult*20 - 10))
        game -> tick_rate -= 2;
    get_exploded(game -> space);
    if (game -> space -> ship -> exploded)
        game -> space -> ship -> exploded++;
    if (game -> space -> ship -> exploded == 20){
        game -> space -> ship -> pos_x = (game -> limits.max_width + game -> limits.min_width)/2;
        game -> space -> ship -> exploded = 0;
    }
    game -> space -> super_alien = get_explod(game -> space -> super_alien);
    if (game -> space -> shot_list -> first){
        update_shots(game -> space -> shot_list, game -> limits.max_height, game -> limits.max_width, game -> limits.min_width);
        hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> shot_list);
        if (!game -> space -> ship -> exploded)
            hit_ship(game -> space -> ship, game -> space -> shot_list);
    }
    update_shots(game -> space -> ship -> shot_list, game -> limits.min_height,  game -> limits.max_width, game -> limits.min_width);
    game -> points += hit_aliens(game -> space -> map, game -> space -> lines, game -> space -> rows, game -> space -> ship -> shot_list);
    hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> ship -> shot_list);
    hit_shots(game -> space -> ship -> shot_list, game -> space -> shot_list);
    game -> points += hit_alien(game -> space -> super_alien, game -> space -> ship -> shot_list);
    if (frame % (game -> tick_rate*2) == 0)
        enemy_shots(game -> space -> ship -> pos_x, game -> space -> ship -> pos_y, game -> space -> lines, game -> space -> rows, game -> space -> map, game -> space -> shot_list);
    if (game -> space -> ship -> power_up_eff <= 0)
        game -> space -> ship -> power_up_type = NONE;
    else if (game -> space -> ship -> power_up_eff > 0)
        game -> space -> ship -> power_up_eff--;

    if (game -> space -> power_up_list -> first)
        ship_got_power_up(game -> space);
}

char restart_round(game* game){
    char vec[6];
    char blank_row[2];
    char qtd_power_ups;

    clean_shots(game -> space -> shot_list);
    clean_shots(game -> space -> ship -> shot_list);
    if (!(set_formation(&game -> space -> rows, &game -> space -> lines, &game -> difficult, &game -> space -> qtd_obstacles, &qtd_power_ups, vec, blank_row))){
        fprintf(stderr, "Can't set map formation\n");
        return 0;
    }
    add_aliens(game -> space, vec, blank_row);
    start_alien_position(game -> space, game -> limits);
    set_random_power_ups(game -> space -> map, game -> space -> lines, game -> space -> rows, qtd_power_ups);
    if (game -> space -> ship -> life < SHIP_MAX_LIFES)
        game -> space -> ship -> life++;
    game -> tick_rate -= 5; //acelera o tickrate em 5 por rodada, aumentando a dificuldade
    return 1; 
}

void start_alien_position(space* space, limits limits){
    int between_x = (limits.max_width*0.65 - limits.min_width)/(space -> rows);
    int between_y = (limits.max_height*0.5 - limits.min_height)/(space -> lines);
	
    for (int i = 0; i < space -> lines; i++) 
		for (int j = 0; j < space -> rows; j++){
            if (!space -> map[i][j])
                continue;

			space -> map[i][j] -> pos_x = limits.min_width + between_x/2 + j*between_x;
            space -> map[i][j] -> pos_y =  limits.min_height + 30 + between_y/2 + i*between_y;
		}
}

void start_obstacles_position(space* space, limits limits){
    int between_x = (limits.max_width - limits.min_width)/space -> qtd_obstacles;

    for (int i = 0; i < space -> qtd_obstacles; i++){
        if (!space -> obstacles[i])
            continue;

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

