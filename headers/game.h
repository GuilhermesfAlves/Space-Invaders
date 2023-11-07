#ifndef __SI_GAME__
#define __SI_GAME__

#include "space.h"
#include "joystick.h"
#include "theme.h"

#define SHOT_MOVE 3

typedef struct{
    int points;
    unsigned char difficult;
    limits limits;
    space* space;
    joystick* joystick;
    set_theme* theme;
}game;

game* add_game(unsigned char difficult, set_theme* theme, ALLEGRO_DISPLAY_MODE *disp_mode);
void destroy_game(game* game);
void update_game(game* game);

#endif //__SI_GAME__