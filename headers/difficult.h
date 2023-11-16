#ifndef __SI_DIFFICULT__
#define __SI_DIFFICULT__
#include "allegro_headers.h"

#define MAX_DIFFICULTIES 4
#define QTD_P_HISTORIC 10

enum diff_mode {Diff_Easy, Diff_Normal, Diff_Hard, Diff_Extreme};

typedef struct{
    int points;
    char data[10];
    char time[8];
}historic;

typedef struct{
    char* name;
    char type;
    char* arq;
    historic historic[QTD_P_HISTORIC];
}difficulties;

typedef struct{
    unsigned char show;
    unsigned char current;
    difficulties vec[MAX_DIFFICULTIES];
}difficult;

void write_historic(difficulties* difficulties);
void push_to_historic(int points, difficulties* difficulties);
void get_historic(difficulties* difficulties);

difficult* add_difficult(unsigned char current);
void destroy_difficult(difficult* difficult);

char last_used_difficult();
void save_last_used_difficult(unsigned char current);

#endif //__DIFFICULT__