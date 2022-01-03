#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structures.h"

#ifndef END_MENU_RENDERERS_H
#define END_MENU_RENDERERS_H

void menu_renderer(SDL_Renderer* ecran, world_t world);
void end_renderer(SDL_Renderer* ecran, world_t world);

#endif