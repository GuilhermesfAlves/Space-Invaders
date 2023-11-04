#include "../headers/obstacles.h"

obstacles* add_obstacles(unsigned char qtd, int height, int width){
    obstacles* new_obstacles;

    if (!(new_obstacles = (obstacles*) malloc(qtd*sizeof(obstacles))))
        return NULL;

    for (int i = 0; i < qtd; i++){
        new_obstacles[i].life = OBSTACLE_LIFES;
        new_obstacles[i].pos_x = (width/2) + (i - qtd)*3;
        new_obstacles[i].pos_y = height*0.65; 
    }
    return new_obstacles;
}

void destroy_obstacles(obstacles* obstacles){

    free(obstacles);
}