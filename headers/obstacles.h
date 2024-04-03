#ifndef __SI_OBSTACLES__
#define __SI_OBSTACLES__

#include "allegro_headers.h"

#define OBSTACLE_LIFES 10

typedef struct{
    int life;
    int pos_x;
    int pos_y;
    ALLEGRO_BITMAP** img;
}obstacles;

//inicialização de uma quantidade de obstáculos 
obstacles** add_obstacles(unsigned char qtd);
//destruição de um obstáculo
void* destroy_obstacle(obstacles* obstacle);
//destruição de uma quantidade de obstáculos seguidos
void destroy_obstacles(obstacles** obstacles, unsigned char qtd_obstacles);

#endif //__OBSTACLES__