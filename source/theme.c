#include "../headers/theme.h"

theme* create_themes(){
    theme* new_theme;

    if (!(new_theme = (theme*)malloc(sizeof(theme))))
        return NULL;

    if (!(new_theme -> vec = (set_theme*)malloc(9*sizeof(set_theme))))
        return NULL;

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

void destroy_themes(theme* theme){
    
    for(int i = 0; i < MAX_THEMES; i++)
        free(theme -> vec[i].name);
    
    free(theme -> vec);
    free(theme);
}