#ifndef __SI_GAME__
#define __SI_GAME__

#include "space.h"
#include "joystick.h"
#include "theme.h"

//TICK_RATE controls the game velocity, higher is slower and lower is faster
#define BASE_TICK_RATE 120

typedef struct{
    int round;
    int points;
    int tick_rate;
    unsigned char difficult;
    limits limits;
    space* space;
    joystick* joystick;
    set_theme* theme;
    ALLEGRO_SAMPLE** move_s;
    ALLEGRO_BITMAP* back_gradient;
}game;

game* add_game(unsigned char difficult, set_theme* theme, ALLEGRO_DISPLAY_MODE *disp_mode);
void destroy_game(game* game);
void update_game(game* game, unsigned int frame);
char restart_round(game* game);

void start_alien_position(space* space, limits limits);
void start_ship_position(ship* ship, limits limits);
void start_objects_position(game* game);

#endif //__SI_GAME__