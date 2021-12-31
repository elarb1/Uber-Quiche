#include "fonctions_SDL.h"
#include "structures.h"

void init_ttf(){
	if(TTF_Init() == -1){
		printf("TTF_Init: %s \n", TTF_GetError());
	}
}

TTF_Font* load_font(const char *path, int font_size){
	TTF_Font* font = TTF_OpenFont(path, font_size);
	if(font == NULL){
		fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
	}
	return font;
}


void apply_text(SDL_Renderer* renderer, int x, int y, int w, int h, const char* text, TTF_Font* font){
	SDL_Color colour = {255, 0, 255, 0};
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dstrect2 = {x, y, w, h};
	SDL_RenderCopy(renderer, tex, NULL, &dstrect2);
}

void clean_font(TTF_Font* font){
	TTF_CloseFont(font);
}

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