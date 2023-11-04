#ifndef __SI_OBSTACLES__
#define __SI_OBSTACLES__
#include <stdlib.h>

typedef struct{
    int life;
    int pos_x;
    int pos_y;
}obstacles;

obstacles* add_obstacles(unsigned char level, int height, int width);
void destroy_obstacles(obstacles* obstacles);

#endif //__OBSTACLES__