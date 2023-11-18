#include "../headers/joystick.h"
#include <stdlib.h>


joystick* add_joystick(){
    joystick* new_joystick;

    if(!(new_joystick = (joystick*) malloc(sizeof(joystick))))
        return NULL;
    
    new_joystick -> tab = 0;
    new_joystick -> enter = 0;
    new_joystick -> space = 0;
    new_joystick -> left = 0;
    new_joystick -> right = 0;

    return new_joystick;
}

void destroy_joystick(joystick* joystick){

    free(joystick);
}

void joystick_space(joystick* joystick){ joystick -> space ^= 1;}
void joystick_enter(joystick* joystick){ joystick -> enter ^= 1;}
void joystick_tab(joystick* joystick){ joystick -> tab ^= 1;}
void joystick_left(joystick* joystick){ joystick -> left ^= 1;}
void joystick_right(joystick* joystick){ joystick -> right ^= 1;}
