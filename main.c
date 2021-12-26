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
#include "functions_main.h"

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
