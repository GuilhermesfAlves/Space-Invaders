#include "../headers/obstacles.h"

obstacles* add_obstacles(unsigned char level, int height, int width){
    obstacles* new_obstacles;
    int qtd;

    switch (level){
    case 0:
        qtd = 6;
        break;
    case 1:
        qtd = 5;
        break;
    case 2:
        qtd = 4;
        break;
    case 3:
        qtd = 2;
        break;
    default:
        return NULL;
    }
    if (!(new_obstacles = (obstacles*) malloc(qtd*sizeof(obstacles))))
        return NULL;

    for (int i = 0; i < qtd; i++){
        new_obstacles[i].life = 10;
        new_obstacles[i].pos_x = (width/2) + (i - qtd)*3;
        new_obstacles[i].pos_y = height*0.65; 
    }
    return new_obstacles;
}

void destroy_obstacles(obstacles* obstacles){

    free(obstacles);
}