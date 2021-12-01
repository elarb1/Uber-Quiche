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
#include "camera.h"
#include "Timer.h"
#include "graphics.h"


#define LEVEL_HEIGHT 3000
#define LEVEL_WIDTH 4000


#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640



int main(int argc, char *argv[])
{
	sprite_t kart; 
	sprite_t quiche3;
	sprite_t quiche5;

	player_t player;
	camera_t camera;
	timer_t chrono;

	int Uneseconde;

	//player = playerReset(player);
	//timeReset(&chrono);

	SDL_Window* fenetre; // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	// Créer la fenêtre
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_RESIZABLE); //set variables to be modifiable
	if(fenetre == NULL){ // En cas d’erreur
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	SDL_Renderer* ecran;

	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* quiche = charger_image("background.png", ecran);
	SDL_Texture* quiche4 = charger_image("bg2.png", ecran);

	init_sprite(&kart, 1080/2, 1080/2, 64, 64); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	
	SDL_Texture* vehicle = charger_image("kart.png", ecran);

	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);


	//dstrect controle le rectangle d'affichage


	SDL_Rect dstrect; //camera
		dstrect.x = 0;
		dstrect.y = 0;
		dstrect.h = 960;
		dstrect.w = 1280;

	SDL_Rect camera2; //camera
		camera2.x = 640/2-64;
		camera2.y = 480/2-64;
		camera2.h = 480;
		camera2.w = 640;

// Boucle principale
	while(!terminer)
	{
		
		//control le renderer
		//https://wiki.libsdl.org/SDL_RenderCopy
		//les deux dernieres controlent ce qui est envoyee, la premiere la source de l'image sur un tilset, le deuxieme est l'emplacement sur l'ecran
		//le premier param sert a appliquer le renderer, le deuxieme c'est le fond a appliquer
		
		//SDL_RenderCopyEx(ecran, vehicle, NULL, &dstrect, 0, 0, SDL_FLIP_NONE);
		//apply_img(ecran, quiche4, &quiche3);
		
		//SDL_RenderDrawRect(ecran, &dstrect);

		//apply_img(ecran, quiche4, &quiche5);
		SDL_PollEvent(&evenements);

		//Uneseconde = completeSeconde(ms, chrono); //ms est le temps du refresh

		/*if(Unseconde){
			counter(&chrono);
			Unseconde = 0;
		}*/
		
		/*Pour quand on aura une arriver
		int n = 0;

		if(arriver){
			player.chronoLap[n] = saveChrono(chrono);
			n++;
		}
		*/

		switch(evenements.type){
	
			case SDL_QUIT:
				terminer = true; break;
			case SDL_KEYDOWN:
			switch(evenements.key.keysym.sym) //temporairement on empeche le kart de sortir avant la mise en place de la camera
			{
				case SDLK_ESCAPE:
				case SDLK_q:
					terminer = true; break;
				case SDLK_LEFT:
					 //remodifier pour correspondre au nouvelles variables de la fenetre
						kart.x -= 1; 
						//quiche3.x -= 1;
						player.vie += 1;
						player.score += 1;
						//printf("%d playerx", kart.x);
						
						if(kart.x <0 ){
							kart.x += 1;
						}
						//preuve de concept de deplacement de "camera"
						
							
						
						//printf("%d \n", player.vie);
					
					break;
				case SDLK_RIGHT:
					
						 
						//quiche3.x += 1;
						//dstrect.x += 1;
						//dstrect.y += 1;
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart.x);
						printf("%d camx \n", camera2.x);
						
							kart.x += 1;
					
						
							

						
					
					break;
				case SDLK_UP:
					if(kart.y-1 > 0){
						kart.y -= 2; 
						quiche3.y -= 1;
						dstrect.y -= 1;
					}
					break;
				case SDLK_DOWN:
					if(kart.y+1 < LEVEL_WIDTH-64){
						kart.y += 2; 
						quiche3.y += 1;
					}
					break;
			}
		}
		if( ( kart.x < 0 ) || ( kart.x + 64 > 4000-64-32 ) )
    {
        //move back
        kart.x -= 1;
    }
		
		camera2.x = (kart.x-64/2) - 1080 / 2;

		if(camera2.x < 0){
			camera2.x = 0;
		}

		if( camera2.x > 4000 - camera2.w )
    {
        camera2.x = 4000 - camera2.w;
    }


	
		//camera2.y = (kart.y+64) - 1024 / 2;


		
		//refreshCycle(ecran, quiche4, dstrect, vehicle, camera2.x);

		 SDL_RenderClear(ecran);


	SDL_RenderCopyEx(ecran, quiche4,&camera2, &dstrect, 0, 0, SDL_FLIP_NONE);
	apply_img(ecran, vehicle, &kart, camera2.x);
	SDL_RenderPresent(ecran);
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
