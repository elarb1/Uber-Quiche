#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structures.h"

#ifndef FONCTIONS_SDL_H	
#define FONCTIONS_SDL_H	


SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);
int SDL_SetColorKey(SDL_Surface* surface, int flag, Uint32 key);
void apply_img(SDL_Renderer *renderer, SDL_Texture *tex, sprite_t *sprite, int x, int y);
void init_sprite(sprite_t *sprite, int x, int y, int w, int h);
void init_ttf();
void apply_text(SDL_Renderer* renderer, int x, int y, int w, int h, const char* text, TTF_Font* font);
TTF_Font* load_font(const char *path, int font_size);

#endif
