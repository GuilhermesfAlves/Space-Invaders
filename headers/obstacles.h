#ifndef __OBSTACLES__
#define __OBSTACLES__
#include <stdlib.h>

typedef struct{
    int life;
    int pos_x;
    int pos_y;
}obstacles;

obstacles* create_obstacles(unsigned char level, int height, int width);
void delete_obstacles(obstacles* obstacles);

#endif //__OBSTACLES__