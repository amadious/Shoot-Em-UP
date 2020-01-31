#include "../include/background.h"
#include "../include/rocket.h"
#include "../include/enemy.h"
#include "../include/shoot.h"
#include "../include/collision.h"
#include "../include/file.h"



int main(int argc,char const *argv[]){
	
	MLV_Event event;
	int x = 300; int y = 550;
	Rocket rocket ;
	ListEnemy enemies = NULL;
	BigEnemy bigEnemy ;
	Position lifePoint ;
	ListShoot fellower ;

	struct timespec start, stop;
    double accum;

	Stars t;
	int scores[10] = {0};
	int nb_enemies = 10 ;
	int level = 7 ;
	int hard = 70 ;
	int fellowerLife = 30 ;
	ListShoot listP = NULL;
	ListShoot listE = NULL;
	MLV_create_window 	("projetC","projetC",WIDTH,HEIGHT);


	
	MLV_Image *imageRocket,*imageEnemy,*imageLifes,*imageEnemy2 = NULL;
	MLV_Keyboard_button  key_sym ;


	
	imageRocket = MLV_load_image( "media/vessel1.gif");
	imageEnemy = MLV_load_image( "media/enemy1.gif");
	imageLifes = MLV_load_image( "media/life.gif");
	imageEnemy2 = MLV_load_image( "media/enemy2.gif");
	
	MLV_resize_image_with_proportions(imageRocket,30,30);
	MLV_resize_image_with_proportions(imageEnemy2,200,200);
	MLV_resize_image_with_proportions(imageEnemy,30,30);
	MLV_resize_image_with_proportions(imageLifes,10,10);

    first_window();

	read_file_score(scores);

	gener_stars(&t);
	init_rocket(&rocket);
	read_file_level(level,&hard,&nb_enemies);
	init_enemies(&enemies,nb_enemies,level);
	init_big_enemy(&bigEnemy,level);
	
	while(key_sym != MLV_KEYBOARD_q && rocket.lifePoints > 0 && level <= 10 && bigEnemy.lifePoints > 0){
		
    	pause_game(&key_sym);
		if( clock_gettime(CLOCK_REALTIME, &start) == -1 ) {
      		perror( "clock gettime" );
      		exit( EXIT_FAILURE );
    	}

		event = MLV_get_event(&key_sym, NULL, NULL,NULL, NULL,NULL, NULL, NULL,NULL);
		
		detect_move(key_sym,&x,&y,rocket.speed);
		
		if (event == MLV_KEY || MLV_get_keyboard_state(key_sym) == MLV_PRESSED ){
			if (key_sym == MLV_KEYBOARD_x && MLV_get_keyboard_state(key_sym) == MLV_RELEASED ){	
				add_shoot(&listP,rocket.pos.x+15,rocket.pos.y,0,10);					
			}
		}					
		if (!(rand()%hard) && level%10 != 0)	
			add_shoot_enemy(enemies,&listE,rocket.pos.x,rocket.pos.y);	

		if (!(rand()%hard) && level%10 == 0){
			add_shoot_bigenemy(bigEnemy,&listE,rocket.pos);
		}
		if (level%10 == 0 && bigEnemy.lifePoints <= 0){
			level ++ ;
		}


	    move_rocket(&rocket, x, y);
		move_enemies(&enemies);
		
		Move_shoot_player(&listP);
		Move_shoot_enemy(&listE);
		
	
		
		verify_all_collision(&listP,&listE,&enemies,&rocket,&nb_enemies,&bigEnemy,&level,&lifePoint,fellower);

		if (nb_enemies <= 0 && level%10 == 9){
			level ++ ;
			init_big_enemy(&bigEnemy,level);
			add_shoot(&fellower,bigEnemy.pos.x,bigEnemy.pos.y,0,0);
		}
		if (nb_enemies <= 0 && level < 9){
			nb_enemies = 10 ;
			level ++ ;
			read_file_level(level,&hard,&nb_enemies);
			init_enemies(&enemies,nb_enemies,level);
		}
		
		remove_shoot_out(&listP);
		remove_shoot_out(&listE);
	    

		draw_lifes(rocket.lifePoints,imageLifes);
		draw_scores(rocket.score);
		draw_level(level);
		draw_shoot_enemy(listE);
		draw_stars(&t);
		draw_shoot(listP);
		draw_life(&lifePoint,imageLifes);
		draw_rocket(rocket.pos.x,rocket.pos.y,imageRocket);
		draw_enemies(&enemies,nb_enemies,imageEnemy);		

	    if (level % 10 == 0){
			if (bigEnemy.lifePoints <= 0)
				level ++ ;
			
			Move_Shoot_fellower(fellower,bigEnemy.pos.x,bigEnemy.pos.y,rocket.pos.x,rocket.pos.y,&fellowerLife);
			move_big_enemy(&bigEnemy);
		    draw_big_enemy(bigEnemy,imageEnemy2);
			draw_shoot_fellower(fellower);

		}

		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
    		perror( "clock gettime" );
    		exit( EXIT_FAILURE );
    	}

   		accum = ( stop.tv_sec - start.tv_sec )+ ( stop.tv_nsec - start.tv_nsec )/ BILLION;

		MLV_actualise_window();
		if( accum < (1.0/48.0)){
			MLV_wait_milliseconds((int)(((1.0/48.0 )-accum)*1000));
		}

		MLV_clear_window(MLV_COLOR_BLACK);
		
	} 
	if (scores[9] < rocket.score){
		scores[9] =  rocket.score ;
		write_file_scores(scores);
	}
	if (bigEnemy.lifePoints <= 0){
	    win_window();
	}
	if (rocket.lifePoints <= 0){
		lose_window();
	}

	MLV_flush_event_queue();
	free_enemies(enemies);
	MLV_free_image(imageRocket);
	MLV_free_image(imageEnemy);
	MLV_free_image(imageLifes);
	MLV_free_image(imageEnemy2);
	MLV_free_window(); 		

	return 0;
}
