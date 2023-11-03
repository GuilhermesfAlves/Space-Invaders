#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
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

typedef struct{
    ALLEGRO_COLOR primary;
    ALLEGRO_COLOR secondary;
    ALLEGRO_COLOR back_theme;
    enum {RETRO, SYNTH_WAVE, RED_B, GREEN_B, BLUE_B, ORANG_W, RED_W, GREEN_W, BLUE_W} set;
    char *name;
}set_theme;

typedef struct{
    unsigned char actual;
    unsigned char max;
    set_theme *vec;
}theme;

typedef struct{
    unsigned char TAB;
    unsigned char ENTER;
    unsigned char RIGHT;
    unsigned char LEFT;
}joystick;

void START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE disp_data, int frame, int move){
    if ((!move) && ((frame < 40) || ((frame > 80) && (frame < 120)) || ((frame > 160) && (frame < 200))))
        al_draw_text(font, al_map_rgb(255, 255, 255), disp_data.width/2, disp_data.height -100- move, ALLEGRO_ALIGN_CENTRE, "Press SPACE to Start!");
}
 
void update_joystick(joystick* joystick, theme* theme){
    if (joystick -> TAB) theme -> actual = (theme -> actual >= theme -> max - 1)? 0 : theme -> actual + 1; joystick -> TAB = 0;
} 

joystick* inicia_joystick(){
    joystick* new_joystick;

    if(!(new_joystick = (joystick*)malloc(sizeof(joystick))))
        return NULL;
    
    new_joystick -> TAB = 0;
    new_joystick -> ENTER = 0;
    new_joystick -> LEFT = 0;
    new_joystick -> RIGHT = 0;

    return new_joystick;
}

void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE disp_data, theme* theme, int move){
    al_draw_text(font, al_map_rgb(255,255,255), disp_data.width/2, disp_data.height - 450 - move, ALLEGRO_ALIGN_CENTRE, "Press TAB to change color");
    for (unsigned char i = 0; i < theme -> max; i++){
        if (theme -> actual == i){
            al_draw_filled_circle((disp_data.width/2) + (i - 4)*35, disp_data.height - 420 - move , 15, theme -> vec[i].primary);
            al_draw_filled_circle((disp_data.width/2) + (i - 4)*35, disp_data.height - 420 - move, 10, theme -> vec[i].back_theme);
        }
        else{
            al_draw_filled_circle((disp_data.width/2) + (i - 4)*35, disp_data.height - 420 - move, 10, theme -> vec[i].back_theme);
            al_draw_filled_circle((disp_data.width/2) + (i - 4)*35, disp_data.height - 420 - move, 5, theme -> vec[i].primary);
        }
    }
    al_draw_text(font, theme -> vec[theme -> actual].primary, disp_data.width/2, disp_data.height - 370 - move, ALLEGRO_ALIGN_CENTRE, theme -> vec[theme -> actual].name);
}

theme* create_themes(){
    theme* new_theme;

    if (!(new_theme = (theme*)malloc(sizeof(theme))))
        return NULL;

    if (!(new_theme -> vec = (set_theme*)malloc(9*sizeof(set_theme))))
        return NULL;

    new_theme -> max = 9;
    new_theme -> actual = 0;
    new_theme -> vec[0].set = RETRO;
    new_theme -> vec[0].name = strdup("RETRO");
    new_theme -> vec[0].primary = al_map_rgb(0,255,0);
    new_theme -> vec[0].secondary = al_map_rgb(0,146,0);
    new_theme -> vec[0].back_theme = al_map_rgb(0,0,0);
    new_theme -> vec[1].set = SYNTH_WAVE;
    new_theme -> vec[1].name = strdup("SYNTH_WAVE");
    new_theme -> vec[1].primary = al_map_rgb(255,44,132);
    new_theme -> vec[1].secondary = al_map_rgb(135,21,69);
    new_theme -> vec[1].back_theme = al_map_rgb(38,0,55);
    new_theme -> vec[2].set = RED_B;
    new_theme -> vec[2].name = strdup("BLUE & BLACK");
    new_theme -> vec[2].primary = al_map_rgb(0,255,255);
    new_theme -> vec[2].secondary = al_map_rgb(0,146,146);
    new_theme -> vec[2].back_theme = al_map_rgb(23,23,23);
    new_theme -> vec[3].set = GREEN_B;
    new_theme -> vec[3].name = strdup("RED & BLACK");
    new_theme -> vec[3].primary = al_map_rgb(255,82,82);
    new_theme -> vec[3].secondary = al_map_rgb(150,47,47);
    new_theme -> vec[3].back_theme = al_map_rgb(23,23,23);
    new_theme -> vec[4].set = BLUE_B;
    new_theme -> vec[4].name = strdup("GREEN & BLACK");
    new_theme -> vec[4].primary = al_map_rgb(187,225,107);
    new_theme -> vec[4].secondary = al_map_rgb(102,137,57);
    new_theme -> vec[4].back_theme = al_map_rgb(23,23,23);
    new_theme -> vec[5].set = ORANG_W;
    new_theme -> vec[5].name = strdup("ORANGE & GRAY");
    new_theme -> vec[5].primary = al_map_rgb(255,142,37);
    new_theme -> vec[5].secondary = al_map_rgb(135,75,20);
    new_theme -> vec[5].back_theme = al_map_rgb(53,51,51);
    new_theme -> vec[6].set = RED_W;
    new_theme -> vec[6].name = strdup("BLUE & WHITE");
    new_theme -> vec[6].primary = al_map_rgb(0,146,146);
    new_theme -> vec[6].secondary = al_map_rgb(0,255,255);
    new_theme -> vec[6].back_theme = al_map_rgb(239,239,239);
    new_theme -> vec[7].set = GREEN_W;
    new_theme -> vec[7].name = strdup("RED & WHITE");
    new_theme -> vec[7].primary = al_map_rgb(150,47,47);
    new_theme -> vec[7].secondary = al_map_rgb(255,82,82);
    new_theme -> vec[7].back_theme = al_map_rgb(239,239,239);
    new_theme -> vec[8].set = BLUE_W;
    new_theme -> vec[8].name = strdup("GREEN & WHITE");
    new_theme -> vec[8].primary = al_map_rgb(102,137,57);
    new_theme -> vec[8].secondary = al_map_rgb(187,225,107);
    new_theme -> vec[8].back_theme = al_map_rgb(239,239,239);
    return new_theme;
}
  
int main(){
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();

    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY_MODE disp_data;
    al_get_display_mode(al_get_num_video_adapters() - 1, &disp_data);
    ALLEGRO_DISPLAY* disp = al_create_display(disp_data.width, disp_data.height);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP *logo = al_load_bitmap("img/Space_Invaders_Logo.bmp");
    ALLEGRO_BITMAP *logo_redimens = al_create_bitmap(disp_data.width*0.359895833, disp_data.width*0.150984956);
    al_set_target_bitmap(logo_redimens);
    al_draw_scaled_bitmap(logo, 0, 0, al_get_bitmap_width(logo), al_get_bitmap_height(logo), 0, 0, disp_data.width*0.359895833, disp_data.width*0.150984956, 0);
    ALLEGRO_BITMAP *ALIEN = al_load_bitmap("img/SPRITE1.bmp");
    ALLEGRO_BITMAP *ALIEN_REDIM = al_create_bitmap(disp_data.width*0.15, disp_data.width*0.15);
    al_set_target_bitmap(ALIEN_REDIM);
    al_draw_scaled_bitmap(ALIEN, 0, 0, al_get_bitmap_width(ALIEN), al_get_bitmap_height(ALIEN), 0, 0, disp_data.width*0.15, disp_data.width*0.15, 0);
    al_set_target_bitmap(al_get_backbuffer(disp));
    theme* theme = create_themes();
    joystick* joystick = inicia_joystick();
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
        update_joystick(joystick, theme);
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
        if (move == 760)
            break;

        if ((event.type == ALLEGRO_EVENT_TIMER) && (al_is_event_queue_empty(queue))){
            al_clear_to_color(theme -> vec[theme -> actual].back_theme);
            al_draw_tinted_bitmap(ALIEN_REDIM,theme -> vec[theme -> actual].primary,(disp_data.width - al_get_bitmap_width(ALIEN_REDIM))/2, al_get_bitmap_height(logo_redimens) + 70 - move, 0);
            al_draw_bitmap(logo_redimens, (disp_data.width - al_get_bitmap_width(logo_redimens))/2, 108 - move, 0);
            show_themes(font, disp_data, theme ,move);
            START_ALERT(font, disp_data, frame, move);
            al_flip_display();
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN)){
            if (event.keyboard.keycode == ALLEGRO_KEY_TAB) joystick -> TAB = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) joystick -> ENTER = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) joystick -> LEFT = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) joystick -> RIGHT =1;
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
