//la map fait 1024x768
//Taille de la map en 3 fois si ca te chante
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

#define HEIGHT 1024
#define WIDTH 1024



int main(int argc, char *argv[])
{
	sprite_t kart; 
	sprite_t quiche3;
	sprite_t quiche5;

	player_t player;
	camera_t camera;

	player.vie = 0;
	player.score = 0;

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
	SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_WINDOW_RESIZABLE); //set variables to be modifiable
	if(fenetre == NULL){ // En cas d’erreur
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	SDL_Renderer* ecran;

	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* quiche = charger_image("background.png", ecran);
	SDL_Texture* quiche4 = charger_image("map.png", ecran);

	init_sprite(&kart, 20, 20, 64, 64); //0, 0 est le coin sup gauche
	
	SDL_Texture* vehicle = charger_image("kart.png", ecran);

	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);

	init_sprite(&quiche3, 50, 50, 64, 64);
	init_sprite(&quiche5, 1000, 1000, 64, 64);
	camera.x = 0;
	camera.y = 0;

	SDL_Rect dstrect;
			dstrect.x = camera.x;
		dstrect.y = camera.y;
		dstrect.h = 240;
		dstrect.w = 240;
// Boucle principale
	while(!terminer)
	{
		SDL_RenderClear(ecran);
		

	
		SDL_RenderCopy(ecran, quiche, NULL, &dstrect);
				apply_img(ecran, quiche4, &quiche3);
		apply_img(ecran, vehicle, &kart);

		apply_img(ecran, quiche4, &quiche5);
		SDL_PollEvent( &evenements );
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
					if(kart.x-1 >0){ //remodifier pour correspondre au nouvelles variables de la fenetre
						kart.x -= 2; 
						quiche3.x -= 1;
						player.vie += 1;
						player.score += 1;
						dstrect.x -= 1;
						;
						printf("%d \n", player.vie);
					}
					break;
				case SDLK_RIGHT:
					if(kart.x+1 < HEIGHT-64){
						kart.x += 2; 
						quiche3.x += 1;
						dstrect.x += 1;
		dstrect.y += 1;
					}
					break;
				case SDLK_UP:
					if(kart.y-1 > 0){
						kart.y -= 2; 
						quiche3.y -= 1;
						dstrect.y -= 1;
					}
					break;
				case SDLK_DOWN:
					if(kart.y+1 < WIDTH-64){
						kart.y += 2; 
						quiche3.y += 1;
					}
					break;
			}
		}
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
