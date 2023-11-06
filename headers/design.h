#ifndef __SI_DESIGN__
#define __SI_DESIGN__

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "difficult.h"
#include "game.h"

#define ENEMIES 3

typedef struct {
    ALLEGRO_BITMAP*** aliens; 
    ALLEGRO_BITMAP*** shots;
    ALLEGRO_BITMAP** obstacles;
    ALLEGRO_BITMAP* ship;
}sprite_base;


void show_START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, int frame, int move);
void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move);
void show_difficulties(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_data, theme* theme, difficult* difficult, int move);

ALLEGRO_BITMAP* add_logo(ALLEGRO_DISPLAY_MODE* disp_data);
ALLEGRO_BITMAP* add_logo_alien(ALLEGRO_DISPLAY_MODE* disp_data);

void set_alien_sprite(enemy* alien, sprite_base* sprite_base);
void set_shot_sprite(shot* shot, unsigned char type, sprite_base* sprite_base);
void set_obstacle_sprite(obstacles *obstacle, sprite_base* sprite_base);
void set_ship_sprite(ship* ship, sprite_base* sprite_base);

sprite_base* get_sprite_base(game* game, ALLEGRO_DISPLAY *disp);
void destroy_sprite_base(sprite_base* sprite_base);

void show_alien(enemy* alien, set_theme* theme, int frame);
void show_obstacles(obstacles* obstacles, set_theme* theme);
void show_ship(ship* ship, set_theme* theme);

#endif //__DESIGN__