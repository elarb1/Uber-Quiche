#include "fonctions_SDL.h"
#include "structures.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer *renderer){


	SDL_Texture *texture;
	SDL_Surface* tmp= IMG_Load(nomfichier);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	return texture;
}

void apply_img(SDL_Renderer *renderer, SDL_Texture *tex, sprite_t *sprite, int x, int y){
	SDL_Rect dst = {0, 0, 0, 0};
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	dst.x = sprite->x - x;
	dst.y = sprite->y - y;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}


void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
	sprite->x = x;
	sprite->y = y;
	sprite->w = w;
	sprite->h = h;
}