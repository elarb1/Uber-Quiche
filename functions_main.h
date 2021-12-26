#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_MAIN_H
#define FUNCTIONS_MAIN_H

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void renderer(SDL_Renderer* ecran, SDL_Texture* quiche4, SDL_Rect* camera2, SDL_Rect* dstrect, SDL_Texture* vehicle, sprite_t* kart, SDL_Texture* ennemi_tex, sprite_t* ennemi);
void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect);
void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2);

#endif
