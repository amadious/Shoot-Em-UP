#include "../include/background.h"

void gener_stars(Stars *t){
	int i;
	for(i=0; i < MAXSTAR; i++ ){
		t->x[i] = rand() % 600+1;
		t->y[i] = rand() % 600+1;
		t->size[i] = rand() % 2+0.5;
		t->speed[i] = rand() % 15+1;
		t->active[i] = 1;
		t->r[i] = 255;
		t->g[i] = 255;
		t->b[i] = 255;
	}
}

MLV_Color make_color (int i ) {
	return MLV_rgba(255, 255,255, 255-i);
}

void draw_stars(Stars* t){
	
	int i;
	
	for(i=0; i<MAXSTAR; i++){
		if (t->active[i])
			MLV_draw_filled_circle( t->x[i], t->y[i] , t->size[i],make_color(i) );
		if (t->y[i] >= 600){
			t->y[i] = 0 ;
			t->active[i] = MLV_get_random_integer(0,2); 
		}
		else if (t->y[i] < 600)
			t->y[i] += t->speed[i] ;
	}	
}

void detect_move(MLV_Keyboard_button key_sym,int *x ,int *y,int vitesse){
	if (MLV_get_keyboard_state(MLV_KEYBOARD_UP ) == MLV_PRESSED)
		*y -= vitesse ;

	if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
		*y += vitesse ;
	
	if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
		*x -= vitesse ;
	
	if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
		*x += vitesse ;		
}

void draw_rocket(int x ,int y,MLV_Image *Image){
	MLV_draw_image (Image,x,y);
}


void draw_level(int level){
    int length = snprintf( NULL, 0, "%d", level );
	char l[length+9];
	sprintf(l, "Level :%d", level); 
	MLV_draw_text(0,0,l,MLV_COLOR_ALICE_BLUE);
}

void draw_scores(int s){
    int length = snprintf( NULL, 0, "%d", s );
	char score[length+10];
	sprintf(score, "score : %d", s); 
	MLV_draw_text(0,HEIGHT-15,score,MLV_COLOR_ALICE_BLUE);
}

void draw_lifes(int lifes,MLV_Image *Image){
	int i ;
	for (i = 0; i < lifes; i++){
		MLV_draw_image(Image,i*10,HEIGHT-30);
	}
	
}

void draw_life(Position *pos,MLV_Image * image){
	if (pos->x != -1 && pos->y != -1 && pos->y < HEIGHT){
		pos->y ++ ;
		MLV_draw_image(image,pos->x,pos->y);
	}
}

void pause_game(MLV_Keyboard_button  *key_sym){
	
	if (*key_sym == MLV_KEYBOARD_p){
		MLV_draw_text(30,HEIGHT/2,"vous avez mis la partie en pause.",MLV_COLOR_GREEN1);
		MLV_draw_text(30,HEIGHT/2+30,"appuyer sur une touche de clavier pour sortir de la pause",MLV_COLOR_GREEN1);
		MLV_actualise_window();
		MLV_wait_keyboard(key_sym,NULL,NULL);
		MLV_clear_window(MLV_COLOR_BLACK);
	}
}


void instruct_window(){
	int px,py = 0 ;		

	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_text(20,20,"-Pour déplacer le vaisseau utilisez les flèches du clavier.",MLV_COLOR_BLUE);
	MLV_draw_text(20,50,"-Pour tirer avec vaisseau utilisez la touhce 'x'.",MLV_COLOR_BLUE);
	MLV_draw_text(20,80,"-vous  évitez les tir des ennemis.",MLV_COLOR_BLUE);
	MLV_draw_text(20,110,"-vous  récupérer les coeurs pour gagner des points de vie.",MLV_COLOR_BLUE);
	MLV_draw_text(WIDTH - 60,HEIGHT - 30,"retour",MLV_COLOR_RED1);
	MLV_actualise_window();

	while (px <= WIDTH-60 || px >= WIDTH - 10 || py <= HEIGHT - 30 ||
		py >= HEIGHT - 10 || MLV_get_mouse_button_state(MLV_BUTTON_LEFT ) != MLV_PRESSED){
		MLV_get_mouse_position	(&px,&py );	
	}		
	first_window();
}

void best_scores_window(){
    FILE* file = fopen("files/rank.txt","r");
	char s[10];
    int i = 15 ;
	int cpt = 1;
	int px,py = 0 ;
	char rank[6];


    MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_text(5,5,"Liste de meilleurs scores :",MLV_COLOR_BLUE);
	while (fgets(s,10,file) != NULL){
		sprintf(rank, "%d . ", cpt); 
        MLV_draw_text(10,i,rank,MLV_COLOR_BLUE);
		MLV_draw_text(35,i,s,MLV_COLOR_BLUE);
		i += 10 ;
		cpt ++ ;
	}
	MLV_draw_text(WIDTH - 60,HEIGHT - 30,"retour",MLV_COLOR_RED1);
	MLV_actualise_window();
	while (px <= WIDTH-60 || px >= WIDTH - 10 || py <= HEIGHT - 30 ||
		 py >= HEIGHT - 10 || MLV_get_mouse_button_state(MLV_BUTTON_LEFT ) != MLV_PRESSED){
		MLV_get_mouse_position	(&px,&py );	
	}	
	fclose(file);
	first_window();
}

void first_window(){
	MLV_Image * img1 ;
	MLV_Image * img2 ;
	int px,py = 0;
	img1 = MLV_load_image("media/space.jpg");
	img2 = MLV_load_image("media/upem.png");

	MLV_resize_image_with_proportions(img2,WIDTH/4,HEIGHT/4);
	
	MLV_draw_image(img1,0,0);
	MLV_draw_image(img2,0,0);

	while (px < WIDTH/7+5 ||  px  > WIDTH/7+100  || MLV_get_mouse_button_state(MLV_BUTTON_LEFT ) != MLV_PRESSED){
		MLV_get_mouse_position	(&px,&py );	
		if (px >= WIDTH/7+5 && px <= WIDTH/7+100 && py >= HEIGHT/7 + 5 && py <= HEIGHT/7 + 20 ){	
			MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 5,"JOUER",MLV_COLOR_RED1);
		}
		if (px >= WIDTH/7+5 && px <= WIDTH/7+100 && py >= HEIGHT/7 + 20 && py <= HEIGHT/7 + 70){
			MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 50,"INSTRUCTION",MLV_COLOR_RED1);
		}
		if (px >= WIDTH/7+5 && px <= WIDTH/7+100 && py >= HEIGHT/7 + 70 && py <= HEIGHT/7 + 120){		
			MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 100,"Meilleurs scores",MLV_COLOR_RED1);	
		}
		MLV_actualise_window();
		MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 5,"JOUER",MLV_COLOR_WHITE);
		MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 50,"INSTRUCTION",MLV_COLOR_WHITE);
		MLV_draw_text(WIDTH/7 + 5,HEIGHT/7 + 100,"Meilleurs scores",MLV_COLOR_WHITE);	
	}
	if (px >= WIDTH/7+5 && px <= WIDTH/7+100 && py >= HEIGHT/7 + 70 && py <= HEIGHT/7 + 120)
		best_scores_window();
	if (px >= WIDTH/7+5 && px <= WIDTH/7+100 && py >= HEIGHT/7 + 20 && py <= HEIGHT/7 + 70)
		instruct_window();	

}


void win_window(){
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_text(30,HEIGHT/2,"vous avez gagné :))",MLV_COLOR_GREEN1);
	MLV_actualise_window();
	MLV_wait_seconds(5);
}

void lose_window(){
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_text(30,HEIGHT/2,"vous avez perdu :(",MLV_COLOR_GREEN1);
	MLV_actualise_window();
	MLV_wait_seconds(5);
}