#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

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
                                                                 
void START_ALERT(ALLEGRO_FONT* font, int frame, int move){
    if ((!move) && ((frame < 40) || ((frame > 80) && (frame < 120)) || ((frame > 160) && (frame < 200))))
        al_draw_text(font, al_map_rgb(255, 255, 255), 960, 960 - move, ALLEGRO_ALIGN_CENTRE, "Press SPACE to Start!");
}


int main(){
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(1920, 1080);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP *logo = al_load_bitmap("SPACE_INVADERS_LOGO.bmp");
    int frame = 0;
    int move = 0;
    char start = 0;
    char exit = 0;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(1) {
        al_wait_for_event(queue, &event);
        if (frame == 240)
            frame = 0;
        
        if (start)
            move += 3;

        if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (event.keyboard.keycode == ALLEGRO_KEY_SPACE))
            start = 1;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = 1;
            break;
        }
        if (move == 700)
            break;

        if ((event.type == ALLEGRO_EVENT_TIMER) && (al_is_event_queue_empty(queue))){
            al_clear_to_color(al_map_rgb(54, 54, 54));
            al_draw_bitmap(logo, 645, 248 - 140 - move, 0);
            START_ALERT(font, frame, move);
            al_flip_display();
        }
        frame++;
    }
    al_destroy_bitmap(logo);
    if (!exit)
        while(1){
            //jogo
        }
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
