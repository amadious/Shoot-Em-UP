#include "../include/rocket.h"


void avance_missile(Position *pos){
		pos->y=pos->y-1;				
}

void init_rocket(Rocket *s){
	s->pos.x = 300 ;
	s->pos.y = 550 ;
	s->lifePoints = 5;
	s->level = 1 ;
	s->speed = 5 ;
	s->score = 0 ;
}


void move_rocket(Rocket *s, int x, int y){
	if(s->pos.x > x && s->pos.x > s->speed ){
		s->pos.x -= s->speed;
	}
	
	if(s->pos.x < x && s->pos.x < WIDTH - s->speed){
		s->pos.x += s->speed;
	}
	
	if(s->pos.y > y && s->pos.y > 0){
		s->pos.y -= s->speed;
	}

	if(s->pos.y < y && s->pos.y < HEIGHT - 30){
		s->pos.y += s->speed;	
	}
}



