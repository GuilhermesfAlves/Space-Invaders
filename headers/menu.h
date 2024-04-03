#ifndef __SI_MENU__
#define __SI_MENU__

#include "sound.h"
#include "design.h"
#include "tutorial.h"

enum mode {_EXIT, _MENU_PART, _TUTORIAL_PART, _GAME_PART, _GAME_OVER_PART};

//onde ocorrem todos os eventos de menu
char menu_part(theme* theme, difficult* difficult, allegro_structures* allegro_structures);
//onde ocorrem todos os eventos de tutorial
char tutorial_part(set_theme* theme, allegro_structures* allegro_structures, int tutorial);
//onde ocorrem todos os eventos do jogo
char game_part(int *points, difficult* difficult, set_theme* theme, allegro_structures* allegro_structures);
//onde ocorrem todos os eventos de game_over
char game_over_part(set_theme* theme, int points, allegro_structures* allegro_structures);

#endif