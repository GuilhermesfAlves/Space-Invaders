#ifndef __SI_MENU__
#define __SI_MENU__

#include "sound.h"
#include "design.h"
#include "tutorial.h"

enum mode {_EXIT, _MENU_PART, _TUTORIAL_PART, _GAME_PART, _GAME_OVER_PART};

char menu_part(theme* theme, difficult* difficult, allegro_structures* allegro_structures);
char game_part(int *points, difficult* difficult, set_theme* theme, allegro_structures* allegro_structures);
char game_over_part(set_theme* theme, int points, allegro_structures* allegro_structures);
char tutorial_part(set_theme* theme, allegro_structures* allegro_structures, int tutorial);

#endif