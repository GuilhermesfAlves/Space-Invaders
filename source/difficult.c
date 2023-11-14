#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../headers/difficult.h"

void get_historic(difficulties* difficulties){
    FILE* file;
    
    if (!(file = fopen(difficulties -> arq, "rb")))
        return;

    fread(difficulties -> historic, sizeof(historic), QTD_P_HISTORIC, file);
    fclose(file);
}

void write_historic(difficulties* difficulties){
    FILE* file;

    if (!(file = fopen(difficulties -> arq, "wb")))
        return;
    printf("escrito\n");
    
    fwrite(difficulties -> historic, sizeof(historic), QTD_P_HISTORIC, file);
    fclose(file);
}

void set_difficulties(difficulties* difficulties, unsigned char type){
    char* name[MAX_DIFFICULTIES] = {"Easy", "Normal", "Hard", "Extreme"};
    char path[34];

    sprintf(path, "database/%s.bin", name[type]);
     
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

void add_new_points(struct tm* time_info, historic* historic, int points){
    char line[15];

    historic -> points = points;
    sprintf(line, "%d/%d/%d", time_info -> tm_mday, time_info -> tm_mon, time_info -> tm_year % 100);
    historic -> data = strdup(line);
    sprintf(line, "%d:%d", time_info -> tm_hour, time_info -> tm_min);
    historic -> data = strdup(line);
}

void push_to_historic(int points, difficulties* difficulties){
    time_t current_time;
    struct tm* time_info;
    int set = -1;

    time(&current_time);
    time_info = localtime(&current_time);

    for (int i = 0; i < QTD_P_HISTORIC; i++){
        if (difficulties -> historic[i].points == 0){
            add_new_points(time_info, &difficulties -> historic[i], points);
            return;
        }
        if (difficulties -> historic[i].points < points){
            set = i;
            break;
        }
    }
    /*não entra nas 10 melhores*/
    if (set == -1)
        return;

    for (int j = QTD_P_HISTORIC - 1; j > set; j--){
        difficulties -> historic[j].data = difficulties -> historic[j - 1].data;
        difficulties -> historic[j].time = difficulties -> historic[j - 1].time;
        difficulties -> historic[j].points = difficulties -> historic[j - 1]. points;
    }
    add_new_points(time_info, &difficulties -> historic[set], points);
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