#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_MAIN_H
#define FUNCTIONS_MAIN_H

int hasWon(player_t* player, chrono_t tlimit);
void lap(sprite_t* kart, sprite_t* finish, player_t* player);
void ennemi_movement_ypos(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_yneg(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_xright(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_xleft(sprite_t* ennemi, sprite_t* r);
void update_states(player_t* player, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, sprite_t* r, sprite_t* finish, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, chrono_t tlimit);
int collision(sprite_t* a, sprite_t* b);
int collision2(sprite_t* a, sprite_t* b);
int collision_test(sprite_t* a, sprite_t* b);
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void renderer(SDL_Renderer* ecran, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, sprite_t* quiche, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, world_t* world, chrono_t tlimit);
void init(SDL_Renderer** renderer, SDL_Window** fenetre, SDL_Rect* camera2, SDL_Rect* dstrect, sprite_t* kart, sprite_t* ennemi, player_t* player, sprite_t* ennemi2, sprite_t* ennemi3, sprite_t* ennemi4, sprite_t* quiche);
void init_textures(world_t* world, SDL_Renderer* ecran);
void movement(SDL_Event* event, bool terminer, sprite_t* kart, SDL_Rect* camera2, sprite_t* r);

#endif
