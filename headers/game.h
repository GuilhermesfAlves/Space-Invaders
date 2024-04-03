#ifndef __SI_GAME__
#define __SI_GAME__

#include "space.h"
#include "joystick.h"
#include "theme.h"

//TICK_RATE controla a velocidade do jogo, quanto menor, mais rápido, quanto menor, mais devagar
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

//criação do jogo
game* add_game(unsigned char difficult, set_theme* theme, ALLEGRO_DISPLAY_MODE *disp_mode);
//destruição do jogo
void destroy_game(game* game);
//atualização de todas as partes do jogo
void update_game(game* game, unsigned int frame);
//reinicialização do mapa ao concluir um round
char restart_round(game* game);

//inicialização da posição dos aliens do mapa dependendo dos limites da tela
void start_alien_position(space* space, limits limits);
//inicialização da posição do ship no mapa dependendo dos limites da tela
void start_ship_position(ship* ship, limits limits);
//(Wrap)inicialização de todos os objetos no jogo
void start_objects_position(game* game);

#endif //__SI_GAME__