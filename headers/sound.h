#ifndef __SI_SOUND__
#define __SI_SOUND__

#include "game.h"

#define MOVE_SOUNDS 4

//define os sons de disparo e explosão de ship
int set_ship_sounds(ship* ship);
//define os sons de explosão de um alien
int set_enemy_sounds(enemy* enemy);
//define os sons de explosão de todos os aliens de um mapa
int set_enemies_sounds(enemy*** enemies, int lines, int rows);
//(Wrap) define todas os sons em um jogo
int set_game_sounds(game* game);

#endif //__SI_SOUND__