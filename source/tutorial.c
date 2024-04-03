#include "../headers/tutorial.h"
#include <stdio.h>

unsigned char show_tutorial(){
    char ind;

    FILE* Tutorial = fopen("database/ShowTutorial.txt","r"); 

    if (!Tutorial)
        return 0;

    ind = fgetc(Tutorial);
    fclose(Tutorial);
    return atoi(&ind); 
}

void save_preference(unsigned char current){
    
    FILE* Tutorial = fopen("database/ShowTutorial.txt","w"); 
    
    if (!Tutorial)
        return;

    fprintf(Tutorial, "%d", current);
    fclose(Tutorial);
}