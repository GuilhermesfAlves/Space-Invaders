#include "../headers/design.h"

void START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, int frame, int move){
    if ((!move) && ((frame < 40) || ((frame > 80) && (frame < 120)) || ((frame > 160) && (frame < 200))))
        al_draw_text(font, al_map_rgb(255, 255, 255), disp_data -> width/2, disp_data -> height - 25 - move, ALLEGRO_ALIGN_CENTRE, "Press SPACE to Start!");
}

void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move){
    al_draw_text(font, al_map_rgb(255,255,255), disp_data -> width/2, disp_data -> height - 400 - move, ALLEGRO_ALIGN_CENTRE, "Press TAB to change color");
    for (unsigned char i = 0; i < MAX_THEMES; i++){
        if (theme -> actual == i){
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move , 15, theme -> vec[i].primary);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i].back_theme);
        }
        else{
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 10, theme -> vec[i].back_theme);
            al_draw_filled_circle((disp_data -> width/2) + (i - 4)*35, disp_data -> height - 370 - move, 5, theme -> vec[i].primary);
        }
    }
    al_draw_text(font, theme -> vec[theme -> actual].primary, disp_data -> width/2, disp_data -> height - 320 - move, ALLEGRO_ALIGN_CENTRE, theme -> vec[theme -> actual].name);
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
    ALLEGRO_BITMAP *ALIEN = al_load_bitmap("img/SPRITE1.bmp");
    ALLEGRO_BITMAP *ALIEN_REDIM = al_create_bitmap(disp_data -> width*0.15, disp_data -> width*0.15);
    
    al_set_target_bitmap(ALIEN_REDIM);
    al_draw_scaled_bitmap(ALIEN, 0, 0, al_get_bitmap_width(ALIEN), al_get_bitmap_height(ALIEN), 0, 0, disp_data -> width*0.15, disp_data -> width*0.15, 0);
    al_destroy_bitmap(ALIEN);

    return ALIEN_REDIM;
}