//la map fait 1024x1024
//retructurer en differents


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "structures.h"

#define H 1024
#define V 1024


int main(int argc, char *argv[])
{
	sprite_t kart; 
	sprite_t quiche3;

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
	SDL_WINDOWPOS_CENTERED, H, V, SDL_WINDOW_RESIZABLE); //set variables to be modifiable
	if(fenetre == NULL){ // En cas d’erreur
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	SDL_Renderer* ecran;

	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* quiche = charger_image("quiche.jpg", ecran);

	init_sprite(&kart, 20, 20, 64, 64); //0, 0 est le coin sup gauche
	
	SDL_Texture* vehicle = charger_image("ferrari4.png", ecran);

	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);

	init_sprite(&quiche3, 50, 50, 64, 64);
	

// Boucle principale
	while(!terminer)
	{
		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, quiche, NULL, NULL);
		apply_img(ecran, vehicle, &kart);
		apply_img(ecran, quiche2, &quiche3);
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
						kart.x -= 1; 
					}
					break;
				case SDLK_RIGHT:
					if(kart.x+1 < H-64){
						kart.x += 1; 
					}
					break;
				case SDLK_UP:
					if(kart.y-1 > 0){
						kart.y -= 1; 
					}
					break;
				case SDLK_DOWN:
					if(kart.y+1 < V-64){
						kart.y += 1; 
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