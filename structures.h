#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
#define LAPS 4
#define LEVEL_HEIGHT 1687
#define LEVEL_WIDTH 3000
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define MOVE_SPEED 10

struct sprite_s{
    int x; //pos en x
    int y; //pos en y
    int h; //hauteur
    int w; //largeur
    int vel; //pour l'ennemi
    int direction; // 0 up 1 left 2 down 3 right
    int isVisible;
};
typedef struct sprite_s sprite_t;

struct camera_s{
    int x; //pos en x
    int y; //pos en y
    int h; //hauteur
    int w; //largeur
};
typedef struct camera_s camera_t;

struct chrono_s{
    int min;
    int sec;
};
typedef struct chrono_s chrono_t;

struct player_s{
    int vie;
    int score;
    int lap;
    int deltaTime;
	int lastTime;
    int win;
    chrono_t chronoLap[LAPS];
};
typedef struct player_s player_t;

struct world_s{
    SDL_Texture* bg;
    SDL_Texture* player_tex;
    SDL_Texture* ennemi_tex;
    SDL_Texture* quiche_tex;
    TTF_Font* font;
    int status; //0 = main menu, 1 = game, 2 = ending, 3 = quit
};
typedef struct world_s world_t;
#endif
