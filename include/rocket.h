#ifndef __SHIP__
#define __SHIP__

#include "background.h"




typedef struct {
	Position pos ;
	int lifePoints ;
	int level ;
	int speed ;
	int score ;
}Rocket;



/*Une fonction qui initie le vaisseau , elle prend en paramètre un
	pointure */
void init_rocket(Rocket *s);

/*Une fonction qui fait avancer le vaisseau ,elle prend en paramètre 
le vaisseau et deu entiers .*/
void move_rocket(Rocket *s, int x, int y);

/*Une focntion libère la mémoire allouée au vaisseau.
Elle prend en paramètre un pointure vers Rocket '*rocket'*/
void free_rocket(Rocket *rocket);

#endif 