#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structures.h"

#ifndef SCORE_H
#define SCORE_H

#include "structures.h"

//tout est en void pour l'instant au cas ou on a pas besoin de retour
void score_write(player_t* player); //est appelee a la fin de la partie
void score_read();

#endif