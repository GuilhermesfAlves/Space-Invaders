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

void add_icon(ALLEGRO_DISPLAY* disp){
    ALLEGRO_BITMAP *icon = al_load_bitmap("img/ICON.png");
    al_set_display_icon(disp, icon);
    al_destroy_bitmap(icon);
}

void set_aliens_sprites(game* game, sprite_base* sprite_base){
    
    for (int i = 0; i < game -> space -> lines; i++)
        for (int j = 0; j < game -> space -> rows; j++){
            game -> space -> map[i][j] -> img1 = &sprite_base -> aliens[game -> space -> map[i][j] -> type][0];
            game -> space -> map[i][j] -> img2 = &sprite_base -> aliens[game -> space -> map[i][j] -> type][1];
    }
}

void set_shot_sprite(shot* shot, sprite_base* sprite_base){

    shot -> img1 = &sprite_base -> shots[shot -> type][0];
    shot -> img2 = &sprite_base -> shots[shot -> type][1];
}

void set_obstacles_sprites(obstacles **obstacle, unsigned char qtd_obstacles, sprite_base* sprite_base){

    for (int i = 0; i < qtd_obstacles; i++) 
        for (int j = 0; j < OBSTACLE_LIFES; j++)
            obstacle[i] -> img[j] = &sprite_base -> obstacles[j];
}

void set_ship_sprite(ship* ship, sprite_base* sprite_base){

    ship -> img = &sprite_base -> ship;
}

void set_game_sprites(game* game, sprite_base* sprite_base){
    
    set_aliens_sprites(game, sprite_base);
    set_obstacles_sprites(game -> space -> obstacles, game -> space -> qtd_obstacles, sprite_base); 
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
        sprintf(path, "img/%s%d.png", name[2], i);
        unscaled = al_load_bitmap(path);
        new_sprite_base -> obstacles[i] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300);
        al_set_target_bitmap(new_sprite_base -> obstacles[i]);
        al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300, 0);
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

void show_aliens(space* space, set_theme* theme, int frame){
    
    for (int i = 0; i < space -> lines; i++){
        for (int j = 0; j < space -> rows; j++){
            if (!space -> map[i][j])
                continue;

            if (space -> map[i][j] -> exploded){
                if ((frame < 5) || (frame > 10))
                    al_draw_tinted_bitmap(*(space -> map[i][j]) -> img1, theme -> primary, space -> map[i][j] -> pos_x - al_get_bitmap_width(*(space -> map[i][j]) -> img1)/2, space -> map[i][j] -> pos_y - al_get_bitmap_height(*(space -> map[i][j]) -> img1)/2, 0);
                else 
                    al_draw_tinted_bitmap(*(space -> map[i][j]) -> img2, theme -> primary, space -> map[i][j] -> pos_x - al_get_bitmap_width(*(space -> map[i][j]) -> img1)/2, space -> map[i][j] -> pos_y - al_get_bitmap_height(*(space -> map[i][j]) -> img1)/2, 0);
                return;
            }
            if (frame < 60)
                al_draw_tinted_bitmap(*(space -> map[i][j]) -> img1, theme -> primary, space -> map[i][j] -> pos_x - al_get_bitmap_width(*(space -> map[i][j]) -> img1)/2, space -> map[i][j] -> pos_y - al_get_bitmap_height(*(space -> map[i][j]) -> img1)/2, 0);
            else 
                al_draw_tinted_bitmap(*(space -> map[i][j]) -> img2, theme -> primary, space -> map[i][j] -> pos_x - al_get_bitmap_width(*(space -> map[i][j]) -> img1)/2, space -> map[i][j] -> pos_y - al_get_bitmap_height(*(space -> map[i][j]) -> img1)/2, 0);
        }
    }
}

void show_shots(shot_sentinel* shot_list, set_theme* theme, int frame){
   for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = (shot*) shot_aux -> next){
        if ((frame < 5) || (frame > 10))
            al_draw_tinted_bitmap(*(shot_aux) -> img1, theme -> secondary, shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img1)/2, shot_aux -> pos_y - al_get_bitmap_height(*(shot_aux) -> img1)/2, 0);
        else 
            al_draw_tinted_bitmap(*(shot_aux) -> img2, theme -> secondary, shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img2)/2, shot_aux -> pos_y - al_get_bitmap_height(*(shot_aux) -> img2)/2, 0);
    }
}

void show_obstacles(space* space, set_theme* theme){
    
    for (int i = 0; i < space -> qtd_obstacles; i++){
        if (space -> obstacles[i])
            al_draw_tinted_bitmap(*(space -> obstacles[i]) -> img[space -> obstacles[i] -> life - 1], theme -> primary, space -> obstacles[i] -> pos_x - (al_get_bitmap_width(*(space -> obstacles[i]) -> img[space -> obstacles[i] -> life - 1])/2), space -> obstacles[i] -> pos_y, 0);
    }
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

    show_aliens(game -> space, game -> theme, frame);
    show_shots(game -> space -> shot_list, game -> theme, frame);
    show_shots(game -> space -> ship -> shots, game -> theme, frame); 
    show_obstacles(game -> space, game -> theme);
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
