#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_MAIN_H
#define FUNCTIONS_MAIN_H

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void renderer(SDL_Renderer* ecran, SDL_Texture* quiche4, SDL_Rect* camera2, SDL_Rect* dstrect, SDL_Texture* vehicle, sprite_t* kart, SDL_Texture* ennemi_tex, sprite_t* ennemi, SDL_Texture* quiche_tex, sprite_t* quiche);
void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t kart);
void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2);
int collision(sprite_t* a, sprite_t* b);
void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche);
#endif
