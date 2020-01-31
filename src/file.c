#include "../include/file.h"


void read_file_score(int scores[10]){
    FILE* f = fopen("./files/rank.txt","r");
    if (f == NULL)
        EXIT_FAILURE;
    char s[100];
    int i = 0 ;
    while(i < 10){
        fgets(s,99,f); 
        scores[i] = atoi(s);
        i++ ;
    }
    fclose(f);
}

int compare (const void * a, const void * b){
  return -( *(int*)a - *(int*)b );
}

void write_file_scores(int scores[10]){
    FILE* f = fopen("./files/rank.txt","w");
    if (f == NULL)
        EXIT_FAILURE;
    int i = 0 ;
    char s[100] ;
    qsort (scores, 10, sizeof(int), compare);
    while(i < 10){
        sprintf(s,"%d\n",scores[i]);
        fputs(s,f);
        strcpy(s,"");
        i++ ;
    }
    fclose(f);
}

void read_file_level(int level,int *hard,int *nb_enemies){
    char s[20];
    char c[10];
    FILE* file = NULL;
    strcpy(s,"./files/");
    sprintf(c,"%d",level);
    strcat(s,c);
    strcat(s,".txt");
    file = fopen(s,"r");
    if (file == NULL)
        EXIT_FAILURE;
    strcpy(c,"");
    fgets(c,5,file); 
    *nb_enemies = atoi(c);
    fgets(c,5,file);
    *hard = atoi(c);
    fclose(file);
}
