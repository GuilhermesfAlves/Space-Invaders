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
    new_game -> space = create_board(difficult, new_game -> limits);

    return new_game;
}

void destroy_game(game* game){

    destroy_joystick(game -> joystick);
    destroy_board(game -> space);
    free(game);
}

void update_game(game* game){

    if (game -> space -> shot_list -> first){
        update_shots(game -> space -> shot_list, game -> limits.max_height);
        hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> shot_list);
        hit_ship(game -> space -> ship, game -> space -> shot_list);
    }
    if (game -> space -> ship -> shots -> first){
        update_shots(game -> space -> ship -> shots, game -> limits.min_height);
        game -> points += hit_aliens(game -> space -> map, game -> space -> lines, game -> space -> rows, game -> space -> ship -> shots);
        hit_obstacles(game -> space -> obstacles, game -> space -> qtd_obstacles, game -> space -> ship -> shots);
        hit_shots(game -> space -> ship -> shots, game -> space -> shot_list);
    }
}