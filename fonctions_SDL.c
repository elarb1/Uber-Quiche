#include "fonctions_SDL.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer *renderer){


	SDL_Texture *texture;
	SDL_Surface* tmp= IMG_Load(nomfichier);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	return texture;
}

void apply_img(SDL_Renderer *renderer, SDL_Texture *tex, int x, int y){
	SDL_Rect dst = {0, 0, 0, 0};
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	dst.x = x;
	dst.y = y;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}
