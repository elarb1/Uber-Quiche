#ifndef STRUCTURES_H
#define STRUCTURES_H

#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
struct sprite_s{
    int x; //pos en x
    int y; //pos en y
    int h; //hauteur
    int w; //largeur
};
typedef struct sprite_s sprite_t;

struct camera_s{
    int x; //pos en x
    int y; //pos en y
    int h; //hauteur
    int w; //largeur
};
typedef struct camera_s camera_t;

struct player_s{
    int vie;
    int score;
    int tours;
    int tMin, tSec;
};
typedef struct player_s player_t;

#endif
