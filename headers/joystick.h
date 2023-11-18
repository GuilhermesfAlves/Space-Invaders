#ifndef __SI_JOYSTICK__
#define __SI_JOYSTICK__

//possible controls in the game
typedef struct{
    unsigned char tab;
    unsigned char enter;
    unsigned char right;
    unsigned char left;
    unsigned char space;
}joystick;

joystick* add_joystick();
void destroy_joystick(joystick* joystick);

//used by commands that receive the keyboard input
//to flip a char

void joystick_space(joystick* joystick);
void joystick_enter(joystick* joystick);
void joystick_tab(joystick* joystick);
void joystick_left(joystick* joystick);
void joystick_right(joystick* joystick);

#endif //__JOYSTICK__