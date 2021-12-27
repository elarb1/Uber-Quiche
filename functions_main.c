#include "functions_main.h"
#include "structures.h"

int movex = 2649; 
int movey = 649;

bool collision(sprite_t* a, sprite_t* b){
  if( !(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) ||(b->y + b->h) < a->y)){
  	b->x=0;
  	b->y=0;
  	b->w=0;
  	b->h=0;
  }
}

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

void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t kart){ //catch error
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
						movex -= 10; 

						//preuve de concept de deplacement de "camera"
						if((kart->x < 600) || (kart->x-100 > 4000)) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex += 10;
   						}
						//printf("%d \n", player.vie);
					
					break;

					case SDLK_RIGHT:
						//preuve de concept de deplacement de "camera"
						printf("%d playerx \n", kart->x);
						printf("%d camx \n", camera2->x);
						
						movex += 10;
							
						if( ( kart->x < 0 ) || ( kart->x-100 > 2750 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movex -= 10;
   						}
					break;

					case SDLK_UP:
						movey -= 10;

						if( ( kart->y < 300 ) || ( kart->y-64 > 3000 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   						{
       						movey += 10;
   						} 
					break;

				case SDLK_DOWN:
					movey += 10;
				
					if( ( kart->y < 0 ) || ( kart->y-64 > 1300 ) ) //ca beug si le x du kart + sa taille "depasse la "limite"
   					{
       					movey -= 10;
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
