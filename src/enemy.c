#include "../include/enemy.h"


int allocate_enemy(ListEnemy *enemy,int speed,int x ,int y){
	*enemy=(Enemy*)malloc(sizeof(Enemy));

	if ((*enemy)!= NULL){
            (*enemy)->pos.x = x ;
            (*enemy)->pos.y = y ;
            (*enemy)->vitesse = speed ;
            (*enemy)->dx = 1 ;
            (*enemy)->sui = NULL ;        
            return 1;
	}

	return 0;
}

int addEnemy(ListEnemy *lst,ListEnemy eListEnemy){
	if((*lst) == NULL){
		*lst = eListEnemy ;
		return 1 ; 
	}

	ListEnemy temp = *lst ;
	
	
	while((*lst)->sui != NULL){
		(*lst) = (*lst) -> sui ;
	}
	(*lst) ->sui = eListEnemy ;
	(*lst) = temp ;
	return 1;   
}

void init_enemies(ListEnemy *enemies,int nbEnemies,int level){
    int i,j,x = 0 ;
    assert(nbEnemies >= 1);

    ListEnemy tmp = NULL;
    j = 0 ;
    for (i = 0; i < nbEnemies ; i++){
            if(40*x > WIDTH-40){ 
                j += 40 ;
                allocate_enemy(&tmp,level,40*x,j);
                x = 0 ;
            }
            else {
                allocate_enemy(&tmp,level,40*x,j);
                x ++ ;
            }
            addEnemy(enemies,tmp);
    }
    
}


void draw_enemies(ListEnemy* enemies,int nbEnemies,MLV_Image* image){
    ListEnemy tmp = *enemies;

    while (tmp != NULL){
        MLV_draw_image (image,tmp->pos.x,tmp->pos.y);
        tmp = tmp->sui ;
    }

}


void move_enemies(ListEnemy *enemies){
    ListEnemy tmp = *enemies ;

    while (*enemies != NULL){
        if ((*enemies)->pos.x >= WIDTH || (*enemies)->pos.x < 0 ){
            (*enemies)->dx = (*enemies)->dx * (-1) ;
            (*enemies)->pos.y += 40 ;    
        }

        (*enemies)->pos.x += (*enemies)->dx;

        *enemies = (*enemies)->sui ;
    }
    *enemies = tmp ;
}




void deleteEnemy(ListEnemy *lst1 ,ListEnemy lst2,int *nb_enemies){
	ListEnemy after = (*lst1)->sui;
	ListEnemy before ;
    assert(*lst1 != NULL);

    if (*lst1 == lst2){
		free(*lst1);
		(*lst1) = NULL;
		(*lst1) = after;		
	}
	
    else {
		after = *lst1 ;
		while (after != lst2 ){
			before = after ;
            after = after->sui ;
		}
		before->sui = after->sui ;
        free(after);
		(after) = NULL;
        
	}
    *nb_enemies -= 1 ;
}


void free_enemies(ListEnemy enemy){
    ListEnemy tmp ;
    while (enemy != NULL){
        tmp = enemy->sui ;
        free(enemy);
        enemy = NULL ;
        enemy = tmp ;
    }
}

void init_big_enemy(BigEnemy *bigEnemy,int level){
    bigEnemy->lifePoints = level*10 ;
    bigEnemy->pos.x = 10;
    bigEnemy->pos.y = 10;
}

void draw_big_enemy(BigEnemy b,MLV_Image* pic){
    MLV_draw_image(pic,b.pos.x,b.pos.y);
}

void move_big_enemy(BigEnemy* b){
    if (b->pos.x == WIDTH - WIDTH/3)
        b->dx -=1 ;
    if (b->pos.x == 10)
        b->dx +=1 ;   

    b->pos.x += b->dx ;

}

