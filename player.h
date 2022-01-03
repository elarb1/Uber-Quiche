#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structures.h"

#ifndef PLAYER_H
#define PLAYER_H

//condition win et lap
int hasWon(player_t* player, chrono_t tlimit);
void lap(sprite_t* kart, sprite_t* finish, player_t* player);

//ennemi
void ennemi_movement_ypos(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_yneg(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_xright(sprite_t* ennemi, sprite_t* r);
void ennemi_movement_xleft(sprite_t* ennemi, sprite_t* r);

//collisions
int collision(sprite_t* a, sprite_t* b);
int collision2(sprite_t* a, sprite_t* b);
int collision_test(sprite_t* a, sprite_t* b);

//tout est en void pour l'instant au cas ou on a pas besoin de retour
void score_write(player_t* player); //est appelee a la fin de la partie
void score_read();

//chrono
void timeReset(chrono_t* t);
void playerReset(player_t* p);
void counterP(player_t* p, int i);
void counterT(chrono_t* t);

#endif
