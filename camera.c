#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "structures.h"


int getStartX(camera_t camera){
	return camera.x;
}

int getStartY(camera_t camera){
	return camera.y;
}

void setStartX(camera_t camera, int x){
    camera.x = x;
}

void setStartY(camera_t camera, int x){
    camera.y = x;
}

void scroll(sprite_t player, camera_t camera){
    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX(camera) + LIMITE_X;
int xlimmax = xlimmin + LIMITE_W;
int ylimmin = getStartY(camera) + LIMITE_Y;
int ylimmax = ylimmin + LIMITE_H;
    if (cxperso < xlimmin)
{
setStartX(camera,  3);
}

}
