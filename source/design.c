#include "../headers/design.h"
#include <stdio.h>
void show_START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, int frame, int move){

    if ((!move) && ((frame < 40) || ((frame > 80) && (frame < 120)) || ((frame > 160) && (frame < 200))))
        al_draw_text(font, al_map_rgb(255, 255, 255), disp_data -> width/2, disp_data -> height - 25 - move, ALLEGRO_ALIGN_CENTRE, "Press SPACE to Start!");
}

void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move){

    al_draw_text(font, al_map_rgb(255,255,255), disp_data -> width/2, disp_data -> height - 400 - move, ALLEGRO_ALIGN_CENTRE, "Press TAB to change color");
    for (unsigned char i = 0; i < MAX_THEMES; i++){
        if (theme -> actual == i){
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move , 15, theme -> vec[i] -> primary);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i] -> back_theme);
        }
        else{
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i] -> back_theme);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 5, theme -> vec[i] -> primary);
        }
    }
    al_draw_text(font, theme -> vec[theme -> actual] -> primary, disp_data -> width/2, disp_data -> height - 320 - move, ALLEGRO_ALIGN_CENTRE, theme -> vec[theme -> actual] -> name);
}

void show_difficulties(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_data, theme* theme, difficult* difficult, int move){

    al_draw_text(font, theme -> vec[theme -> actual] -> primary, disp_data -> width/2, disp_data -> height - 300 - move, ALLEGRO_ALIGN_CENTRE, "Press ENTER to show historic");
    al_draw_text(font, theme -> vec[theme -> actual] -> primary, disp_data -> width/2, disp_data -> height - 250 - move, ALLEGRO_ALIGN_CENTRE, difficult -> vec[difficult -> actual] -> name);
}   

ALLEGRO_BITMAP* add_logo(ALLEGRO_DISPLAY_MODE* disp_data){
    ALLEGRO_BITMAP *logo = al_load_bitmap("img/Space_Invaders_Logo.bmp");
    ALLEGRO_BITMAP *logo_redimens = al_create_bitmap(disp_data -> width*0.359895833, disp_data -> width*0.150984956);
    
    al_set_target_bitmap(logo_redimens);
    al_draw_scaled_bitmap(logo, 0, 0, al_get_bitmap_width(logo), al_get_bitmap_height(logo), 0, 0, disp_data -> width*0.359895833, disp_data -> width*0.150984956, 0);
    al_destroy_bitmap(logo);

    return logo_redimens;
}

ALLEGRO_BITMAP* add_logo_alien(ALLEGRO_DISPLAY_MODE* disp_data){
    ALLEGRO_BITMAP *ALIEN = al_load_bitmap("img/ALIEN1_0.bmp");
    ALLEGRO_BITMAP *ALIEN_REDIM = al_create_bitmap(disp_data -> width*0.12, disp_data -> width*0.087272727);
    
    al_set_target_bitmap(ALIEN_REDIM);
    al_draw_scaled_bitmap(ALIEN, 0, 0, al_get_bitmap_width(ALIEN), al_get_bitmap_height(ALIEN), 0, 0, disp_data -> width*0.12, disp_data -> width*0.087272727, 0);
    al_destroy_bitmap(ALIEN);

    return ALIEN_REDIM;
}

void set_alien_sprite(enemy* alien, sprite_base* sprite_base){
    
    alien -> img1 = &sprite_base -> aliens[alien -> type][0];
    alien -> img2 = &sprite_base -> aliens[alien -> type][1];
}

void set_shot_sprite(shot* shot, sprite_base* sprite_base){

    shot -> img1 = &sprite_base -> shots[shot -> type][0];
    shot -> img2 = &sprite_base -> shots[shot -> type][1];
}

void set_obstacle_sprite(obstacles *obstacle, sprite_base* sprite_base){

    obstacle -> img = &sprite_base -> obstacles[obstacle -> life - 1];
}

void set_ship_sprite(ship* ship, sprite_base* sprite_base){

    ship -> img = &sprite_base -> ship;
}

void set_game_sprites(game* game, sprite_base* sprite_base){
    
    for (int i = 0; i < game -> space -> rows; i++)
        for (int j = 0; j < game -> space -> lines; j++)
            set_alien_sprite(game -> space -> map[j][i], sprite_base);

    for (int i = 0; i < game -> space -> qtd_obstacles; i++)
        set_obstacle_sprite(game -> space -> obstacles[i], sprite_base);
    
    set_ship_sprite(game -> space -> ship, sprite_base);

}

sprite_base* get_sprite_base(limits* limits){
    sprite_base* new_sprite_base;
    ALLEGRO_BITMAP* unscaled;
    char* name[4] = {"ALIEN", "SHOT", "OBSTACLE", "SHIP"};
    char path[25];

    if (!(new_sprite_base = (sprite_base*) malloc(sizeof(sprite_base))))
        return NULL;
    if (!(new_sprite_base -> aliens = (ALLEGRO_BITMAP***) malloc(ENEMIES*sizeof(ALLEGRO_BITMAP**))))
        return NULL;
    for (int i = 0; i < ENEMIES; i++){
        if (!(new_sprite_base -> aliens[i] = (ALLEGRO_BITMAP**) malloc(2*sizeof(ALLEGRO_BITMAP*))))
            return NULL;

        for (int j = 0; j < 2; j++){
            sprintf(path, "img/%s%d_%d.bmp", name[0], i, j);
            unscaled = al_load_bitmap(path);
            new_sprite_base -> aliens[i][j] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/25000,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/25000);
            al_set_target_bitmap(new_sprite_base -> aliens[i][j]);
            al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/25000, (limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/25000, 0);
            al_destroy_bitmap(unscaled);
        } 
    } 

    if (!(new_sprite_base -> shots = (ALLEGRO_BITMAP***) malloc(3*sizeof(ALLEGRO_BITMAP**))))
        return NULL;

    for (int i = 0; i < 3; i++){
        if (!(new_sprite_base -> shots[i] = (ALLEGRO_BITMAP**) malloc(2*sizeof(ALLEGRO_BITMAP*))))
            return NULL;

        for (int j = 0; j < 2; j++){
            sprintf(path, "img/%s%d_%d.bmp", name[1], i, j);
            unscaled = al_load_bitmap(path);
            new_sprite_base -> shots[i][j] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/15000,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/15000);
            al_set_target_bitmap(new_sprite_base -> shots[i][j]);
            al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/15000, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/15000, 0);
            al_destroy_bitmap(unscaled);
        }
    }

    if (!(new_sprite_base -> obstacles = (ALLEGRO_BITMAP**) malloc(OBSTACLE_LIFES*sizeof(ALLEGRO_BITMAP*))))
        return NULL;

    for (int i = 0; i < OBSTACLE_LIFES; i++){
        sprintf(path, "img/%s%d.bmp", name[2], i);
        unscaled = al_load_bitmap(path);
        new_sprite_base -> obstacles[i] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/13000,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/13000);
        al_set_target_bitmap(new_sprite_base -> obstacles[i]);
        al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/13000, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/13000, 0);
        al_destroy_bitmap(unscaled);
    }

    sprintf(path, "img/%s.bmp", name[3]);
    unscaled = al_load_bitmap(path);
    new_sprite_base -> ship = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/29000,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/29000);
    al_set_target_bitmap(new_sprite_base -> ship);
    al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/29000, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/29000, 0);
    al_destroy_bitmap(unscaled);

    return new_sprite_base;
}

void destroy_sprite_base(sprite_base* sprite_base){

    for(int i = 0; i < ENEMIES; i++){
        for (int j = 0; j < 2; j++)
            al_destroy_bitmap(sprite_base -> aliens[i][j]);
        free(sprite_base -> aliens[i]);
    }
    free(sprite_base -> aliens);
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++)
            al_destroy_bitmap(sprite_base -> shots[i][j]);
        free(sprite_base -> shots[i]);
    }
    free(sprite_base -> shots);
    
    for (int i = 0; i < OBSTACLE_LIFES; i++)
        al_destroy_bitmap(sprite_base -> obstacles[i]);
    free(sprite_base -> obstacles);
    
    al_destroy_bitmap(sprite_base -> ship);
    
    free(sprite_base);
}

void show_alien(enemy* alien, set_theme* theme, int frame){
    if (alien -> exploded){
        if ((frame < 5) || (frame > 10))
            al_draw_tinted_bitmap(*(alien) -> img1, theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> img1)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> img1)/2, 0);
        else 
            al_draw_tinted_bitmap(*(alien) -> img2, theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> img1)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> img1)/2, 0);
        return;
    }
    if (frame < 60)
        al_draw_tinted_bitmap(*(alien) -> img1, theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> img1)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> img1)/2, 0);
    else 
        al_draw_tinted_bitmap(*(alien) -> img2, theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> img1)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> img1)/2, 0);
}

void show_shots(shot* shot, set_theme* theme, int frame){
    if ((frame < 5) || (frame > 10))
        al_draw_tinted_bitmap(*(shot) -> img1, theme -> secondary, shot -> pos_x - al_get_bitmap_width(*(shot) -> img1)/2, shot -> pos_y - al_get_bitmap_height(*(shot) -> img1)/2, 0);
    else 
        al_draw_tinted_bitmap(*(shot) -> img2, theme -> secondary, shot -> pos_x - al_get_bitmap_width(*(shot) -> img2)/2, shot -> pos_y - al_get_bitmap_height(*(shot) -> img2)/2, 0);
}

void show_obstacle(obstacles* obstacle, set_theme* theme){

    al_draw_tinted_bitmap(*(obstacle) -> img, theme -> primary, obstacle -> pos_x - (al_get_bitmap_width(*(obstacle) -> img)/2), obstacle -> pos_y, 0);
}

void show_ship(ship* ship, set_theme* theme){

    al_draw_tinted_bitmap(*(ship) -> img, theme -> primary, ship -> pos_x - (al_get_bitmap_width(*(ship) -> img))/2, ship -> pos_y - al_get_bitmap_height(*(ship) -> img)/2, 0);
}

void show_points(int points, set_theme* theme, ALLEGRO_FONT* font, limits limits){
    char line[20];

    sprintf(line, "POINTS: %d", points);
    al_draw_text(font, theme -> primary, limits.min_width + 30, limits.min_height + 20, ALLEGRO_ALIGN_LEFT, line);
}

void show_game(ALLEGRO_FONT* font, game* game, int frame){

    for (int i = 0; i < game -> space -> rows; i++)
        for (int j = 0; j < game -> space -> lines; j++)
            show_alien(game -> space -> map[j][i], game -> theme, frame);
        
    for (shot* shot_aux = game -> space -> shot_list -> first; shot_aux; shot_aux -> next)
        show_shots(shot_aux, game -> theme, frame);

    if (game -> space -> ship -> shots)
        show_shots(game -> space -> ship -> shots, game -> theme, frame);
    
    for (int i = 0; i < game -> space -> qtd_obstacles; i++){
        show_obstacle(game -> space -> obstacles[i], game -> theme);
    }
    
    show_ship(game -> space -> ship, game -> theme);    

    show_points(game -> points, game -> theme, font, game -> limits);
}

void start_objects_position(game* game){
    int between_x;
    int between_y;

	for (int i = 0; i < game -> space -> lines; i++) 
		for (int j = 0; j < game -> space -> rows; j++){
			between_x = (game -> limits.max_width*0.57 - game -> limits.min_width)/(game -> space -> rows);
			between_y = (game -> limits.max_height*0.5 - game -> limits.min_height)/(game -> space -> lines);
			game -> space -> map[i][j] -> pos_x = game -> limits.min_width + between_x/2 + j*between_x;
            game -> space -> map[i][j] -> pos_y =  game -> limits.min_height + 30 + between_y/2 + i*between_y;
		}

    for (int i = 0; i < game -> space -> qtd_obstacles; i++){
        between_x = (game -> limits.max_width - game -> limits.min_width)/game -> space -> qtd_obstacles;
        game -> space -> obstacles[i] -> pos_x = between_x*i + between_x/2 + 50;
        game -> space -> obstacles[i] -> pos_y = (game -> limits.max_height - game -> limits.min_height)*0.75;
    }
	
    game -> space -> ship -> pos_x = (game -> limits.max_width + game -> limits.min_width)/2;
    game -> space -> ship -> pos_y = game -> limits.max_height*0.97;
}
