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
    shot* previous = NULL;
    ship* ship = game -> space -> ship;

    //enemies shots
    for (shot* shot_aux = game -> space -> shot_list -> first; shot_aux; ){
        shot_aux -> pos_y += SHOT_MOVE;

        if (shot_aux -> pos_y > game -> limits.max_height)//saiu do game
            previous = destroy_shot(shot_aux, previous, game -> space -> shot_list);

        for (int i = 0; i < game -> space -> qtd_obstacles; i++){//bateu em obstacle
            if (((game -> space -> obstacles[i] -> pos_y + al_get_bitmap_height(*(game) -> space -> obstacles[i] -> img)/2) < shot_aux -> pos_y)\
            && ((game -> space -> obstacles[i] -> pos_y - al_get_bitmap_height(*(game) -> space -> obstacles[i] -> img)/2) > shot_aux -> pos_y)\
            && ((game -> space -> obstacles[i] -> pos_x - al_get_bitmap_width(*(game) -> space -> obstacles[i] -> img)/2) > shot_aux -> pos_x)\
            && ((game -> space -> obstacles[i] -> pos_x + al_get_bitmap_width(*(game) -> space -> obstacles[i] -> img)/2) < shot_aux -> pos_x)){
                previous = destroy_shot(shot_aux, previous, game -> space -> shot_list);
                game -> space -> obstacles[i] -> life--;
                break;
            }
        }
        //bateu em ship
        if (((ship -> pos_y + al_get_bitmap_height(*(game) -> space -> ship -> img)/2) < shot_aux -> pos_y)\
        && ((ship -> pos_y - al_get_bitmap_height(*(game) -> space -> ship -> img)/2) > shot_aux -> pos_y)\
        && ((ship -> pos_x - al_get_bitmap_width(*(game) -> space -> ship -> img)/2) > shot_aux -> pos_x)\
        && ((ship -> pos_x + al_get_bitmap_width(*(game) -> space -> ship -> img)/2) < shot_aux -> pos_x)){
            previous = destroy_shot(shot_aux, previous, game -> space -> shot_list);
            ship -> life--;
        }
    }
    //ship_shots
    if (!ship -> shots)
        return;

    ship -> shots -> pos_y -= SHOT_MOVE;
 
    if (ship -> shots -> pos_y < game -> limits.min_height)
        destroy_ship_shot(ship);

    for (int i = 0; i < game -> space -> lines; i++){//bateu em enemies
        for (int j = 0; j < game -> space -> rows; j++){
            if (((game -> space -> map[i][j] -> pos_y + al_get_bitmap_height(*(game) -> space -> map[i][j] -> img1)/2) > ship -> shots -> pos_y)\
            && ((game -> space -> map[i][j] -> pos_y - al_get_bitmap_height(*(game) -> space -> map[i][j] -> img1)/2) < ship -> shots -> pos_y)\
            && ((game -> space -> map[i][j] -> pos_x - al_get_bitmap_width(*(game) -> space -> map[i][j] -> img1)/2) < ship -> shots -> pos_x)\
            && ((game -> space -> map[i][j] -> pos_x + al_get_bitmap_width(*(game) -> space -> map[i][j] -> img1)/2) > ship -> shots -> pos_x)){
                destroy_ship_shot(ship);
                game -> points += (game -> space -> map[i][j] -> type + 1)*10;
                destroy_enemy(game -> space -> map[i][j]);
                return;
            }
        }
    }
 
    previous = NULL;
    for (shot* shot_atual = game -> space -> shot_list -> first; shot_atual; shot_atual = (shot*) shot_atual -> next){//bateu em shot
        if ((ship -> shots == shot_atual) || (ship -> shots -> trajectory == shot_atual -> trajectory))
            continue;
        if (((shot_atual -> pos_y + al_get_bitmap_height(*(shot_atual) -> img1)/2) < ship -> shots -> pos_y)\
        && ((shot_atual -> pos_y - al_get_bitmap_height(*(shot_atual) -> img1)/2) > ship -> shots -> pos_y)\
        && ((shot_atual -> pos_x - al_get_bitmap_width(*(shot_atual) -> img1)/2) > ship -> shots -> pos_x)\
        && ((shot_atual -> pos_x + al_get_bitmap_width(*(shot_atual) -> img1)/2) < ship -> shots -> pos_x)){
            destroy_ship_shot(ship);
            previous = destroy_shot(shot_atual, previous, game -> space -> shot_list);
            return;
        }
    

    for (int i = 0; i < game -> space -> qtd_obstacles; i++)//bateu em obstacle
        if (((game -> space -> obstacles[i] -> pos_y + al_get_bitmap_height(*(game) -> space -> obstacles[i] -> img)/2) < ship -> shots -> pos_y)\
        && ((game -> space -> obstacles[i] -> pos_y - al_get_bitmap_height(*(game) -> space -> obstacles[i] -> img)/2) > ship -> shots -> pos_y)\
        && ((game -> space -> obstacles[i] -> pos_x - al_get_bitmap_width(*(game) -> space -> obstacles[i] -> img)/2) > ship -> shots -> pos_x + al_get_bitmap_width(*(game) -> space -> ship -> img)/2)\
        && ((game -> space -> obstacles[i] -> pos_x + al_get_bitmap_width(*(game) -> space -> obstacles[i] -> img)/2) < ship -> shots -> pos_x - al_get_bitmap_width(*(game) -> space -> ship -> img)/2)){
            destroy_ship_shot(ship);
            game -> space -> obstacles[i] -> life--;
            return;
        }
    
}