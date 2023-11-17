#include "../headers/menu.h"

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
 

int main(){
    al_init();
    al_install_keyboard();
    al_install_audio();
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_acodec_addon();

    allegro_structures* allegro_structures = add_allegro_structures();
    theme* theme = create_themes(last_used_theme());
    difficult* difficult = add_difficult(last_used_difficult());
    char mode = _MENU_PART;
    int points = 0;
    add_icon(allegro_structures -> disp);

    al_register_event_source(allegro_structures -> queue, al_get_keyboard_event_source());
    al_register_event_source(allegro_structures -> queue, al_get_display_event_source(allegro_structures -> disp));
    al_register_event_source(allegro_structures -> queue, al_get_timer_event_source(allegro_structures -> timer));

    al_start_timer(allegro_structures -> timer);

    while (mode){
        al_play_sample_instance(allegro_structures -> song_instance);
        switch (mode){
        case _MENU_PART:
            mode = menu_part(theme, difficult, allegro_structures);
            break;
        case _TUTORIAL_PART:
            mode = tutorial_part(theme -> vec[theme -> current], allegro_structures, 1);
            break;
        case _GAME_PART:
            mode = game_part(&points, difficult, theme -> vec[theme -> current], allegro_structures); 
            break;
        case _GAME_OVER_PART:
            push_to_historic(points, &difficult -> vec[difficult -> current]);
            write_historic(&difficult -> vec[difficult -> current]);
            mode = game_over_part(theme -> vec[theme -> current], points, allegro_structures);
            break;
        default:
            break;
       }
    }    
    destroy_themes(theme);
    destroy_difficult(difficult);
    destroy_allegro_structures(allegro_structures);
    return 0;
}
