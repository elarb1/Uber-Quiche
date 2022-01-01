#ifndef SCORE.H
#define SCORE.H

#include "structures.h"

//tout est en void pour l'instant au cas ou on a pas besoin de retour
void points_manager(player_t* player);
void score_write(player_t* player); //est appelee a la fin de la partie
void score_read();
