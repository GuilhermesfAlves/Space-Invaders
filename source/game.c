#include "../headers/game.h"


game* add_game(unsigned char difficult, set_theme *theme, ALLEGRO_DISPLAY_MODE *disp_mode){
    game* new_game;

    if(!(new_game = (game*) malloc(sizeof(game))))
        return NULL;

    new_game -> limits.min_x = 50;
    new_game -> limits.min_y = 60;
    new_game -> limits.max_x = disp_mode -> width - 50;
    new_game -> limits.max_y = disp_mode -> height - 60;
    new_game -> difficult = difficult;
    new_game -> joystick = add_joystick();
    new_game -> points = 0;
    new_game -> theme = theme;
    new_game -> space = create_board(difficult, new_game -> limits);

    return new_game;
}

void destroy_game(game* game){

}