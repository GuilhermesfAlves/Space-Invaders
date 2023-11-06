#include "../headers/obstacles.h"
#include <stdio.h>

obstacles** add_obstacles(unsigned char qtd, int height, int width){
    obstacles** new_obstacles;
    int space_between;

    if (!(new_obstacles = (obstacles**) malloc(qtd*sizeof(obstacles*))))
        return NULL;

    for (int i = 0; i < qtd; i++){
        if (!(new_obstacles[i] =  (obstacles*) malloc(sizeof(obstacles))))
            return NULL;
        space_between = width/qtd;
        new_obstacles[i] -> life = OBSTACLE_LIFES;
        new_obstacles[i] -> pos_x = space_between*i + space_between/2 + 50;
        new_obstacles[i] -> pos_y = height*0.6; 
        new_obstacles[i] -> img = NULL;
        printf("criou obstacle %d %d\n", new_obstacles[i] -> pos_x, new_obstacles[i] -> pos_y);
    }
    return new_obstacles;
}

void destroy_obstacles(obstacles** obstacles, unsigned char qtd_obstacles){

    for (int i = 0; i < qtd_obstacles; i++)
        free(obstacles[i]);
    free(obstacles);
}