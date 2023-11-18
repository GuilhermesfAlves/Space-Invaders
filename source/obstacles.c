#include "../headers/obstacles.h"
#include <stdlib.h>

obstacles** add_obstacles(unsigned char qtd){
    obstacles** new_obstacles;

    if (!(new_obstacles = (obstacles**) malloc(qtd*sizeof(obstacles*))))
        return NULL;

    for (int i = 0; i < qtd; i++){
        if (!(new_obstacles[i] =  (obstacles*) malloc(sizeof(obstacles))))
            return NULL;
            
        new_obstacles[i] -> life = OBSTACLE_LIFES;
        new_obstacles[i] -> pos_x = 0;
        new_obstacles[i] -> pos_y = 0; 
    }
    return new_obstacles;
}

void* destroy_obstacle(obstacles* obstacle){

    if (obstacle)
       free(obstacle);
    return NULL;
}

void destroy_obstacles(obstacles** obstacles, unsigned char qtd_obstacles){

    for (int i = 0; i < qtd_obstacles; i++)
        obstacles[i] = destroy_obstacle(obstacles[i]);
    free(obstacles);
}