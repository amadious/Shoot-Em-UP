#ifndef __BACKGROUND__
#define __BACKGROUND__
#define _POSIX_C_SOURCE 199309L
/* LIBRARY */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <MLV/MLV_all.h>


#define BILLION  1000000000L;

#define MAXSTAR 256
#define WIDTH 600
#define HEIGHT 600 


typedef struct{
	double x;
	double y;
}Position;


typedef struct star{
	int x[MAXSTAR] ;
	int y[MAXSTAR];
	int size[MAXSTAR];
	int speed[MAXSTAR];	
	int active[MAXSTAR];
	int r[MAXSTAR];
	int g[MAXSTAR];
	int b[MAXSTAR];
}Stars;




/*Une fonction qui genère des étoiles ,elle 
  prend en paramètre un pointure sur une 
  Stars `*t` à génerer . */
void gener_stars(Stars *t);

/*Une fonction qui génere une couleur,elle
  prend en paramètre un enitier int `i`,
  elle renvoie une couleur (Blanc) MLV_Color avec 
   une transparence égale à 255-1 .*/
MLV_Color make_color (int i );

/*Une fonction qui affichent les étoiles ,
	elle prend en paramètre un tableau de 
	Stars `*t` .*/
void draw_stars(Stars* t);

/*Une fonction qui detecte le mouvement 
	et decide de la direction à prendre ,elle
	prend en parmètre un bouton de clavier 
	MLV_Keyboard_button `key_sym` ,deux entiers
	`*x`et`*y` et un entier `vitesse`. */
void detect_move(MLV_Keyboard_button key_sym,int *x ,int *y,int vitesse);

/*Une fonction qui permet de dessiner un vaisseau ,
	elle prend en paramètre une cordonée x et y et 
	une image pour le vaisseau à afficher.*/
void draw_rocket(int x ,int y,MLV_Image *Image);

/*Une focntion qui permet de dessiner le niveau,
elle prend en paramètre un entier .*/
void draw_level(int level);

/*Une fonction qui affiche les vies quand 
on joue ,elle prend en paramètre le nombre 
de vies et une image de cette dernière.*/
void draw_lifes(int lifes,MLV_Image *Image);

/*une focntion qui affiche uen vie à à prendre 
par le joeur pour gagner un poit de vie . */
void draw_life(Position *pos,MLV_Image * image);

/*Une focntion qui affiche le score du jeu.
Elle predn en apramètre une entier 's*/
void draw_scores(int s);

/*Une fonction qui met le jeu en Pause,elle prend
en paramètre un MLV_Keyboard_button '*key_sym'. */
void pause_game(MLV_Keyboard_button  *key_sym);

/*Une fonction qui affiche la fenêtre pour
les instructions.*/
void instruct_window();

/*Une focntion qui affiche une fenêtre des 
meilleurs scores.*/
void best_scores_windows();

/*Une focntion qui affiche la première fenêtre .*/
void first_window();

/*Une focntion qui affiche une fenetre en cas de de victoire*/
void win_window();

/*Une focntion qui affiche une fenetre en cas de de défaite*/
void lose_window();
#endif 
