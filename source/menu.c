#include "../headers/menu.h"

int time_to_start(unsigned int frame){
    return (frame > 40)? 1:0;
}

void update_joystick_menu(joystick* joystick, theme* theme, difficult* difficult){
    
    if (joystick -> tab) {
        theme -> current = (theme -> current + 1) % MAX_THEMES; 
        joystick_tab(joystick);
    }
    if (joystick -> left){
        if (difficult -> current > 0)
            difficult -> current--;
        joystick_left(joystick);
    }
    if (joystick -> right){
        if (difficult -> current < MAX_DIFFICULTIES - 1)
            difficult -> current ++;
        joystick_right(joystick);
    }
    if (joystick -> enter){
        difficult -> show ^= 1;
        joystick_enter(joystick);
    }
}

void update_joystick_game(joystick* joystick, ship* ship, sprite_base* sprite_base, limits limits){

    if ((joystick -> right) && (ship -> pos_x + SHIP_MOVE + al_get_bitmap_width(*(ship) -> alive_img)/2 < limits.max_width)){
        ship -> pos_x += SHIP_MOVE;
    }
    if ((joystick -> left) && (ship -> pos_x - SHIP_MOVE - al_get_bitmap_width(*(ship) -> alive_img)/2 > limits.min_width)){
        ship -> pos_x -= SHIP_MOVE; 
    }
    if (joystick -> space){
        shot* shot = straight_shoot(ship -> shot_list, 1, STAY, UP, ship -> pos_x, ship -> pos_y, SHIP);
        if (shot){
            set_shot_sprite(shot, sprite_base);
            al_play_sample(ship -> shoot_s, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        joystick_space(joystick);
    }
}

char menu_part(theme* theme, difficult* difficult, allegro_structures* allegro_structures){
    ALLEGRO_BITMAP *logo = add_logo(&allegro_structures -> disp_mode);
    ALLEGRO_BITMAP *alien = add_logo_alien(&allegro_structures -> disp_mode);
    joystick* joystick = add_joystick();
    unsigned int frame = 0;
    int move = 0;
    char exit = _GAME_PART;

    al_set_target_bitmap(al_get_backbuffer(allegro_structures -> disp));

    while (exit){
        al_wait_for_event(allegro_structures -> queue, &allegro_structures -> event);
        update_joystick_menu(joystick, theme, difficult);
        
        if (joystick -> space)
            move += 30;
        
        if (move >= allegro_structures -> disp_mode.height)
            break;

        if ((allegro_structures -> event.type == ALLEGRO_EVENT_TIMER) && (al_is_event_queue_empty(allegro_structures -> queue))){
            al_clear_to_color(theme -> vec[theme -> current] -> back_theme);
            al_draw_bitmap(logo, (allegro_structures -> disp_mode.width - al_get_bitmap_width(logo))/2, 108 - move, 0);
            al_draw_tinted_bitmap(alien, theme -> vec[theme -> current] -> primary,(allegro_structures -> disp_mode.width - al_get_bitmap_width(alien))/2, al_get_bitmap_height(logo) + 108 + 20 - move, 0);
            show_themes(allegro_structures -> font, &allegro_structures -> disp_mode, theme, move);
            show_difficulties(allegro_structures -> font, &allegro_structures -> disp_mode, theme -> vec[theme -> current], difficult, move);
            show_START_ALERT(allegro_structures -> font, &allegro_structures -> disp_mode, frame, move, theme -> vec[theme -> current]);
            show_historic(allegro_structures -> font, difficult, theme -> vec[theme -> current], allegro_structures -> disp_mode.width, allegro_structures -> disp_mode.height, move);
            al_flip_display();
        }
        else if ((allegro_structures -> event.type == ALLEGRO_EVENT_KEY_DOWN) && (!move)){
            if (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_TAB) joystick_tab(joystick);
            else if (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_ENTER) joystick_enter(joystick);
            else if (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_SPACE) joystick_space(joystick);
            else if ((allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_LEFT) || (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_A)) joystick_left(joystick);
            else if ((allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_RIGHT) || (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_D)) joystick_right(joystick);
        }
        else if (allegro_structures -> event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = _EXIT;

        frame++;
    }
    save_last_used(theme -> current);
    save_last_used_difficult(difficult -> current);
    destroy_joystick(joystick);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(alien);
    
    return exit;
}

char game_part(int *points, difficult* difficult, set_theme* theme, allegro_structures* allegro_structures){
    sprite_base* sprite_base;
    unsigned int frame = 0;
    game* game;
    int mov_x;
    char exit = _GAME_OVER_PART;
    int shot_pos;

    game = add_game(difficult -> current, theme, &allegro_structures -> disp_mode);
    
    srand(time(NULL));
    sprite_base = get_sprite_base(&game -> limits);
    al_set_target_bitmap(al_get_backbuffer(allegro_structures -> disp));

    set_game_sprites(game, sprite_base);
    set_game_sounds(game);
    start_objects_position(game);

    mov_x = RIGHT;
    while((game -> space -> ship -> exploded != 20) && (mov_x) && (exit)){
        al_wait_for_event(allegro_structures -> queue, &allegro_structures -> event);
        update_joystick_game(game -> joystick, game -> space -> ship, sprite_base, game -> limits);
    
        if (frame % 60 == 0){
            mov_x = move_aliens(game -> space, game -> limits, mov_x);
            al_play_sample(game -> move_s[(frame /60) % MOVE_SOUNDS], 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        if (!has_alien(game -> space)){
            mov_x = restart_round(game, sprite_base);
            set_game_sounds(game);
        }
        
        if (time_to_start(frame))
            update_game(game, frame);
        if ((frame % 1000 == 500) && (!game -> space -> super_alien)){
            game -> space -> super_alien = add_enemy(SUPER, mov_x);
            short mid = (game -> limits.max_width - game -> limits.min_width)/2;
            game -> space -> super_alien -> pos_x = mid + game -> limits.min_width - mov_x*mid;
            game -> space -> super_alien -> pos_y = game -> limits.min_height + 10;
            set_alien_sprite(game -> space -> super_alien, sprite_base);
            set_enemy_sounds(game -> space -> super_alien);
            shot_pos = (rand() % (game -> limits.max_width - game -> limits.min_width)) + game -> limits.min_width;
        }
        if (game -> space -> super_alien){
            if ((!game -> space -> super_shot -> first) && (shot_pos*game -> space -> super_alien -> dir < game -> space -> super_alien -> pos_x*game -> space -> super_alien -> dir)){
                shot* shot = straight_shoot(game -> space -> super_shot, 1, mov_x, DOWN, game -> space -> super_alien -> pos_x, game -> space -> super_alien -> pos_y, SUPER);
                set_shot_sprite(shot, sprite_base);
                shot_pos = 5000*shot -> trajectory_x;
            }
            game -> space -> super_alien -> pos_x += game -> space -> super_alien -> dir*SUPER_ALIEN_STEP;
            if (game -> space -> super_alien -> pos_x > game -> limits.max_width)
                game -> space -> super_alien = destroy_enemy(game -> space -> super_alien);
        }

        if ((allegro_structures -> event.type == ALLEGRO_EVENT_KEY_DOWN) || (allegro_structures -> event.type == ALLEGRO_EVENT_KEY_UP)){
            if ((allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_SPACE) && !(allegro_structures -> event.type == ALLEGRO_EVENT_KEY_UP) && time_to_start(frame)) joystick_space(game -> joystick);
            else if ((allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_LEFT) || (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_A)) joystick_left(game -> joystick);
            else if ((allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_RIGHT) || (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_D)) joystick_right(game -> joystick);
        }
        else if (allegro_structures -> event.type == ALLEGRO_EVENT_TIMER){
            al_clear_to_color(theme -> back_theme);
            show_game(allegro_structures -> font, game, frame);
            al_flip_display();
        }
        else if (allegro_structures -> event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = _EXIT;
        frame++;
    }
    *points = game -> points;
    destroy_sprite_base(sprite_base);
    destroy_game(game);
    return exit;
}

char game_over_part(set_theme* theme, int points, allegro_structures* allegro_structures){
    unsigned int frame = 0;
    char exit = _MENU_PART;

    while(exit){
        al_wait_for_event(allegro_structures -> queue, &allegro_structures -> event);

        if (allegro_structures -> event.type == ALLEGRO_EVENT_TIMER){
            al_clear_to_color(theme -> back_theme);
            show_game_over(allegro_structures -> font, &allegro_structures -> disp_mode, frame, points, theme);
            al_flip_display();
        }
        else if ((frame > 40) && (allegro_structures -> event.type == ALLEGRO_EVENT_KEY_DOWN)){
            if (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_SPACE)
                break;
            if (allegro_structures -> event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                exit = _EXIT;
        }
        else if (allegro_structures -> event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = _EXIT;
        frame++;
    }

    return exit;
}
