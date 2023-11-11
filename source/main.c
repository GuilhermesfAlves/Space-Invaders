#include <string.h>
#include "../headers/design.h"
#include <stdio.h>
/*           ____                                                   */ 
/*         /\  __`\                                                 */
/*         \ \,\L\_\  _____      __      ___     __                 */
/*          \/_\__ \ /\ '__`\  /'__`\   /'___\ /'__`\               */
/*            /\ \L\ \ \ \L\ \/\ \L\.\_/\ \__//\  __/               */
/*            \ `\____\ \ ,__/\ \__/.\_\ \____\ \____\              */
/*             \/_____/\ \ \/  \/__/\/_/\/____/\/____/              */
/*   ______             \ \_\            __                         */
/* /\__  _\              \/_/           /\ \                        */
/* \/_/\ \/     ___   __  __     __     \_\ \     __   _ __   ____  */
/*    \ \ \   /' _ `\/\ \/\ \  /'__`\   /'_` \  /'__`\/\`'__\/',__\ */
/*     \_\ \__/\ \/\ \ \ \_/ |/\ \L\.\_/\ \L\ \/\  __/\ \ \//\__, `\*/
/*     /\_____\ \_\ \_\ \___/ \ \__/.\_\ \___,_\ \____\\ \_\\/\____/*/
/*     \/_____/\/_/\/_/\/__/   \/__/\/_/\/__,_ /\/____/ \/_/ \/___/ */
 
void update_joystick_menu(joystick* joystick, theme* theme, difficult* difficult){
    
    if (joystick -> tab) {
        theme -> actual = (theme -> actual + 1) % MAX_THEMES; 
        joystick_tab(joystick);
    }
    if (joystick -> left){
        if (difficult -> actual > 1)
            difficult -> actual--;
        joystick_left(joystick);
    }
    if (joystick -> right){
        if (difficult -> actual < MAX_DIFFICULTIES - 1)
            difficult -> actual ++;
        joystick_right(joystick);
    }
}

void update_joystick_game(joystick* joystick, ship* ship, sprite_base* sprite_base, limits limits){

    if ((joystick -> right) && (ship -> pos_x + SHIP_MOVE + al_get_bitmap_width(*(ship) -> img)/2 < limits.max_width)){
        ship -> pos_x += SHIP_MOVE;
    }
    if ((joystick -> left) && (ship -> pos_x - SHIP_MOVE - al_get_bitmap_width(*(ship) -> img)/2 > limits.min_width)){
        ship -> pos_x -= SHIP_MOVE;
    }
    if (joystick -> space){
        shot* shot = straight_shoot(ship -> shots, 1, UP, ship -> pos_x, ship -> pos_y, SHIP_SHOT);
        if (shot)
            set_shot_sprite(shot, sprite_base);
        
        joystick_space(joystick);
    }
}

char menu_part(ALLEGRO_FONT* font, unsigned int frame, ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, theme* theme, difficult* difficult, ALLEGRO_DISPLAY_MODE* disp_mode, ALLEGRO_DISPLAY* disp){
    ALLEGRO_BITMAP *logo = add_logo(disp_mode);
    ALLEGRO_BITMAP *alien = add_logo_alien(disp_mode);
    joystick* joystick = add_joystick();
    int move = 0;
    char exit = 2;

    al_set_target_bitmap(al_get_backbuffer(disp));

    while (exit){
        al_wait_for_event(queue, &event);
        update_joystick_menu(joystick, theme, difficult);
        
        if (joystick -> space)
            move += 30;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = 0;
        
        if (move >= disp_mode -> height)
            break;

        if ((event.type == ALLEGRO_EVENT_TIMER) && (al_is_event_queue_empty(queue))){
            al_clear_to_color(theme -> vec[theme -> actual] -> back_theme);
            al_draw_bitmap(logo, (disp_mode -> width - al_get_bitmap_width(logo))/2, 108 - move, 0);
            al_draw_tinted_bitmap(alien, theme -> vec[theme -> actual] -> primary,(disp_mode -> width - al_get_bitmap_width(alien))/2, al_get_bitmap_height(logo) + 108 + 20 - move, 0);
            show_themes(font, disp_mode, theme, move);
            show_difficulties(font, disp_mode, theme -> vec[theme -> actual], difficult, move);
            show_START_ALERT(font, disp_mode, frame, move, theme -> vec[theme -> actual]);
            al_flip_display();
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (!move)){
            if (event.keyboard.keycode == ALLEGRO_KEY_TAB) joystick_tab(joystick);
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) joystick_enter(joystick);
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) joystick_space(joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_LEFT) || (event.keyboard.keycode == ALLEGRO_KEY_A)) joystick_left(joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT) || (event.keyboard.keycode == ALLEGRO_KEY_D)) joystick_right(joystick);
        }
        frame++;
    }
    save_last_used(theme -> actual);
    save_last_used_difficult(difficult -> actual);
    destroy_joystick(joystick);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(alien);
    
    return exit;
}

char game_part(int *points, ALLEGRO_FONT* font, unsigned int frame, difficult* difficult, set_theme* theme, ALLEGRO_DISPLAY_MODE* disp_mode, ALLEGRO_DISPLAY* disp, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event){
    sprite_base* sprite_base;
    game* game;
    int mov_x;
    char exit = 3;

    game = add_game(difficult -> actual, theme, disp_mode);
    
    sprite_base = get_sprite_base(&game -> limits);
    al_set_target_bitmap(al_get_backbuffer(disp));

    set_game_sprites(game, sprite_base);
    start_objects_position(game);

    mov_x = 1;
    while((game -> space -> ship -> life) && (exit)){
        al_wait_for_event(queue, &event);
        update_joystick_game(game -> joystick, game -> space -> ship, sprite_base, game -> limits);
    
        if (frame % 60 == 0)
            mov_x = move_aliens(game -> space, game -> limits, mov_x);
    
        if (!has_alien(game -> space))
            mov_x = restart_round(game, sprite_base);
        
        if (!mov_x)
            exit = 3;
    
        update_game(game);
    
        if (event.type == ALLEGRO_EVENT_TIMER){
            al_clear_to_color(theme -> back_theme);
            show_game(font, game, frame);
            al_flip_display();
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_KEY_UP)){
            if ((event.keyboard.keycode == ALLEGRO_KEY_SPACE) && !(event.type == ALLEGRO_EVENT_KEY_UP)) joystick_space(game -> joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_LEFT) || (event.keyboard.keycode == ALLEGRO_KEY_A)) joystick_left(game -> joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT) || (event.keyboard.keycode == ALLEGRO_KEY_D)) joystick_right(game -> joystick);
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = 0;
        frame++;        
    }
    *points = game -> points;
    destroy_sprite_base(sprite_base);
    destroy_game(game);
    return exit;
}

char game_over_part(ALLEGRO_FONT* font, unsigned int frame, ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, set_theme* theme, ALLEGRO_DISPLAY_MODE* disp_mode, int points){
    char exit = 1;

    while(exit){
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER){
            al_clear_to_color(theme -> back_theme);
            show_game_over(font, disp_mode, frame, points, theme);
            al_flip_display();
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
                break;
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                exit = 0;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = 0;
        frame++;
    }

    return exit;
}

int main(){
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();

    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY_MODE disp_data;
    al_get_display_mode(al_get_num_video_adapters() - 1, &disp_data);
    disp_data.height -= 70;
    ALLEGRO_DISPLAY* disp = al_create_display(disp_data.width, disp_data.height);
    ALLEGRO_FONT* font = al_create_builtin_font();
    theme* theme = create_themes(last_used_theme());
    difficult* difficult = add_difficult(last_used_difficult());
    unsigned int frame = 0;
    char mode = 1;
    int points = 0;
    add_icon(disp);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (mode){
        switch (mode){
        case 1:
            mode = menu_part(font, frame, event, queue, theme, difficult, &disp_data, disp);
            break;
        case 2:
            mode = game_part(&points, font, frame, difficult, theme -> vec[theme -> actual], &disp_data, disp, queue, event);
            break;
        case 3:
            mode = game_over_part(font, frame, event, queue, theme -> vec[theme -> actual], &disp_data, points);
            break;
        default:
            break;
       }
    }    

    destroy_themes(theme);
    destroy_difficult(difficult);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
