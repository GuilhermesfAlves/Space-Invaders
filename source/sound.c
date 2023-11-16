#include "../headers/sound.h"

int set_ship_sounds(ship* ship){

    if (!ship)
        return -1;
    if (!(ship -> death_s = al_load_sample("sound/explosion.wav")))
        return -1;
    if(!(ship -> shoot_s = al_load_sample("sound/shoot.wav")))
        return -1;
    return 1;
}

int set_enemy_sounds(enemy* enemie){
    ALLEGRO_SAMPLE* sample;

    if (!(enemie -> death_s = al_load_sample("sound/invaderkilled.wav")))
        return -1;
    
    return 1;
}

int set_enemies_sounds(enemy*** enemies, int lines, int rows){
    ALLEGRO_SAMPLE* sample;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < rows; j++){
            if (!enemies[i][j])
                continue;
            if (!(enemies[i][j] -> death_s = al_load_sample("sound/invaderkilled.wav")))
                return -1;
            }
    return 1;
}

int set_game_sounds(game* game){
    char path[50];

    if (!(set_ship_sounds(game -> space -> ship)))
        return -1;
    if (!(set_enemies_sounds(game -> space -> map, game -> space -> lines, game -> space -> rows)))
        return -1;

    if (!(game -> move_s = (ALLEGRO_SAMPLE**) malloc(MOVE_SOUNDS*sizeof(ALLEGRO_SAMPLE*))))
        return -1;

    for (int i = 0; i < MOVE_SOUNDS; i++){
        sprintf(path, "sound/fastinvader%d.wav", i);
        if (!(game -> move_s[i] = al_load_sample(path)))
            return -1;
    }
    return 1;
}

void destroy_game_sounds(game* game){

    for (int i = 0; i < MOVE_SOUNDS; i++)
        al_destroy_sample(game -> move_s[i]);
    
}