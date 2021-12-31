#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_MAIN_H
#define FUNCTIONS_MAIN_H

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void renderer(SDL_Renderer* ecran, TTF_Font* font, SDL_Texture* quiche4, SDL_Rect* camera2, SDL_Rect* dstrect, SDL_Texture* vehicle, sprite_t* kart, SDL_Texture* ennemi_tex, sprite_t* ennemi, SDL_Texture* quiche_tex, sprite_t* quiche);
void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t kart, sprite_t* ennemi);
void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2, sprite_t* r);
int collision(sprite_t* a, sprite_t* b);
void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, sprite_t* r);
void ennemi_movement_xleft(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_xright(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_yneg(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_ypos(sprite_t* ennemi, sprite_t* r);
#endif
