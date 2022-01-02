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
//#include "collision.h"

int main(int argc, char *argv[])
{
	sprite_t kart, quiche3, quiche5, ennemi, quiche;
	sprite_t ennemi2;
	sprite_t ennemi3;
	sprite_t ennemi4;
	player_t player;
	chrono_t globaltime;

	//val random pour le time limit pour l'instant
	chrono_t tlimit;
	tlimit.min = 2;
	tlimit.sec = 30;

	player.score = 0;
	
	//playerReset(&player);
	timeReset(&globaltime);

	 // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	SDL_Window* fenetre;
	SDL_Renderer* ecran;
	
	SDL_Rect dstrect; //camera
	SDL_Rect camera2; //camera

	init(&ecran, &fenetre, &camera2, &dstrect, kart, &ennemi, &player, &ennemi2, &ennemi3, &ennemi4);


	SDL_Texture* quiche4 = charger_image("map.png", ecran);
	SDL_Texture* vehicle = charger_image("kart.png", ecran);
	SDL_Texture* quiche2 = charger_image("quiche.png", ecran);
	SDL_Texture* ennemi_tex = charger_image("square.png", ecran);
	SDL_Texture* quiche_tex = charger_image("square.png", ecran);
	TTF_Font* font = load_font("arial.ttf", 14); 

	

	init_sprite(&kart, 2649, 649, 100, 256); //0, 0 est le coin sup gauche, (kart.x+64) - 1080 / 2;
	init_sprite(&ennemi, 500, 700, 64, 64); //ca fonctionne correctement quand on met les memes valeurs que le kart, mais pas sans
	init_sprite(&quiche, 2500, 720, 64, 64);
		init_sprite(&ennemi, 500, 900, 64, 64);
	init_sprite(&ennemi2, 2500, 900, 64, 64);
	init_sprite(&ennemi3, 1500, 1000, 64, 64);
	init_sprite(&ennemi4, 1500, 500, 64, 64);
	//init_sprite(&ennemi, WINDOW_WIDTH/2-256, WINDOW_HEIGHT/4, 64, 64);

	sprite_t r;
	init_sprite(&r, 1010, 720, 1500, 450);

	sprite_t finish;
	init_sprite(&finish, 2600, 750, 358, 1);

		

// Boucle principale
	while(!terminer)
	{
		SDL_PollEvent(&evenements);
		movement(&evenements, terminer, &kart, &camera2, &r);
		update_states(&player, &kart, &ennemi, &quiche, &r, &finish, &ennemi2, &ennemi3, &ennemi4);
		//printf("score: %d", player.score);
		switch(evenements.type){
			case SDL_QUIT:
				terminer = true;
                 break;
        }

		int x = 0; //clock
		globaltime.sec = SDL_GetTicks()/1000;

		counterT(&globaltime);
		/*
		if(arriver){
			player.timeMap[i].sec = globaltime->sec;
			counterP(player, x);
			x++;
		}*/

		renderer(ecran, font, quiche4, &camera2, &dstrect, vehicle, &kart, ennemi_tex, &ennemi, quiche_tex, &quiche, &player, &ennemi2, &ennemi3, &ennemi4);
		
	}

	// Boucle principale

	// Libérer de la mémoire
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(ecran);
	//Quitter SDL ...
	// Quitter SDL
	SDL_DestroyWindow(fenetre);

	SDL_Quit();
	return 0;
}
