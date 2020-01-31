#include"../include/shoot.h"
							

void Move_shoot_player(ListShoot* s){
    ListShoot tmp = *s ;
	
	while (*s != NULL){	
		(*s)->pos.y -= (*s)->diry ;
		(*s)->pos.y -= (*s)->dirx ;
		(*s)= (*s)->sui ;
	}
	
	*s = tmp ;
}

void Move_shoot_enemy(ListShoot* s){
	ListShoot tmp = *s ;
	
	while (*s != NULL){	
		(*s)->pos.x += (*s)->dirx  ;
		
		(*s)->pos.y += (*s)->diry ;
		
		(*s) = (*s)->sui ;
	}

	*s = tmp ;
}

void Move_Shoot_fellower(ListShoot s,int rx,int ry,int x ,int y,int* life){
	while (s != NULL){
		if (s->pos.x < x)
			s->pos.x += 1 ; 
		if (s->pos.x > x)
			s->pos.x -= 1 ;
		if (s->pos.y < y)
			s->pos.y += 1 ;
		if (s->pos.y > y)
			s->pos.y -= 1 ;
		life -- ;
		s =s->sui ;
	}
	if (*life <= 0){
		s->pos.x = rx ;
		s->pos.y = ry ;
		*life = 30 ; 
	}
}

void draw_shoot(ListShoot lst){
	while (lst != NULL ){
		MLV_draw_filled_circle(lst->pos.x,lst->pos.y,2,MLV_COLOR_RED1);
		lst = lst->sui ;
	}	
	
}


void draw_shoot_enemy(ListShoot lst){
	while (lst != NULL ){
		MLV_draw_filled_circle(lst->pos.x,lst->pos.y,2,MLV_COLOR_GREEN1);
		lst = lst->sui ;
	}	
	
}

Position shoot_enemy_orient(double x,double y,double dx,double dy){
	Position pos ;
	double ata = atan((y-dy)/(x-dx-5));
	
	if (x >= dx)
		pos.x = cos(ata+3.14259)*3;
	if (x <= dx)
		pos.x = cos(ata)*3;
	if (y <= dy)
		pos.y = sin(ata)*3;
	if (x > dx)
		pos.y = sin(ata+3.14159)*3;
	return pos ;
}

int allocate_shoot(ListShoot* shoot,double x ,double y,double dx ,double dy){
	assert(*shoot == NULL);

	*shoot = (Shoot*)malloc(sizeof(Shoot));
	if ((*shoot)!= NULL){
		(*shoot)->pos.x = x  ;
        (*shoot)->pos.y = y  ;
        (*shoot)->demage = 5 ;
		(*shoot)->dirx = dx ;
		(*shoot)->diry = dy ;
        (*shoot)->sui = NULL ;
        return 1;
	}

	return 0;
}

void add_shoot_enemy(ListEnemy lstE,ListShoot *lst,double x,double y){
	Position pos ;
	while (lstE != NULL){
		pos = shoot_enemy_orient(lstE->pos.x,lstE->pos.y,x,y);
		add_shoot(lst,lstE->pos.x,lstE->pos.y,pos.x,pos.y);
		lstE = lstE->sui ;
	}
}

int add_shoot(ListShoot *lst,double x ,double y,double dx ,double dy){
	ListShoot tmp ;

	if((*lst) == NULL){
		return allocate_shoot(&(*lst),x,y,dx,dy); 
	}

	else {
		tmp = *lst ;	
		while(tmp->sui != NULL){
			tmp = tmp -> sui ;
		}
		
		return allocate_shoot(&(tmp->sui),x,y,dx,dy) ;  
	}
}


void free_list_shoot(ListShoot *liste){
	assert(*liste != NULL);

	ListShoot before = *liste;
	
	while (before->sui != NULL ){
		Shoot* t = before;
		free(t);
		before = before->sui ;
	}
	
	free(before);
	(before) = NULL ;
}


void deleteShoot(ListShoot *lst1 ,ListShoot lst2){
	ListShoot after ;
	ListShoot before ;
	
	assert(*lst1 != NULL);
	assert(lst2 != NULL);
	
	after = (*lst1)->sui ;

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
    
}

void remove_shoot_out(ListShoot *lst1 ){
	ListShoot tmp = *lst1 ;

	while (tmp != NULL){
		if (tmp->pos.y <= 0){
			deleteShoot(lst1,tmp);
		}
		tmp = tmp->sui ;
	}
}


void add_shoot_bigenemy(BigEnemy e,ListShoot *en,Position rocket){
    Position pos ;
	pos = shoot_enemy_orient(e.pos.x,e.pos.y,rocket.x,rocket.y);
    add_shoot(en,e.pos.x,e.pos.y,pos.x,pos.y);
	pos = shoot_enemy_orient(e.pos.x+50,e.pos.y,rocket.x,rocket.y);
    add_shoot(en,e.pos.x+50,e.pos.y,pos.x,pos.y);
	pos = shoot_enemy_orient(e.pos.x,e.pos.y+50,rocket.x,rocket.y);
    add_shoot(en,e.pos.x,e.pos.y+50,pos.x,pos.y);
	pos = shoot_enemy_orient(e.pos.x+50,e.pos.y+50,rocket.x,rocket.y);
    add_shoot(en,e.pos.x+50,e.pos.y+50,pos.x,pos.y);
	pos = shoot_enemy_orient(e.pos.x+150,e.pos.y,rocket.x,rocket.y);
    add_shoot(en,e.pos.x+150,e.pos.y,pos.x,pos.y);
	pos = shoot_enemy_orient(pos.x,e.pos.y+150,rocket.x,rocket.y);
    add_shoot(en,e.pos.x,e.pos.y+150,pos.x,pos.y);
}

void draw_shoot_fellower(ListShoot lst){
	while (lst != NULL ){
		MLV_draw_filled_circle(lst->pos.x,lst->pos.y,2,MLV_COLOR_BLUE);
		lst = lst->sui ;
	}	
	
}