//la map fait 1024x768
//Taille de la map en 3 fois si ca te chante wtf
//retructurer en differents
//reecrire le code

/*
Reecrire le code: 
	- Tout le main est rearange dans d'autres fichiers
	- Fichier pour le monde
	- Fichier pour le graphisme
	- Remodifier le makefile en consequence
s

*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fonctions_SDL.h"
#include "structures.h"
#include "chrono.h"


#define LEVEL_HEIGHT 3000
#define LEVEL_WIDTH 4000
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define MOVE_SPEED 1

int movex, movey = 0;

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect);
void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2);
void renderer();

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
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


void renderer(SDL_Renderer* ecran, SDL_Texture* quiche4, SDL_Rect* camera2, SDL_Rect* dstrect, SDL_Texture* vehicle, sprite_t* kart, SDL_Texture* ennemi_tex, sprite_t* ennemi){
	SDL_RenderClear(ecran);

	SDL_RenderCopyEx(ecran, quiche4,camera2, dstrect, 0, 0, SDL_FLIP_NONE);
	apply_img(ecran, ennemi_tex, ennemi, camera2->x, camera2->y);
	apply_img(ecran, vehicle, kart, camera2->x, camera2->y);
	SDL_RenderPresent(ecran);
}

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect){ //catch error
	init_sdl(fenetre, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	//renderer = SDL_CreateRenderer(&fenetre, -1, SDL_RENDERER_ACCELERATED);

		dstrect->x = 0;
		dstrect->y = 0;
		dstrect->h = WINDOW_HEIGHT;
		dstrect->w = WINDOW_WIDTH;

		camera2->x = 0;
		camera2->y = 0;
		camera2->h = 480;
		camera2->w = 640;

	//init_sprite(ennemi, 64, 64, 64, 64);
}

void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2){
   
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
						movex -= 1; 

						//preuve de concept de deplacement de "camera"
						if((kart->x < 0) || (kart->x-100 > 4000)) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex += 1;
   						}
						//printf("%d \n", player.vie);
					
					break;

					case SDLK_RIGHT:
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart->y);
						printf("%d camx \n", camera2->y);
						
						movex += 10;
							
						if( ( kart->x < 0 ) || ( kart->x-100 > 4000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex -= 1;
   						}
					break;

					case SDLK_UP:
						movey -= 1;

						if( ( kart->y < 0 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movey += 1;
   						} 
					break;

				case SDLK_DOWN:
					movey += 1;
				
					if( ( kart->y < 0 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   					{
       					movey -= 1;
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

int main(int argc, char *argv[])
{
	sprite_t kart; 
	sprite_t quiche3;
	sprite_t quiche5;
	sprite_t ennemi;
	player_t player;
	chrono_t gobaltime;

	playerReset(&player);
	timeReset(&gobaltime);

	 // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	SDL_Window* fenetre;
	SDL_Renderer* ecran;
	
	SDL_Rect dstrect; //camera
	SDL_Rect camera2; //camera

	init(&ecran, &fenetre, &camera2, &dstrect);

	SDL_Texture* quiche = charger_image("background.png", ecran);
	SDL_Texture* quiche4 = charger_image("bg2.png", ecran);
	SDL_Texture* vehicle = charger_image("kart.png", ecran);
	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);
	SDL_Texture* ennemi_tex = charger_image("square.png", ecran);

	init_sprite(&kart, WINDOW_WIDTH/2-256, WINDOW_HEIGHT/4, 64, 64); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	init_sprite(&ennemi, WINDOW_WIDTH/2-256, WINDOW_HEIGHT/4, 64, 64);
		

// Boucle principale
	while(!terminer)
	{
		SDL_PollEvent(&evenements);
		movement(&evenements, terminer, &kart, &camera2);
		switch(evenements.type){
			case SDL_QUIT:
				terminer = true;
                 break;
        }

		int x = 0; //clock
		gobaltime.sec = SDL_GetTicks()/1000;

		counterT(&gobaltime);
		/*
		if(arriver){
			player.timeMap[i].sec = globaltime->sec;
			counterP(player, x);
			x++;
		}*/

		renderer(ecran, quiche4, &camera2, &dstrect, vehicle, &kart, ennemi_tex, &ennemi);
		
		
	}

	// Boucle principale

	// Libérer de la mémoire
	IMG_Quit();
	SDL_DestroyRenderer(ecran);
	//Quitter SDL ...
	// Quitter SDL
	SDL_DestroyWindow(fenetre);

	SDL_Quit();
	return 0;
}
