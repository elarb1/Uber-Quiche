#ifndef STRUCTURES_H
#define STRUCTURES_H

#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
#define MAX_LAPS 3
#define LEVEL_HEIGHT 1687
#define LEVEL_WIDTH 3000
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define MOVE_SPEED 1

struct sprite_s{
    int x; //pos en x
    int y; //pos en y
    int h; //hauteur
    int w; //largeur
    int vel; //pour l'ennemi
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
    chrono_t chronoLap[MAX_LAPS];
};
typedef struct player_s player_t;

#endif
