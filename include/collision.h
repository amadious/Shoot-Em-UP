#ifndef __COLLISION__
#define __COLLISION__

#include "background.h"
#include "shoot.h"
#include "enemy.h"
#include "rocket.h"

/*Une focntion qui verifie les collisions entre le tir du joueur et et les 
ennemis ,elle prend en paramètre une liste chainée de tir ListShoot `*lst` ,
une liste chainée d'ennemis ListEnemy `*en` et deux entiers `nb_ennemies` et un `scores`*/
void verifyCollisionShEn(ListShoot *lst, ListEnemy *en, int *nb_ennemies, int *score, Position *lifePoint);

/*Une focntion qui verifie les collisions entre le vaisseau et les tirs des ennemis ,
elle prend en paramètre un pointure vers une lsite de tirs '*lst' et un Rocket '*ro' */
void verifyCollisionRoShEn(Rocket *ro, ListShoot *lst);

/*Une fonction qui verifie les collisions entre le vaisseau et les ennemis ,
elle prend en paramètre une liste chainée de tirs ListShoot `*lst` ,
un Rocket '*ro' et un pointure vers un entier '*nb_enemies' .*/
void verifyCollisionRoEn(Rocket *ro, ListEnemy *lst, int *nb_enemies);

/*Une fonction qui vérifie les collisions entrez les tirs du,joueur et le boss ,
elle prend en paramètre une liste chainée de tirs ListShoot '*lst ',un pointure BigEnemy*
et deux pointure vers deux entiers '*score' et '*level' .*/
void verifyCollisionShBEN(ListShoot *lst, BigEnemy *en, int *score, int *level);

/*Une fonction qui fait appel à toutes les collisions pendant la partie. */
void verify_all_collision(ListShoot *listP, ListShoot *listE, ListEnemy *enemies, Rocket *rocket, int *nb_enemies, BigEnemy *BigEn, int *level, Position *lifePoint, ListShoot fellower);

#endif