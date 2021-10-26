#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef FONCTIONS_SDL_H	
#define FONCTIONS_SDL_H	


SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);
int SDL_SetColorKey(SDL_Surface* surface, int flag, Uint32 key);
void apply_img(SDL_Renderer *renderer, SDL_Texture *tex, int x, int y);

#endif