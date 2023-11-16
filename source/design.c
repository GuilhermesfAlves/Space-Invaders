#include "../headers/design.h"
#include <stdio.h>

allegro_structures* add_allegro_structures(){
    allegro_structures* new_allegro_structures;

    if (!(new_allegro_structures = (allegro_structures*) malloc(sizeof(allegro_structures))))
        return NULL;
    al_set_app_name("Space Invaders");
    new_allegro_structures -> timer = al_create_timer(1.0 / 60.0);
    new_allegro_structures -> queue = al_create_event_queue();
    al_get_display_mode(al_get_num_video_adapters() - 1, &new_allegro_structures -> disp_mode);
    new_allegro_structures -> disp_mode.height -= 70;
    new_allegro_structures -> disp = al_create_display(new_allegro_structures -> disp_mode.width, new_allegro_structures -> disp_mode.height);
    al_set_window_title(new_allegro_structures -> disp, "Space Invaders");
    new_allegro_structures -> font = al_create_builtin_font();
    new_allegro_structures -> sample = al_load_sample("sound/menu_song.wav");
    new_allegro_structures -> song_instance = al_create_sample_instance(new_allegro_structures -> sample);
    al_set_sample_instance_playmode(new_allegro_structures -> song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(new_allegro_structures -> song_instance, 0.1);
    al_reserve_samples(20);
    al_attach_sample_instance_to_mixer(new_allegro_structures -> song_instance, al_get_default_mixer());
    new_allegro_structures -> back_gradient = al_load_bitmap("img/Back.png");

    return new_allegro_structures;
}

void destroy_allegro_structures(allegro_structures* allegro_structures){

    al_destroy_bitmap(allegro_structures -> back_gradient);
    al_destroy_font(allegro_structures -> font);
    al_destroy_display(allegro_structures -> disp);
    al_destroy_timer(allegro_structures -> timer);
    al_destroy_event_queue(allegro_structures -> queue);
    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
}

void show_START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, unsigned int frame, int move, set_theme* theme){

    if ((!move) && ((frame / 60) % 2))
        al_draw_text(font, theme -> primary, disp_data -> width/2, disp_data -> height - 25 - move, ALLEGRO_ALIGN_CENTRE, "Press SPACE to Start!");
}

void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move){

    al_draw_text(font, theme -> vec[theme -> current] -> secondary, disp_data -> width/2, disp_data -> height - 400 - move, ALLEGRO_ALIGN_CENTRE, "Press TAB to change color");
    for (unsigned char i = 0; i < MAX_THEMES; i++){
        if (theme -> current == i){
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move , 15, theme -> vec[i] -> primary);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i] -> back_theme);
        }
        else{
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i] -> back_theme);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 5, theme -> vec[i] -> primary);
        }
    }
    al_draw_text(font, theme -> vec[theme -> current] -> primary, disp_data -> width/2, disp_data -> height - 320 - move, ALLEGRO_ALIGN_CENTRE, theme -> vec[theme -> current] -> name);
}

void show_difficulties(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_data, set_theme* theme, difficult* difficult, int move){

    al_draw_text(font, theme -> secondary, disp_data -> width/2, disp_data -> height - 300 - move, ALLEGRO_ALIGN_CENTRE, "Press ENTER to show historic");
    al_draw_text(font, theme -> primary, disp_data -> width/2, disp_data -> height - 250 - move, ALLEGRO_ALIGN_CENTRE, difficult -> vec[difficult -> current].name);
}   

ALLEGRO_BITMAP* add_logo(ALLEGRO_DISPLAY_MODE* disp_data){
    ALLEGRO_BITMAP *logo = al_load_bitmap("img/LOGO.png");
    ALLEGRO_BITMAP *logo_redimens = al_create_bitmap(disp_data -> width*0.359895833, disp_data -> width*0.150984956);
    
    al_set_target_bitmap(logo_redimens);
    al_draw_scaled_bitmap(logo, 0, 0, al_get_bitmap_width(logo), al_get_bitmap_height(logo), 0, 0, disp_data -> width*0.359895833, disp_data -> width*0.150984956, 0);
    al_destroy_bitmap(logo);

    return logo_redimens;
}

ALLEGRO_BITMAP* add_logo_alien(ALLEGRO_DISPLAY_MODE* disp_data){
    ALLEGRO_BITMAP *ALIEN = al_load_bitmap("img/ALIEN1_0.png");
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

void set_power_up_sprite(power_up* power_up, sprite_base* sprite_base){
    if (power_up -> img)
        return;
    power_up -> img = sprite_base -> power_up[power_up -> type - 1];
}

void set_alien_sprite(enemy* enemy, sprite_base* sprite_base){

    if (!enemy)
        return;
        
    enemy -> alive_img = sprite_base -> aliens[enemy -> type];
    enemy -> dead_img = sprite_base -> explosion;
    enemy -> shot_img = sprite_base -> shots[enemy -> type + 1];
}

void set_aliens_sprites(space* space, sprite_base* sprite_base){
    
    for (int i = 0; i < space -> lines; i++)
        for (int j = 0; j < space -> rows; j++)
            set_alien_sprite(space -> map[i][j], sprite_base);
        
}

void set_shot_sprite(shot* shot, sprite_base* sprite_base){

    shot -> img = sprite_base -> shots[shot -> type];
}

void set_obstacles_sprites(obstacles **obstacle, unsigned char qtd_obstacles, sprite_base* sprite_base){

    for (int i = 0; i < qtd_obstacles; i++) 
        obstacle[i] -> img = sprite_base -> obstacles;
}

void set_ship_sprite(ship* ship, sprite_base* sprite_base){

    ship -> alive_img = sprite_base -> ship;
    ship -> dead_img = sprite_base -> explosion;
    ship -> shot_img = sprite_base -> shots[SHIP];
}

void set_game_sprites(game* game, sprite_base* sprite_base){
    
    set_aliens_sprites(game -> space, sprite_base);
    set_obstacles_sprites(game -> space -> obstacles, game -> space -> qtd_obstacles, sprite_base); 
    set_ship_sprite(game -> space -> ship, sprite_base);
}

sprite_base* get_sprite_base(limits* limits){
    sprite_base* new_sprite_base;
    ALLEGRO_BITMAP* unscaled;
    char* name[6] = {"ALIEN", "SHOT", "OBSTACLE", "SHIP", "EXPLOSION", "POWER_UP"};
    char path[25];

    if (!(new_sprite_base = (sprite_base*) malloc(sizeof(sprite_base))))
        return NULL;
    if (!(new_sprite_base -> aliens = (ALLEGRO_BITMAP***) malloc(ENEMIES_SPRITES*sizeof(ALLEGRO_BITMAP**))))
        return NULL;
    for (int i = 0; i < ENEMIES_SPRITES; i++){
        if (!(new_sprite_base -> aliens[i] = (ALLEGRO_BITMAP**) malloc(ALT_SPRITES*sizeof(ALLEGRO_BITMAP*))))
            return NULL;

        for (int j = 0; j < ALT_SPRITES; j++){
            sprintf(path, "img/%s%d_%d.png", name[0], i, j);
            unscaled = al_load_bitmap(path);
            new_sprite_base -> aliens[i][j] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/285,(limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/285);
            al_set_target_bitmap(new_sprite_base -> aliens[i][j]);
            al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/285, (limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/285, 0);
            al_destroy_bitmap(unscaled);
        } 
    }  

    if (!(new_sprite_base -> shots = (ALLEGRO_BITMAP***) malloc(SHOT_SPRITES*sizeof(ALLEGRO_BITMAP**))))
        return NULL;

    for (int i = 0; i < SHOT_SPRITES; i++){
        if (!(new_sprite_base -> shots[i] = (ALLEGRO_BITMAP**) malloc(ALT_SPRITES*sizeof(ALLEGRO_BITMAP*))))
            return NULL;

        for (int j = 0; j < ALT_SPRITES; j++){
            sprintf(path, "img/%s%d_%d.png", name[1], i, j);
            unscaled = al_load_bitmap(path);
            new_sprite_base -> shots[i][j] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/230,(limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/230);
            al_set_target_bitmap(new_sprite_base -> shots[i][j]);
            al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/230, (limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/230, 0);
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

    if (!(new_sprite_base -> explosion = (ALLEGRO_BITMAP**) malloc(ALT_SPRITES*sizeof(ALLEGRO_BITMAP*))))
        return NULL;

    for (int i = 0; i < ALT_SPRITES; i++){
        sprintf(path, "img/%s%d.png", name[4], i);
        unscaled = al_load_bitmap(path);
        new_sprite_base -> explosion[i] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/320, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/320);
        al_set_target_bitmap(new_sprite_base -> explosion[i]);
        al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/320, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/320, 0);
        al_destroy_bitmap(unscaled);
    }

    if (!(new_sprite_base -> power_up = (ALLEGRO_BITMAP**) malloc(QTD_POWER_UP_TYPES*sizeof(ALLEGRO_BITMAP*))))
        return NULL;

    for (int i = 0; i < QTD_POWER_UP_TYPES; i++){
        sprintf(path, "img/%s%d.png", name[5], i);
        unscaled = al_load_bitmap(path);
        new_sprite_base -> power_up[i] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/650, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/650);
        al_set_target_bitmap(new_sprite_base -> power_up[i]);
        al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/650, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/650, 0);
        al_destroy_bitmap(unscaled);
    }

    if (!(new_sprite_base -> ship = (ALLEGRO_BITMAP**) malloc(2*sizeof(ALLEGRO_BITMAP*))))
        return NULL;

    for (int i = 0; i < 2; i++){
        sprintf(path, "img/%s%d.png", name[3], i); 
        unscaled = al_load_bitmap(path);
        new_sprite_base -> ship[i] = al_create_bitmap((limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300,(limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/300);
        al_set_target_bitmap(new_sprite_base -> ship[i]);
        al_draw_scaled_bitmap(unscaled, 0, 0, al_get_bitmap_width(unscaled), al_get_bitmap_height(unscaled), 0, 0, (limits -> max_width - limits -> min_width)*al_get_bitmap_width(unscaled)/300, (limits -> max_width - limits -> min_width)*al_get_bitmap_height(unscaled)/300, 0);
        al_destroy_bitmap(unscaled);
    }

    return new_sprite_base;
}

void destroy_sprite_base(sprite_base* sprite_base){

    for(int i = 0; i < ENEMIES_SPRITES; i++){
        for (int j = 0; j < ALT_SPRITES; j++)
            al_destroy_bitmap(sprite_base -> aliens[i][j]);
        free(sprite_base -> aliens[i]);
    }
    free(sprite_base -> aliens);
    
    for (int i = 0; i < SHOT_SPRITES; i++){
        for (int j = 0; j < ALT_SPRITES; j++)
            al_destroy_bitmap(sprite_base -> shots[i][j]);
        free(sprite_base -> shots[i]);
    }
    free(sprite_base -> shots);
    
    for (int i = 0; i < OBSTACLE_LIFES; i++)
        al_destroy_bitmap(sprite_base -> obstacles[i]);
    free(sprite_base -> obstacles);
    
    for (int i = 0; i < ALT_SPRITES; i++)
        al_destroy_bitmap(sprite_base -> explosion[i]);
    free(sprite_base -> explosion);
    for (int i = 0; i < 2; i++){
        al_destroy_bitmap(sprite_base -> ship[i]);
    }
    free(sprite_base);
}

void show_aliens(ALLEGRO_FONT* font, game* game , unsigned int frame){
    
    for (int i = 0; i < game -> space -> lines; i++){
        for (int j = 0; j < game -> space -> rows; j++){
            if (!game -> space -> map[i][j])
                continue;

            if (game -> space -> map[i][j] -> exploded){
                al_draw_tinted_bitmap((game -> space -> map[i][j]) -> dead_img[(frame / 7) % ALT_SPRITES], game -> theme -> primary, game -> space -> map[i][j] -> pos_x - al_get_bitmap_width(*(game -> space -> map[i][j]) -> dead_img)/2, game -> space -> map[i][j] -> pos_y - al_get_bitmap_height(*(game -> space -> map[i][j]) -> dead_img)/2, 0);
                al_draw_textf(font, game -> theme -> secondary, game -> space -> map[i][j] -> pos_x, game -> space -> map[i][j] -> pos_y, ALLEGRO_ALIGN_CENTRE, "+%d", game -> space -> map[i][j] -> points);
            } else 
                al_draw_tinted_bitmap((game -> space -> map[i][j] -> alive_img)[(frame / game -> tick_rate) % ALT_SPRITES], game -> theme -> primary, game -> space -> map[i][j] -> pos_x - al_get_bitmap_width(*(game -> space -> map[i][j]) -> alive_img)/2, game -> space -> map[i][j] -> pos_y - al_get_bitmap_height(*(game -> space -> map[i][j]) -> alive_img)/2, 0);
        }
    }
}

void show_alien(ALLEGRO_FONT* font, enemy* alien, set_theme* theme, unsigned int frame){

    if (!alien)
        return;

    if (alien -> exploded){
        al_draw_tinted_bitmap(alien -> dead_img[(frame / 7) % ALT_SPRITES], theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> dead_img)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> dead_img)/2, 0);
        al_draw_textf(font, theme -> secondary, alien -> pos_x, alien -> pos_y, ALLEGRO_ALIGN_CENTRE, "+%d", alien -> points);
    } else 
        al_draw_tinted_bitmap(alien -> alive_img[(frame / 60) % ALT_SPRITES], theme -> primary, alien -> pos_x - al_get_bitmap_width(*(alien) -> alive_img)/2, alien -> pos_y - al_get_bitmap_height(*(alien) -> alive_img)/2, 0);
}

void show_shots(shot_sentinel* shot_list, set_theme* theme, unsigned int frame){
    for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = (shot*) shot_aux -> next)
        al_draw_tinted_bitmap((shot_aux) -> img[(frame / 10) % ALT_SPRITES], theme -> secondary, shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2, shot_aux -> pos_y - al_get_bitmap_height(*(shot_aux) -> img)/2, 0);
}

void show_obstacles(space* space, set_theme* theme){
    
    for (int i = 0; i < space -> qtd_obstacles; i++){
        if (space -> obstacles[i])
            al_draw_tinted_bitmap(space -> obstacles[i] -> img[space -> obstacles[i] -> life - 1], theme -> primary, space -> obstacles[i] -> pos_x - (al_get_bitmap_width(space -> obstacles[i] -> img[space -> obstacles[i] -> life - 1])/2), space -> obstacles[i] -> pos_y, 0);
    }
}

void show_ship(ship* ship, set_theme* theme, unsigned int frame){

    if (ship -> exploded)
        al_draw_tinted_bitmap(ship -> dead_img[(frame / 7) % ALT_SPRITES], theme -> primary, ship -> pos_x - (al_get_bitmap_width(*(ship) -> dead_img))/2, ship -> pos_y - al_get_bitmap_height(*(ship) -> dead_img)/2, 0);
    else 
        al_draw_tinted_bitmap(ship -> alive_img[ship -> power_up_type], theme -> primary, ship -> pos_x - (al_get_bitmap_width(ship -> alive_img[ship -> power_up_type]))/2, ship -> pos_y - al_get_bitmap_height(ship -> alive_img[ship -> power_up_type])/2, 0);
}

void show_lifes(ALLEGRO_FONT* font, ship* ship, set_theme* theme, limits limits){

    al_draw_text(font, theme -> primary, limits.max_width - 450, limits.min_height + 20, ALLEGRO_ALIGN_RIGHT, "LIFES: ");
    for (int i = ship ->life - 1; i > -1; i--)
       al_draw_tinted_scaled_bitmap(*ship -> alive_img, theme -> secondary, 0,0 ,al_get_bitmap_width(*ship -> alive_img),al_get_bitmap_height(*ship -> alive_img), limits.max_width - 150 - (75*i),limits.min_height - 13, al_get_bitmap_width(*ship -> alive_img)*0.75, al_get_bitmap_height(*ship -> alive_img)*0.75,0);
}

void show_points(ALLEGRO_FONT* font, game* game){

    al_draw_textf(font, game -> theme -> primary, game -> limits.min_width + 30, game -> limits.min_height + 20, ALLEGRO_ALIGN_LEFT, "POINTS: %d", game -> points);
}

void show_power_ups(power_up_list* power_up_list, set_theme* theme){

    for (power_up* aux_power_up = power_up_list -> first; aux_power_up; aux_power_up = aux_power_up -> next)
        al_draw_tinted_bitmap(aux_power_up -> img, theme -> secondary, aux_power_up -> pos_x, aux_power_up -> pos_y, 0);
}

void show_game(ALLEGRO_FONT* font, game* game, unsigned int frame){

    al_draw_rounded_rectangle(game -> limits.min_width + 100, game -> limits.max_height*1.025, game -> limits.max_width - 100, game -> limits.max_height*1.03, 3,3, game -> theme -> secondary, 9);
    show_aliens(font, game, frame);
    show_shots(game -> space -> shot_list, game -> theme, frame);
    show_shots(game -> space -> ship -> shot_list, game -> theme, frame); 
    show_obstacles(game -> space, game -> theme);
    show_ship(game -> space -> ship, game -> theme, frame);    
    show_points(font, game);
    show_lifes(font, game -> space -> ship, game -> theme, game -> limits);
    show_alien(font, game -> space -> super_alien, game -> theme, frame);
    show_shots(game -> space -> super_shot, game -> theme, frame);
    show_power_ups(game -> space -> power_up_list, game -> theme);
}

char restart_round(game* game, sprite_base* sprite_base){
    char vec[6];
    char blank_row[2];
    char qtd_power_ups;

    clean_shots(game -> space -> shot_list);
    clean_shots(game -> space -> ship -> shot_list);
    set_formation(&game -> space -> rows, &game -> space -> lines, &game -> difficult, &game -> space -> qtd_obstacles, &qtd_power_ups, vec, blank_row);
    add_aliens(game -> space, vec, blank_row);
    start_alien_position(game -> space, game -> limits);
    set_random_power_ups(game -> space -> map, game -> space -> lines, game -> space -> rows, qtd_power_ups);
    set_aliens_sprites(game -> space, sprite_base);
    if (game -> space -> ship -> life < SHIP_MAX_LIFES)
        game -> space -> ship -> life++;
    return 1;
}

void show_game_over(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_mode, unsigned int frame, int points, set_theme* theme){
    int centre_x = disp_mode -> width/2;
    int centre_y = disp_mode -> height/2;

    al_draw_filled_rounded_rectangle(centre_x - 400, centre_y - 400, centre_x + 400, centre_y + 400, 40, 40, theme -> secondary);
    al_draw_filled_rounded_rectangle(centre_x - 380, centre_y - 380, centre_x + 380, centre_y + 380, 20, 20, theme -> back_theme);
    al_draw_text(font, theme -> primary, centre_x, centre_y - 300, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_draw_textf(font, theme -> primary, centre_x, centre_y, ALLEGRO_ALIGN_CENTRE, "POINTS: %d", points);
    al_draw_text(font, theme -> secondary, centre_x, centre_y + 280, ALLEGRO_ALIGN_CENTRE, "Press ESC to Exit");
    if ((frame / 40) % 2)
        al_draw_text(font, theme -> primary, centre_x, centre_y + 300, ALLEGRO_ALIGN_CENTRE, "Press SPACE to go to Menu");
}

void set_shot_sprites(shot_sentinel* shot_list, sprite_base* sprite_base){
    for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = (shot*) shot_aux -> next)
        set_shot_sprite(shot_aux, sprite_base);
}

void show_historic(ALLEGRO_FONT* font, difficult* difficult, set_theme* theme, int max_x, int max_y, int move){
    int min_x = max_x*0.05;
    int min_y = max_y*0.05;
    max_x *= 0.3;
    int mid_x = (min_x + max_x)/2;
    int mid_y = max_y*0.5;
    int space_between = (-min_y - 50 + max_y - 30)*0.1;

    if (!difficult -> show)
        return;
    al_draw_textf(font, theme -> primary, mid_x, min_y + 10 + (space_between >> 2) - move, ALLEGRO_ALIGN_CENTRE, "HISTORIC - %s", difficult -> vec[difficult -> current].name);
    al_draw_rounded_rectangle(min_x, min_y - move, max_x, (max_y*0.95) - move, 40, 40, theme -> primary, 10);
    for (int i = 0; i < QTD_P_HISTORIC; i++){
        al_draw_textf(font, theme -> secondary, mid_x, (min_y*2.5) - move + i*space_between, ALLEGRO_ALIGN_CENTRE, "%d PTS    ||    %s - %s", difficult -> vec[difficult -> current].historic[i].points, difficult -> vec[difficult -> current].historic[i].data, difficult -> vec[difficult -> current].historic[i].time);
    }
}