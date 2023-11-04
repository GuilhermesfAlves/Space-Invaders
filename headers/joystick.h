#ifndef __SI_JOYSTICK__
#define __SI_JOYSTICK__
#include <stdlib.h>

typedef struct{
    unsigned char tab;
    unsigned char enter;
    unsigned char right;
    unsigned char left;
    unsigned char space;
}joystick;

joystick* add_joystick();
void destroy_joystick(joystick* joystick);

void joystick_space(joystick* joystick);
void joystick_enter(joystick* joystick);
void joystick_tab(joystick* joystick);
void joystick_left(joystick* joystick);
void joystick_right(joystick* joystick);

#endif //__JOYSTICK__