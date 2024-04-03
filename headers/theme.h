#ifndef __SI_THEME__
#define __SI_THEME__

#include "allegro_headers.h"

#define MAX_THEMES 9

enum theme_set{RETRO, SYNTH_WAVE, RED_B, GREEN_B, BLUE_B, ORANG_W, RED_W, GREEN_W, BLUE_W};

typedef struct{
    ALLEGRO_COLOR primary;
    ALLEGRO_COLOR secondary;
    ALLEGRO_COLOR back_theme;
    char set;
    char *name;
}set_theme;

typedef struct{
    unsigned char current;
    set_theme **vec;
}theme;

// cria e determina quais são as opções de cores possíveis para o jogo
theme* create_themes(unsigned char current);
//destroi a memória allocada para os temas
void destroy_themes(theme* theme);
// Lê de um determinado arquivo a última preferência de tema escolhida 
unsigned char last_used_theme();
// Guarda em um arquivo a preferência de tema definida pelo usuário
void save_last_used_theme(unsigned char current);

#endif //__THEME__