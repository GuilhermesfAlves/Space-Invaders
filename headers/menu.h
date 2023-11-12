#ifndef __SI_MENU__
#define __SI_MENU__

#include "design.h"

#define __EXIT 0
#define __MENU_PART 1
#define __GAME_PART 2
#define __GAME_OVER_PART 3

char menu_part(theme* theme, difficult* difficult, allegro_structures* allegro_structures);
char game_part(int *points, difficult* difficult, set_theme* theme, allegro_structures* allegro_structures);
char game_over_part(set_theme* theme, int points, allegro_structures* allegro_structures);

#endif