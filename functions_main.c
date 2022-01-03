#include "functions_main.h"
#include "fonctions_SDL.h"
#include "structures.h"
#include "player.h"

int movex = 2649; 
int movey = 649;

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

void renderer(SDL_Renderer* ecran, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, world_t* world){
	SDL_RenderClear(ecran);
		SDL_RenderCopyEx(ecran, world->bg,camera2, dstrect, 0, 0, SDL_FLIP_NONE);
	if(ennemi->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi, camera2->x-64, camera2->y-64);
	}	
	if(ennemi2->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi2, camera2->x-64, camera2->y-64);
	}	
	if(ennemi3->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi3, camera2->x-64, camera2->y-64);
	}	
	if(ennemi4->isVisible != 1){
		apply_img(ecran, world->ennemi_tex, ennemi4, camera2->x-64, camera2->y-64);
	}	
	apply_img(ecran, world->quiche_tex, quiche, camera2->x-64, camera2->y-64);
	apply_img(ecran, world->player_tex, kart, camera2->x, camera2->y);
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
	world->ennemi_tex = charger_image("square.png", ecran);
	world->quiche_tex = charger_image("square.png", ecran);
	world->font = load_font("arial.ttf", 14); 
}

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, sprite_t* quiche){
	init_sdl(fenetre, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_ttf();


	init_sprite(kart, 2649, 649, 100, 256); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	
	init_sprite(ennemi, 500, 700, 64, 64);
	init_sprite(ennemi, 500, 900, 64, 64);
	init_sprite(ennemi2, 2500, 900, 64, 64);
	init_sprite(ennemi3, 1500, 1000, 64, 64);
	init_sprite(ennemi4, 1500, 500, 64, 64);

	init_sprite(quiche, 2500, 720, 64, 64);

		dstrect->x = 0;
		dstrect->y = 0;
		dstrect->h = WINDOW_HEIGHT;
		dstrect->w = WINDOW_WIDTH;

		camera2->x = 0;
		camera2->y = 0;
		camera2->h = 480;
		camera2->w = 640;

	ennemi->vel = 1;
	ennemi2->vel = 1;
	ennemi3->vel = 1;
	ennemi4->vel = 1;

	player->score = 0;
	player->win = 0;
}

void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, sprite_t* r, sprite_t* finish, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, chrono_t tlimit){
    int coll = collision(kart, ennemi), coll2 = collision(kart, ennemi2);
    int coll3 = collision(kart, ennemi3), coll4 = collision(kart, ennemi4);
    int coll5 = collision(kart, quiche);

    if(coll == 1 || coll2 == 1 || coll3 == 1 || coll4 == 1){
        player->score--;
    }
        
    if(coll5 == 1){
        player->score++;
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
    }
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
						movex -= MOVE_SPEED; 

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
							
						if( ( kart->x < 0 ) || ( kart->x-100 > 2750 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex -= MOVE_SPEED;
   						}
						if(collision2(kart, r) == 1){
							movex -=MOVE_SPEED * 5;
						}
					break;

					case SDLK_UP:
						movey -= MOVE_SPEED;

						if( ( kart->y < 300 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movey += MOVE_SPEED;
   						} 
						if(collision2(kart, r) == 1){
							movey +=MOVE_SPEED * 5;
						}
					break;

				case SDLK_DOWN:
					movey += MOVE_SPEED;
				
					if( ( kart->y < 0 ) || ( kart->y-64 > 1300 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
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

		camera2->x = (kart->x+128/2) - WINDOW_WIDTH / 2;//(kart.x+64/2) - 1280 / 2;
		camera2->y = (kart->y+150/2) - WINDOW_HEIGHT / 2; //j'ai pas la largeur du kart
}
