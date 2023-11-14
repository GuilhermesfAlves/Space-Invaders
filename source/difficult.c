#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../headers/difficult.h"

void get_historic(difficulties* difficulties){
    FILE* file;
    
    file = fopen(difficulties -> arq, "rb");

    if (file){
        fread(difficulties -> historic, sizeof(historic), QTD_P_HISTORIC, file);
        if (difficulties -> historic){
            fclose(file);
            return;
        }
    }

    for (int i = 0; i < QTD_P_HISTORIC; i++){
        difficulties -> historic -> data = strdup("00/00/00");
        difficulties -> historic -> points = 0;
        difficulties -> historic -> time = strdup("00:00");
    }
    fclose(file);
}

void write_historic(difficulties* difficulties){
    FILE* file;

    if (!(file = fopen(difficulties -> arq, "wb")));
        return;
    
    fwrite(difficulties -> historic, sizeof(historic), QTD_P_HISTORIC, file);
}

void set_difficulties(difficulties* difficulties, unsigned char type){
    char* name[MAX_DIFFICULTIES] = {"Easy", "Normal", "Hard", "Extreme"};
    char path[34];

    sprintf(path, "../database/%s.bin", name[type]);
     
    difficulties -> arq = strdup(path);
    difficulties -> name = strdup(name[type]);
    difficulties -> type = type;
    get_historic(difficulties);
}

difficult* add_difficult(unsigned char actual){
    difficult* new_difficult; 

    if (!(new_difficult = (difficult*) malloc(sizeof(difficult))))
        return NULL;

    new_difficult -> actual = actual;
    new_difficult -> show = 0;
    for (int i = 0; i < MAX_DIFFICULTIES; i++)
        set_difficulties(&new_difficult -> vec[i], i);

    return new_difficult;
}

void destroy_difficult(difficult* difficult){

    free(difficult);
}

void push_to_historic(){

}

char last_used_difficult(){
    char ind;

    FILE* LastUsed = fopen("database/LastUsedDifficult.txt", "r+"); 

    if (!LastUsed)
        return 0;

    ind = fgetc(LastUsed);
    fclose(LastUsed);

    return atoi(&ind); 
}

void save_last_used_difficult(unsigned char actual){
    FILE* LastUsed = fopen("database/LastUsedDifficult.txt", "w+"); 
    
    if (!LastUsed)
        return;

    fprintf(LastUsed, "%d", actual);
    fclose(LastUsed);
}