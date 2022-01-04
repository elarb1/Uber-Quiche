//la map fait 1024x768
//Taille de la map en 3 fois si ca te chante wtf
//retructurer en differents
//reecrire le code

/*
c'est devenu un sokoban xD
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fonctions_SDL.h"
#include "structures.h"
#include "chrono.h"
#include "functions_main.h"
#include "score.h"
#include "end_menu_renderers.h"
//#include "collision.h"

int main(int argc, char *argv[])
{
	world_t world;
	sprite_t kart, ennemi, quiche;
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
	world.status = 0;
	
	//playerReset(&player);
	timeReset(&globaltime);

	 // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	SDL_Window* fenetre;
	SDL_Renderer* ecran;
	
	SDL_Rect dstrect; //camera
	SDL_Rect camera2; //camera
	SDL_Rect kart_coord;

	init(&ecran, &fenetre, &camera2, &dstrect, &kart, &ennemi, &player, &ennemi2, &ennemi3, &ennemi4, &quiche, &kart_coord);
	init_textures(&world, ecran);


//	SDL_Texture* quiche4 = charger_image("map.png", ecran);
	

	


	sprite_t r;
	init_sprite(&r, 1010, 720, 1500, 450);

	sprite_t finish;
	init_sprite(&finish, 2600, 750, 358, 1);
	while(world.status==0){
		SDL_PollEvent(&evenements);
		switch(evenements.type){
			case SDL_QUIT:
				world.status = 3;
                break;
			case SDL_KEYDOWN:
				switch(evenements.key.keysym.sym) //temporairement on empeche le kart de sortir avant la mise en place de la camera
				{
					case SDLK_SPACE:
						world.status = 1;
						break;
        	}
		}
		menu_renderer(ecran, world);
	}
		

// Game loop
	while(world.status == 1)
	{
		SDL_PollEvent(&evenements);
		movement(&evenements, terminer, &kart, &camera2, &r, &kart_coord);
		update_states(&player, &kart, &ennemi, &quiche, &r, &finish, &ennemi2, &ennemi3, &ennemi4, tlimit, &world);
		switch(evenements.type){
			case SDL_QUIT:
				world.status = 3;
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

		renderer(ecran, &camera2, &dstrect, &kart, &ennemi, &quiche, &player, &ennemi2, &ennemi3, &ennemi4, &world, tlimit, &kart_coord);
		
	}

	while(world.status==2){
		SDL_PollEvent(&evenements);
		switch(evenements.type){
			case SDL_QUIT:
				world.status = 3;
                break;
		}
		end_renderer(ecran, world);
	}

	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(ecran);
	SDL_DestroyWindow(fenetre);

	SDL_Quit();
	return 0;
}
