#ifndef __SI_DESIGN__
#define __SI_DESIGN__

#include "game.h"

#define ENEMIES_SPRITES 4
#define SHOT_SPRITES 5
#define ALT_SPRITES 2

//the structure that contains the allegro basic structures to run
typedef struct{
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_DISPLAY_MODE disp_mode;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_FONT* font;
    ALLEGRO_TIMER* timer;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE* song_instance;
    ALLEGRO_BITMAP* back_gradient;
}allegro_structures;

//the structure that constains the images of the game
typedef struct {
    ALLEGRO_BITMAP*** aliens;
    ALLEGRO_BITMAP*** shots;
    ALLEGRO_BITMAP** obstacles;
    ALLEGRO_BITMAP** explosion;
    ALLEGRO_BITMAP** ship;
    ALLEGRO_BITMAP** power_up;
}sprite_base;

allegro_structures* add_allegro_structures();
void destroy_allegro_structures(allegro_structures* allegro_structures);

void show_START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, unsigned int frame, int move, set_theme* theme);
void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move);
void show_difficulties(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_data, set_theme* theme, difficult* difficult, int move);
void show_historic(ALLEGRO_FONT* font, difficult* difficult, set_theme* theme, int max_x, int max_y, int move);
void show_tutorial_op(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_data, set_theme* theme, int move, int tutorial);

ALLEGRO_BITMAP* add_logo(ALLEGRO_DISPLAY_MODE* disp_data);
ALLEGRO_BITMAP* add_logo_alien(ALLEGRO_DISPLAY_MODE* disp_data);
ALLEGRO_BITMAP* add_monster(ALLEGRO_DISPLAY_MODE* disp_data);
ALLEGRO_BITMAP* add_tutorial(ALLEGRO_DISPLAY_MODE* disp_data);
void add_icon(ALLEGRO_DISPLAY* disp);

void set_alien_sprite(enemy* enemy, sprite_base* sprite_base);
void set_aliens_sprites(space* space, sprite_base* sprite_base);
void set_game_sprites(game* game, sprite_base* sprite_base);
void set_shot_sprite(shot* shot, sprite_base* sprite_base);
void set_shot_sprites(shot_sentinel* shot_list, sprite_base* sprite_base);
void set_power_up_sprite(power_up* power_up, sprite_base* sprite_base);

//to return the structure with all the bitmaps for the game
sprite_base* get_sprite_base(limits* limits);
void destroy_sprite_base(sprite_base* sprite_base);

void show_game(ALLEGRO_FONT* font, game* game, unsigned int frame);
char restart_round(game* game);
void show_game_over(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE* disp_mode, unsigned int frame, int points, set_theme* theme);

#endif //__DESIGN__