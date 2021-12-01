#ifndef STRUCTURES_H
#define STRUCTURES_H

#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
#define MAX_LAPS 3

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
    int lap;
    timer_t chronolap[MAX_LAPS];
};
typedef struct player_s player_t;

struct timer_s{
    int min;
    int sec;
    int ms;
};
typedef struct timer_s timer_t;

#endif
