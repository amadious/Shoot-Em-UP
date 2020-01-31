#ifndef __LEVEL__
#define __LEVEL__
#include "background.h"
#include "string.h"

/*Une fonction qui a pour role lire les scores dans un fcihier 
et les enregistrer dans un tableau d'entier .*/
void read_file_score(int scores[10]);

/*Une fonction qui remplie un fichier avec les scores sauvgardés dans
tableau d'entiers 'scores[10]' */
void write_file_scores(int scores[10]);

/*Une fonction qui prend en paramètre un entier 'level' et un pointure 
pour deux autres à modifier avec les donées lues depuis le fichier du niveau. */
void read_file_level(int level,int *hard,int *nb_enemies);

#endif