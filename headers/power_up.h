#ifndef __SI_POWER_UP__
#define __SI_POWER_UP__

#include "allegro_headers.h"

#define FALL_MOVE 3
#define QTD_POWER_UP_TYPES 1
#define POWER_UP_LIFETIME 200
enum power_up_enums{NONE, SHIELD};

typedef struct power_up{
    int pos_x;
    int pos_y;
    ALLEGRO_BITMAP* img;
    int type;
    struct power_up* next;
    struct power_up* previous;
}power_up;

typedef struct{
    power_up* first;
    power_up* last;
}power_up_list;

power_up_list* create_power_up_list();
void destroy_power_up_list(power_up_list* power_up_list);

power_up* add_power_up(char type, int pos_x, int pos_y, power_up_list* power_up_list);
power_up* destroy_power_up(power_up* power_up, power_up_list* power_up_list);

#endif //__SI_POWER_UP__