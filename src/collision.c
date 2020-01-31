#include "../include/collision.h"


void verifyCollisionShEn(ListShoot* lst,ListEnemy* en,int* nb_ennemies,int *score,Position* lifePoint){

    ListShoot tmps = *lst;
    ListEnemy tmpe = *en;
    
    while (tmpe != NULL){
        while (tmps != NULL){
            if (tmpe->pos.x <= tmps->pos.x && tmpe->pos.y <= tmps->pos.y &&
                tmpe->pos.x+30 >= tmps->pos.x && tmpe->pos.y+30 >= tmps->pos.y ){
                if (rand()%5 == 2){
                    lifePoint->x = tmpe->pos.x ;
                    lifePoint->y = tmpe->pos.y ;
                }
                deleteEnemy(en,tmpe,nb_ennemies);
                deleteShoot(lst,tmps);
                *score += 5 ;
            }
            tmps = tmps->sui ;
        }
        tmps = *lst ;
            
        tmpe = tmpe->sui ;

    }

}

void verifyCollisionRoShEn(Rocket* ro,ListShoot* lst){
    ListShoot tmps = *lst ;
    while (tmps != NULL){
        if (ro->pos.x <= tmps->pos.x && ro->pos.y <= tmps->pos.y &&
                ro->pos.x+30 >= tmps->pos.x && ro->pos.y+30 >= tmps->pos.y ){
            deleteShoot(lst,tmps);
            ro->lifePoints -= 1 ;
        }
        tmps = tmps->sui ;
    }
}

void verifyCollisionRoEn(Rocket *ro,ListEnemy *lst,int *nb_enemies){
    ListEnemy tmpe = *lst ;
    while (tmpe != NULL){
        if (ro->pos.x <= tmpe->pos.x && ro->pos.y <= tmpe->pos.y &&
                ro->pos.x+50 >= tmpe->pos.x && ro->pos.y+50 >= tmpe->pos.y ){
            deleteEnemy(lst,tmpe,nb_enemies);
            ro->lifePoints -= 1 ;
            *nb_enemies -= 1 ;
        }
        
        tmpe = tmpe->sui ;
    }

}

void verifyCollisionShBEN(ListShoot* lst,BigEnemy *en,int *score,int *level){
    ListShoot tmps = *lst ;
   
    while (tmps != NULL){
            if (en->pos.x+200 >= tmps->pos.x && en->pos.x <= tmps->pos.x
                && en->pos.y+200 >= tmps->pos.y && en->pos.y <= tmps->pos.y ){
                deleteShoot(lst,tmps);
                en->lifePoints -- ;
            }
        tmps = tmps->sui ;
    }

    if (en->lifePoints <= 0){
        *score += 50*(*level) ;
        (*level) ++ ;
    }
}



void verifyCollisionRoLP(Rocket* rocket,Position* posLife){
    if (rocket->pos.x >= posLife->x && rocket->pos.x <= posLife->x+30 &&rocket->pos.y >= posLife->y && rocket->pos.y <= posLife->y+30){
        posLife->x = -1;
        posLife->y = -1;
        rocket->lifePoints ++ ;
    }
}


void verifyCollisionRoShfellower(Rocket* ro,ListShoot lst,Position pos){
    ListShoot tmps = lst ;
    while (tmps != NULL){
        if (ro->pos.x <= tmps->pos.x && ro->pos.y <= tmps->pos.y &&
                ro->pos.x+30 >= tmps->pos.x && ro->pos.y+30 >= tmps->pos.y ){
            tmps->pos.x = pos.x;
            tmps->pos.y = pos.y;        
            ro->lifePoints -= 1 ;
        }
        tmps = tmps->sui ;
    }
}


void verify_all_collision(ListShoot* listP,ListShoot* listE,ListEnemy* enemies,Rocket *rocket,int *nb_enemies,BigEnemy *BigEn,int *level,Position* lifePoint,ListShoot fellower){
    if ((*level) % 10 != 0){
        verifyCollisionShEn(listP,enemies,nb_enemies,&(rocket->score),lifePoint);
        verifyCollisionRoShEn(rocket,listE);
        verifyCollisionRoEn(rocket,enemies,nb_enemies);
        verifyCollisionRoLP(rocket,lifePoint);
    }
    else {
        verifyCollisionShBEN(listP,BigEn,&(rocket->score),level);
        verifyCollisionRoShEn(rocket,listE);
        verifyCollisionRoShfellower(rocket,fellower,BigEn->pos);
    }
}