#include "functions_main.h"
#include "structures.h"

int movex = 2649; 
int movey = 649;

int hasWon(player_t* player, chrono_t tlimit){
	int result = 0;

	if(player->lap == LAPS){
		if(player->score == 4){
			player->win = 1;
			result = 1;
		}else if(player->score < 4){
			player->win = 0;
			result = 2;
		}else if((player->chronoLap[LAPS].min > tlimit.min) || (player->chronoLap[LAPS].min == tlimit.min && player->chronoLap[LAPS].sec > tlimit.sec)){
			player->win = 0;
			result = 3;
		}
	}

	return result;
}

void lap(sprite_t* kart, sprite_t* finish, player_t* player){
	if(collision2(kart, finish) == 1 && (player->deltaTime > 100)){
		player->lap +=1;
		player->deltaTime = 0;
	}
}

void ennemi_movement_ypos(sprite_t* ennemi, sprite_t* r){
	printf("%d \n", ennemi->vel);
	if(ennemi->y < 270){
		ennemi->vel = -1;
	}
	if(collision2(ennemi, r) == 1){
		printf("hi");
		ennemi->vel = 1;
	}
	if(ennemi->vel >0){
		ennemi->y -=1;
	}else{
		ennemi->y +=1;
	}
}

void ennemi_movement_yneg(sprite_t* ennemi, sprite_t* r){
	if(ennemi->y > 1500){
		ennemi->vel = 1;
	}
	if(collision2(ennemi, r) == 1){
		ennemi->vel = -1;
	}

	if(ennemi->vel >0){
		ennemi->y -=1;
	}else{
		ennemi->y +=1;
	}
}

void ennemi_movement_xright(sprite_t* ennemi, sprite_t* r){ //le rendering de la map est se distorte legerement et fait que la perspective de la vue est changee
	printf("%d \n", ennemi->x);
	printf("%d\n", ennemi->vel);
	if(ennemi->x > 3000){
		ennemi->vel = 1;
	}
	if(collision2(ennemi, r) == 1){
		ennemi->vel = -1;
	}

	if(ennemi->vel >0){
		ennemi->x -=1;
	}else{
		ennemi->x +=1;
	}
}

void ennemi_movement_xleft(sprite_t* ennemi, sprite_t* r){ //le rendering de la map est se distorte legerement et fait que la perspective de la vue est changee
	printf("%d \n", ennemi->x);
	printf("%d\n", ennemi->vel);
	if(ennemi->x < 500){
		ennemi->vel = -1;
	}
	if(collision2(ennemi, r) == 1){
		ennemi->vel = +1;
	}

	if(ennemi->vel >0){
		ennemi->x -=1;
	}else{
		ennemi->x +=1;
	}
}

void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, sprite_t* r, sprite_t* finish){
	
			int coll = collision(kart, ennemi);
		int coll2 = collision(kart, quiche);
		int coll3 = collision_test(kart, r);
		if(coll == 1){
			player->score -=1;
			printf("score: %d \n", player->score);
			//printf("yes: %d", collision(&kart, &ennemi));
		}
		if(coll2 == 1){
			player->score +=1;
			printf("score: %d \n", player->score);
			//printf("yes: %d", collision(&kart, &ennemi));
		}
		if(coll3 == 1){
			printf("yes");
			//printf("yes: %d", collision(&kart, &ennemi));
		}
		/*int time = SDL_GetTicks();
		player->deltaTime = time - player->lastTime;
		player->lastTime = SDL_GetTicks();*/
		ennemi_movement_xleft(ennemi, r);
		lap(kart, finish, player);
}

int collision(sprite_t* a, sprite_t* b){
  if( !(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) ||(b->y + b->h) < a->y)){
  	b->x=0;
  	b->y=0;
  	b->w=0;
  	b->h=0;
	return 1;
  }
  return 0;
}

int collision2(sprite_t* a, sprite_t* b){
  if( !(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) ||(b->y + b->h) < a->y)){
	return 1;
  }
  return 0;
}

int collision_test(sprite_t* a, sprite_t* b){
  if((a->x - a->w) == (b->x + b->w)){
	return 1;
  }
  return 0;
}

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height){
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

void apply_text(SDL_Renderer* renderer, int x, int y, int w, int h, const char* text, TTF_Font* font);

void renderer(SDL_Renderer* ecran, TTF_Font* font, SDL_Texture* quiche4, SDL_Rect* camera2, SDL_Rect* dstrect, SDL_Texture* vehicle, sprite_t* kart, SDL_Texture* ennemi_tex, sprite_t* ennemi, SDL_Texture* quiche_tex, sprite_t* quiche, player_t* player){
	SDL_RenderClear(ecran);
	SDL_RenderCopyEx(ecran, quiche4,camera2, dstrect, 0, 0, SDL_FLIP_NONE);	
	apply_img(ecran, ennemi_tex, ennemi, camera2->x-64, camera2->y-64);
	//apply_img(ecran, quiche_tex, quiche, camera2->x-64, camera2->y-64);
	apply_img(ecran, vehicle, kart, camera2->x, camera2->y);
	player->deltaTime +=1;
	//systeme de print a l'ecran (texte)
	char score[20];
	sprintf(score, "score : %d", player->score);
	apply_text(ecran, 0, 0, 100, 100, score, font);
	//systeme de print au dessus
	SDL_RenderPresent(ecran);
}

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t kart, sprite_t* ennemi, player_t* player){ //catch error
	init_sdl(fenetre, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_ttf();

	//renderer = SDL_CreateRenderer(&fenetre, -1, SDL_RENDERER_ACCELERATED);

		dstrect->x = 0;
		dstrect->y = 0;
		dstrect->h = WINDOW_HEIGHT;
		dstrect->w = WINDOW_WIDTH;

		camera2->x = 0;
		camera2->y = 0;
		camera2->h = 480;
		camera2->w = 640;

	ennemi->vel = 1;

	//init_sprite(ennemi, 64, 64, 64, 64);

}

void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2, sprite_t* r){
   
       switch(event->type){
	
			case SDL_QUIT:
				terminer = true; break;

			case SDL_KEYDOWN:
				switch(event->key.keysym.sym) //temporairement on empeche le kart de sortir avant la mise en place de la camera
				{
					case SDLK_ESCAPE:

					case SDLK_q:
						terminer = true; break;

					case SDLK_LEFT:
						//remodifier pour correspondre au nouvelles variables de la fenetre
						movex -= 10; 

						//preuve de concept de deplacement de "camera"
						if((kart->x < 600) || (kart->x-100 > 4000)) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex += 10;
   						}
						if(collision2(kart, r) == 1){
							movex +=50;
						}
						//printf("%d \n", player.vie);
					
					break;

					case SDLK_RIGHT:
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart->x);
						printf("%d camx \n", camera2->x);
						
						movex += 10;
							
						if( ( kart->x < 0 ) || ( kart->x-100 > 2750 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex -= 10;
   						}
						if(collision2(kart, r) == 1){
							movex -=50;
						}
					break;

					case SDLK_UP:
						movey -= 10;

						if( ( kart->y < 300 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movey += 10;
   						} 
						if(collision2(kart, r) == 1){
							movey +=50;
						}
					break;

				case SDLK_DOWN:
					movey += 10;
				
					if( ( kart->y < 0 ) || ( kart->y-64 > 1300 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   					{
       					movey -= 10;
   					} 
					if(collision2(kart, r) == 1){
						movey -=50;
					}
				break;
			}
		}

		SDL_Delay(10);
        kart->x = movex;
		kart->y = movey;

		camera2->x = (kart->x+128/2) - WINDOW_WIDTH / 2;//(kart.x+64/2) - 1280 / 2;
		camera2->y = (kart->y+150/2) - WINDOW_HEIGHT / 2; //j'ai pas la largeur du kart
}
