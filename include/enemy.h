#ifndef __ENEMY__
#define __ENEMY__

#include "background.h"



typedef struct enemy{
    Position pos ;
    int vitesse ; 
    int dx ;   
    struct enemy* sui ;
}Enemy,*ListEnemy;


typedef struct {
  Position pos ;
  int lifePoints ;
  int dx ;
}BigEnemy;

/*Une fonction qui alloue la mémoire pour un 
  ennemie prend en paramètre une liste chainée
  d'ennemies `*enemy` et trois entiers `x` , `y`et 'speed' */
int allocate_enemy(ListEnemy *enemy,int speed ,int x ,int y);

/*Une focntion qui rajoute un ennemie à une liste
  chainée d'ennemies ,elle prend en paramètre une
  liste chainée d'ennemies ListEnemy `*enemy` et
  deux entier `x` et `y`*/
int addEnemy(ListEnemy *lst,ListEnemy eListEnemy);

/*Une fonction qui initialise une liste d'ennemies
  ,elle prend en paramètre une liste chainée d'ennemie
   ListEnemy `*lst` et un ennemie`eListEnemy`.*/
void init_enemies(ListEnemy *enemies,int nbEnemies,int level);

/*Une fonction qui dessine les ennemies , elle prend
  en paramètre un eliste d'ennemie ListEnemy `*enemies`
  ,un entier `nbEnemies` et une imaged MLV_Image `*image`. */
void draw_enemies(ListEnemy* enemies,int nbEnemies,MLV_Image* image);

/*Une fonction qui fait bouger les ennemies ,elle
  prend en paramètre une liste d'ennemies ListEnemy `*enemies`*/
void move_enemies(ListEnemy *enemies);

/*Une fonction qui supprime un ennemie , elle prend 
 en paramètre une liste d'ennemies ListEnemy `*lst1` ,l'ennemie
 à enlever `lst2` et un entier pourle nombre d'ennemies
 à mettre à jour  `*nb_enemies` */
void deleteEnemy(ListEnemy *lst1 ,ListEnemy lst2,int *nb_enemies);

/*Une fonction qui libère la mémoire d'une liste d'ennemies ,elle prend
en paramètre la liste à liberer */
void free_enemies(Enemy *enemy);

/*Une focntion qui initie les boss ,elle prend en paramètre un pointure 
sur un BigEnemy '*bigEnemy' et un entier level.*/
void init_big_enemy(BigEnemy *bigEnemy,int level);

/*Une fonction qui affiche le boos ,elle prend en apramètre ce dernier et 
une image MLV_Image .*/
void draw_big_enemy(BigEnemy b,MLV_Image* pic);

/*Une fonction qui fait avancer le boos ,elle prend en paramètre 
un BigEnenmy '*b'.*/
void move_big_enemy(BigEnemy* b);
#endif