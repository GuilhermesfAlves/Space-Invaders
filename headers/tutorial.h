#ifndef __SI_TUTORIAL__
#define __SI_TUTORIAL__

#include <stdlib.h>

// Carrega de um determinado arquivo a opção passada do usuário de ver o tutorial 
unsigned char show_tutorial();
// Salva em um determinado arquivo a opção do usuário sobre ver o tutorial
void save_preference(unsigned char current);

#endif