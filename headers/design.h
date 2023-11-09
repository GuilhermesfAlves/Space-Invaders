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
void add_icon(ALLEGRO_DISPLAY* disp);

void set_aliens_sprites(game* game, sprite_base* sprite_base);
void set_game_sprites(game* game, sprite_base* sprite_base);
void set_shot_sprite(shot* shot, sprite_base* sprite_base);

sprite_base* get_sprite_base(limits* limits);
void destroy_sprite_base(sprite_base* sprite_base);

void show_game(ALLEGRO_FONT* font, game* game, int frame);

void start_objects_position(game* game);

#endif //__DESIGN__