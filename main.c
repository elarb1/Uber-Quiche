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
#include "chrono.h"


#define LEVEL_HEIGHT 3000
#define LEVEL_WIDTH 4000
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define MOVE_SPEED 1


int main(int argc, char *argv[])
{
	sprite_t kart; 
	sprite_t quiche3;
	sprite_t quiche5;

	player_t player;
	camera_t camera;
	chrono_t chrono;

	int Uneseconde = 0;

	playerReset(&player);
	timeReset(&chrono);

	SDL_Window* fenetre; // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	// Créer la fenêtre
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE); //set variables to be modifiable
	if(fenetre == NULL){ // En cas d’erreur
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	SDL_Renderer* ecran;

	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* quiche = charger_image("background.png", ecran);
	SDL_Texture* quiche4 = charger_image("bg2.png", ecran);

	init_sprite(&kart, WINDOW_WIDTH/2-256, WINDOW_HEIGHT/4, 64, 64); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	
	SDL_Texture* vehicle = charger_image("kart.png", ecran);

	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);


	//dstrect controle le rectangle d'affichage


	SDL_Rect dstrect; //camera
		dstrect.x = 0;
		dstrect.y = 0;
		dstrect.h = WINDOW_HEIGHT;
		dstrect.w = WINDOW_WIDTH;

	SDL_Rect camera2; //camera
		camera2.x = 0;
		camera2.y = 0;
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

		//Uneseconde = completeSeconde(ms, chrono); //ms, le temps du refresh
/*
		if(Uneseconde){
			counter(&chrono);
			Uneseconde = 0;
		}
		*/
		/*Pour quand on aura une arriver
		int n = 0;

		if(arriver){
			player.chronoLap[n] = chrono;
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

						//preuve de concept de deplacement de "camera"
						
							
						
						//printf("%d \n", player.vie);
					
					break;
				case SDLK_RIGHT:
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart.y);
						printf("%d camx \n", camera2.y);
						
							kart.x += 1;
							
					
								if( ( kart.x < 0 ) || ( kart.x-100 > 4000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   								 {
       								 kart.x -= 1;
   								 }
									

						
					
					break;
				case SDLK_UP:

						kart.y -= 1; 

					break;
				case SDLK_DOWN:

						kart.y += 1;
							if( ( kart.y < 0 ) || ( kart.y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   								 {
       								 kart.y -= 1;
   								 } 
	
					break;
			}
		}

		camera2.x = (kart.x+128/2) - WINDOW_WIDTH / 2;//(kart.x+64/2) - 1280 / 2;
		camera2.y = (kart.y+150/2) - WINDOW_HEIGHT / 2; //j'ai pas la largeur du kart
		
		
		SDL_RenderClear(ecran);

		
		SDL_RenderCopyEx(ecran, quiche4,&camera2, &dstrect, 0, 0, SDL_FLIP_NONE);
		apply_img(ecran, vehicle, &kart, camera2.x, camera2.y);
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
