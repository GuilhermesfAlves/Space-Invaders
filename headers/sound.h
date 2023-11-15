#ifndef __SI_SOUND__
#define __SI_SOUND__
#include <stdio.h>
#include "game.h"

#define MOVE_SOUNDS 4

int set_ship_sounds(ship* ship);
int set_enemy_sounds(enemy* enemy);
int set_enemies_sounds(enemy*** enemies, int lines, int rows);
int set_game_sounds(game* game);

#endif //__SI_SOUND__