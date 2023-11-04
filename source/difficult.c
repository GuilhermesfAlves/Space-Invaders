#include <time.h>
#include <stdio.h>

#include "../headers/difficult.h"


historic_node* start_node(int points){
    historic_node* new_node;

    if (!(new_node = (historic_node*) malloc(sizeof(historic_node))))
        return NULL;

    new_node -> next = NULL;
    new_node -> points = points;
    new_node -> data = "\0";

    return new_node;
}

void destroy_node(historic_node* node){
    
    free(node -> data);
    free(node);
}

historic_node* get_historic(FILE* arq){
    historic_node* new;
    historic_node* previous = NULL;
    historic_node* head = NULL;
    int points;
    char* line;

    while(fscanf(arq, "%s", line)){
        new = start_node(atoi(strtok(line, " ")));
        new -> data = strdup(strtok(NULL, " "));
        if (!head)
            head = new;
        else if (!previous)
            previous = head;
        previous -> next = new;
    }
    return head;
}

difficult* start_difficult(){
    difficult* new_difficult;

    if (!(new_difficult = (difficult*) malloc(MAX_DIFFICULTIES*sizeof(difficult))))
        return NULL;

    new_difficult -> actual = 0;
    new_difficult -> show = 0;
    new_difficult -> vec[0] -> arq = fopen("Easy.txt","r+");
    new_difficult -> vec[0] -> name = strdup("Easy");
    new_difficult -> vec[0] -> type = Easy;
    new_difficult -> vec[0] -> node = get_historic(new_difficult -> vec[0] -> arq);
    new_difficult -> vec[1] -> arq = fopen("Normal.txt","r+");
    new_difficult -> vec[1] -> name = strdup("Normal");
    new_difficult -> vec[1] -> type = Normal;
    new_difficult -> vec[1] -> node = get_historic(new_difficult -> vec[1] -> arq);
    new_difficult -> vec[2] -> arq = fopen("Hard.txt","r+");
    new_difficult -> vec[2] -> name = strdup("Hard");
    new_difficult -> vec[2] -> type = Hard;
    new_difficult -> vec[2] -> node = get_historic(new_difficult -> vec[2] -> arq);
    new_difficult -> vec[3] -> arq = fopen("Extreme.txt","r+");
    new_difficult -> vec[3] -> name = strdup("EXTREME");
    new_difficult -> vec[3] -> type = Extreme;
    new_difficult -> vec[3] -> node = get_historic(new_difficult -> vec[3] -> arq);
    
    return new_difficult;
}

void destroy_difficult(difficult* difficult){

    for (int i = 0; i < MAX_DIFFICULTIES; i++){
        free(difficult -> vec[i] -> name);
        fclose(difficult -> vec[i] -> arq);
        for (historic_node* aux = difficult -> vec[i] -> node; aux; difficult -> vec[i] -> node){
            difficult -> vec[i] -> node = aux -> next;
            free(aux -> data);
            free(aux);
        }
    }
    free(difficult);
}


