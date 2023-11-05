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

    // while(fgets(line, 1024, arq)){
    //     new = start_node(atoi(strtok(line, " ")));
    //     new -> data = strdup(strtok(NULL, " "));
    //     if (!head)
    //         head = new;
    //     else if (!previous)
    //         previous = head;
    //     previous -> next = (struct historic_node*) new;
    // }
    return head;
}

difficulties* add_difficulties(char** actual, unsigned char type){
    difficulties* new_difficulties;
    char path[34];

    sprintf(path, "../database/%s.txt", actual[type]);
     
    if (!(new_difficulties = (difficulties*) malloc(sizeof(difficulties))))
        return NULL;
    
    new_difficulties -> arq = fopen(path,"r+");
    new_difficulties -> name = strdup(actual[type]);
    new_difficulties -> type = type;
    new_difficulties -> node = get_historic(new_difficulties -> arq);

    return new_difficulties;
}

difficult* add_difficult(){
    difficult* new_difficult; 
    char* name[MAX_DIFFICULTIES] = {"Easy", "Normal", "Hard", "Extreme"};
    char** passed;

    if (!(new_difficult = (difficult*) malloc(sizeof(difficult))))
        return NULL;

    if (!(new_difficult -> vec = (difficulties**) malloc(MAX_DIFFICULTIES*sizeof(difficulties*))))
        return NULL;

    new_difficult -> actual = 0;
    new_difficult -> show = 0;
    for (int i = 0; i < MAX_DIFFICULTIES; i++)
        new_difficult -> vec[i] = add_difficulties(name, i);
    
    return new_difficult;
}

void destroy_difficult(difficult* difficult){

    for (int i = 0; i < MAX_DIFFICULTIES; i++){
        free(difficult -> vec[i] -> name);
        fclose(difficult -> vec[i] -> arq);
        for (historic_node* aux = difficult -> vec[i] -> node; aux; difficult -> vec[i] -> node){
            difficult -> vec[i] -> node = (historic_node*) aux -> next;
            free(aux -> data);
            free(aux);
        }
    }
    free(difficult);
}


