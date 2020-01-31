#ifndef __SHOOT__
#define __SHOOT__

#include "background.h"
#include "enemy.h"

typedef struct shoot{
    Position pos ;
    int demage ;
    struct shoot* sui ;
    double dirx ;
    double diry ;
}Shoot,*ListShoot;


/*Une fonction qui déplace les tirs de l'ennemies
  elle prend en paramètre une liste chainée de tirs 
  ListShoot `*s`.*/
void Move_shoot_player(ListShoot* s);

/*Une focntion qui dessine les tirs ,elle 
    prend en paramètre une liste de tirs ListShoot
    `lst`. */
void draw_shoot(ListShoot lst);

/*Une focntion qui fait avancer les ennemis,Elle prend
en paramètre une liste d'ennemies.*/
void Move_shoot_enemy(ListShoot* s);


/*Une fonction qui affiches une lsite d'ennemies */
void draw_shoot_enemy(ListShoot lst);

/*Une focntion qui a pour roler de définir l'orientation d'un 
tir ennemie ,elle renvoie une position et prend en paramètre 4 doubles
qui font référence à la postion du joueur et de l'ennemie.*/
Position shoot_enemy_orient(double x,double y,double dx,double dy);

/*Une focntion qui prend en paramètre un pointure vers une lsite de tirs
et 4 doubles ,elle a pour rôle la mémoire pour un tir.*/
int allocate_shoot(ListShoot *shoot,double x ,double y,double dx,double dy);

/*Une fonction qui ajoute un tir à tout les ennmies de la meme liste
elle prend en paramètre une lsite d'ennemies ,liste de tir à remplir et 
deux doubles pour les coordonées du joueur à viser.
*/
void add_shoot_enemy(ListEnemy lstE,ListShoot *lst,double x,double y);

/*Une fonction qui ajoute à un tir à une lsite de tirs ,elle prend en pramaètre
4 doubles (x,y,dx et dy) et une lsite de tirs '*lst'.*/
int add_shoot(ListShoot *lst,double x ,double y,double dx ,double dy);

/*Une fonction qui prend en paramètre un pointure sur une liste de tirs '*liste'
 qu'elle va libérer */
void free_list_shoot(ListShoot *liste);

/*Une fonction qui prend enlève un tir d'une liste de tirs.*/
void deleteShoot(ListShoot *lst1 ,ListShoot lst2);

/*Unr fonction qui prend en paramètre une liste de tirs ,elle a
pour rôle d'enlever les tirs qui sont en dehors de la fenêtre*/
void remove_shoot_out(ListShoot *lst1 );

/*Une fonction qui fait avancer un missile à tête chercheuse,elle prend 
en paramètre 5 entiers et une lsite de tirs .*/
void Move_Shoot_fellower(ListShoot s,int rx,int ry,int x ,int y,int* life);

/*Une fonction qui prend en paramètre un grand ennemie */
void add_shoot_bigenemy(BigEnemy e,ListShoot *en,Position rocket);

/*une fonction qui dessine le missile à tete chercheuse.*/
void draw_shoot_fellower(ListShoot lst);

#endif