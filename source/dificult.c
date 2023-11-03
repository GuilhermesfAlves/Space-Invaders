#include <time.h>
#include <stdio.h>

#include "../headers/dificult.h"


historic_node* start_node(int points){
    historic_node* new_node;

    if (!(new_node = (historic_node*) malloc(sizeof(historic_node))))
        return NULL;

    new_node -> next = NULL;
    new_node -> points = points;
    new_node -> data = "\0";
}

void node_destroy(historic_node* node){
    
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

dificult* start_dificult(){
    dificult* new_dificult;

    if (!(new_dificult = (dificult*) malloc(MAX_DIFICULTIES*sizeof(dificult))))
        return NULL;

    new_dificult -> actual = 0;
    new_dificult -> show = 0;
    new_dificult -> vec[0] -> arq = fopen("Easy.txt","r+");
    new_dificult -> vec[0] -> name = strdup("Easy");
    new_dificult -> vec[0] -> type = Easy;
    new_dificult -> vec[0] -> node = get_historic(new_dificult -> vec[0] -> arq);
    new_dificult -> vec[1] -> arq = fopen("Normal.txt","r+");
    new_dificult -> vec[1] -> name = strdup("Normal");
    new_dificult -> vec[1] -> type = Normal;
    new_dificult -> vec[1] -> node = get_historic(new_dificult -> vec[1] -> arq);
    new_dificult -> vec[2] -> arq = fopen("Hard.txt","r+");
    new_dificult -> vec[2] -> name = strdup("Hard");
    new_dificult -> vec[2] -> type = Hard;
    new_dificult -> vec[2] -> node = get_historic(new_dificult -> vec[2] -> arq);
    new_dificult -> vec[3] -> arq = fopen("Extreme.txt","r+");
    new_dificult -> vec[3] -> name = strdup("EXTREME");
    new_dificult -> vec[3] -> type = Extreme;
    new_dificult -> vec[3] -> node = get_historic(new_dificult -> vec[3] -> arq);
    
}

void dificult_destroy(dificult* dificult){

    for (int i = 0; i < MAX_DIFICULTIES; i++){
        free(dificult -> vec[i] -> name);
        fclose(dificult -> vec[i] -> arq);
        for (historic_node* aux = dificult -> vec[i] -> node; aux; dificult -> vec[i] -> node){
            dificult -> vec[i] -> node = aux -> next;
            free(aux -> data);
            free(aux);
        }
    }
    free(dificult);
}


