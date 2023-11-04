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

 
void update_joystick(joystick* joystick, theme* theme){
    if (joystick -> tab) {
        theme -> actual = (theme -> actual >= MAX_THEMES - 1)? 0 : theme -> actual + 1; 
        joystick_tab(joystick);
    }
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
    printf("start\n");
    disp_data.height -= 73;
    ALLEGRO_DISPLAY* disp = al_create_display(disp_data.width, disp_data.height);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP *logo = add_logo(&disp_data);
    ALLEGRO_BITMAP *alien = add_logo_alien(&disp_data);
    theme* theme = create_themes();
    joystick* joystick = add_joystick();
    int frame = 0;
    int move = 0;
    char start = 0;
    char exit = 0;

    al_set_target_bitmap(al_get_backbuffer(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(1) {
        al_wait_for_event(queue, &event);
        update_joystick(joystick, theme);
        if (frame == 240)
            frame = 0;
        
        if (joystick -> space)
            move += 3;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = 1;
            break;
        }
        if (move == 760)
            break;

        if ((event.type == ALLEGRO_EVENT_TIMER) && (al_is_event_queue_empty(queue))){
            al_clear_to_color(theme -> vec[theme -> actual].back_theme);
            al_draw_tinted_bitmap(alien, theme -> vec[theme -> actual].primary,(disp_data.width - al_get_bitmap_width(alien))/2, al_get_bitmap_height(logo) + 70 - move, 0);
            al_draw_bitmap(logo, (disp_data.width - al_get_bitmap_width(logo))/2, 108 - move, 0);
            show_themes(font, &disp_data, theme ,move);
            START_ALERT(font, &disp_data, frame, move);
            al_flip_display();
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN)){
            if (event.keyboard.keycode == ALLEGRO_KEY_TAB) joystick_tab(joystick);
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) joystick_enter(joystick);
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) joystick_space(joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_LEFT) || (event.keyboard.keycode == ALLEGRO_KEY_A)) joystick_left(joystick);
            else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT) || (event.keyboard.keycode == ALLEGRO_KEY_D)) joystick_right(joystick);
        }
        frame++;
    }
    al_destroy_bitmap(logo);
    joystick_space(joystick);
    if (!exit)
        while(1){
            //jogo
        }
    destroy_joystick(joystick);
    destroy_themes(theme);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
