#include "fonctions_SDL.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer){


	SDL_Texture *texture;
	SDL_Surface* tmp= IMG_Load(nomfichier);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	return texture;
}
