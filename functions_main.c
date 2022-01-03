#include "functions_main.h"
#include "fonctions_SDL.h"
#include "structures.h"

int movex = 2649; 
int movey = 649;

int hasWon(player_t* player, chrono_t tlimit){
	int result = 0;

	if(player->lap == LAPS){
		if(player->score == 1){
			player->win = 1;
			result = 1;
		}else if(player->score < 4){
			player->win = 2;
			result = 2;
		}else if((player->chronoLap[LAPS].min > tlimit.min) || (player->chronoLap[LAPS].min == tlimit.min && player->chronoLap[LAPS].sec > tlimit.sec)){
			player->win = 3;
			result = 3;
		}
	}

	return result;
}

void lap(sprite_t* kart, sprite_t* finish, player_t* player){
	if(collision2(kart, finish) == 1 && (player->deltaTime > 400)){
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

void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, sprite_t* r, sprite_t* finish, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, chrono_t tlimit, world_t* world){
	
			int coll = collision(kart, ennemi);
		int coll2 = collision(kart, ennemi2);
		int coll3 = collision(kart, ennemi3);
		int coll4 = collision(kart, ennemi4);
		int coll5 = collision(kart, quiche);
		if(coll == 1 || coll2 == 1|| coll3 == 1|| coll4 == 1){
			player->score -=1;
		}
		if(coll5 == 1){
			player->score +=1;
		}
		ennemi_movement_xleft(ennemi, r);
		ennemi_movement_xright(ennemi2, r);
		ennemi_movement_yneg(ennemi3, r);
		ennemi_movement_ypos(ennemi4, r);
		lap(kart, finish, player);
		hasWon(player, tlimit);
		printf("win? %d\n", player->win);
		printf("lap? %d\n", player->lap);

		if(player->win != 0){
			score_write(player);
			world->status = 2;
		}

}

int collision(sprite_t* a, sprite_t* b){
  if( !(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) ||(b->y + b->h) < a->y)){
  	b->x=0;
  	b->y=0;
  	b->w=0;
  	b->h=0;
	   b->isVisible = 1;
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


void renderer(SDL_Renderer* ecran, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, world_t* world, chrono_t tlimit, SDL_Rect* kart_coords){
	SDL_RenderClear(ecran);
	SDL_RenderCopyEx(ecran, world->bg,camera2, dstrect, 0, 0, SDL_FLIP_NONE);
	if(ennemi->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi, camera2->x, camera2->y);
	}	
	if(ennemi2->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi2, camera2->x, camera2->y);
	}	
	if(ennemi3->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi3, camera2->x, camera2->y);
	}	
	if(ennemi4->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi4, camera2->x, camera2->y);
	}	
	apply_img(ecran, world->quiche_tex, quiche, camera2->x, camera2->y);
	apply_img_blits(ecran, kart_coords, world->player_tex, kart, camera2->x, camera2->y);
	
	player->deltaTime +=1;
	//systeme de print a l'ecran (texte)
	char score[20];
	sprintf(score, "score : %d", player->score);
	apply_text(ecran, 0, 0, 100, 100, score, world->font);
	if(player->win == 1){
		apply_text(ecran, 100, 100, 100, 100, "victoire", world->font);
	}
	if(player->win == 2 || player->win == 3){
		apply_text(ecran, 100, 100, 100, 100, "no", world->font);
	}
	//systeme de print au dessus
	SDL_RenderPresent(ecran);
	
}

void init_textures(world_t* world, SDL_Renderer* ecran){
	world->bg = charger_image("map.png", ecran);
	world->player_tex = charger_image("kart.png", ecran);
	world->ennemi_tex = charger_image("backhoff.png", ecran);
	world->quiche_tex = charger_image("quiche.png", ecran);
	world->font = load_font("arial.ttf", 14); 
}

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, sprite_t* quiche, SDL_Rect* kart_coords){
	init_sdl(fenetre, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_ttf();


	init_sprite(kart, 2649, 649, 64, 64); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	
	init_sprite(ennemi, 500, 700, 64, 64);
	init_sprite(ennemi, 500, 900, 64, 64);
	init_sprite(ennemi2, 2500, 900, 64, 64);
	init_sprite(ennemi3, 1500, 1000, 64, 64);
	init_sprite(ennemi4, 1500, 500, 64, 64);

	init_sprite(quiche, 700, 1350, 64, 64);

		dstrect->x = 0;
		dstrect->y = 0;
		dstrect->h = WINDOW_HEIGHT;
		dstrect->w = WINDOW_WIDTH;

		camera2->x = 0;
		camera2->y = 0;
		camera2->h = 480;
		camera2->w = 640;

		kart_coords->x = 2*kart->direction * 64;
		kart_coords->y = 0;
		kart_coords->w = 64;
		kart_coords->h = 64;

	ennemi->vel = 1;
	ennemi2->vel = 1;
	ennemi3->vel = 1;
	ennemi4->vel = 1;

	player->score = 0;
	player->win = 0;

	kart->direction = 0;
}

void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2, sprite_t* r, SDL_Rect* kart_coords){
   
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
						movex -= MOVE_SPEED; 
						kart->direction = 1;
						//preuve de concept de deplacement de "camera"
						if((kart->x < 600) || (kart->x-100 > 4000)) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex += MOVE_SPEED;
   						}
						if(collision2(kart, r) == 1){
							movex +=MOVE_SPEED * 5;
						}
					
					break;

					case SDLK_RIGHT:
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart->x);
						printf("%d camx \n", camera2->x);
						
						movex += MOVE_SPEED;
							kart->direction = 3;
						if( ( kart->x < 0 ) || ( kart->x-64 > 2900 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex -= MOVE_SPEED;
   						}
						if(collision2(kart, r) == 1){
							movex -=MOVE_SPEED * 5;
						}
					break;

					case SDLK_UP:
						movey -= MOVE_SPEED;
						kart->direction = 0;
						if( ( kart->y < 350 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movey += MOVE_SPEED;
   						} 
						if(collision2(kart, r) == 1){
							movey +=MOVE_SPEED * 5;
						}
					break;

				case SDLK_DOWN:
					movey += MOVE_SPEED;
					kart->direction = 2;
					if( ( kart->y < 0 ) || ( kart->y-64 > 1450 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   					{
       					movey -= MOVE_SPEED;
   					} 
					if(collision2(kart, r) == 1){
						movey -=MOVE_SPEED * 5;
					}
				break;
			}
		}

		SDL_Delay(10);
        kart->x = movex;
		kart->y = movey;

		camera2->x = (kart->x) - WINDOW_WIDTH / 2;//(kart.x+64/2) - 1280 / 2;
		camera2->y = (kart->y) - WINDOW_HEIGHT / 2; //j'ai pas la largeur du kart
}
