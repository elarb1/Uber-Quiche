#include "score.h"
#include "errno.h"
#include "fonctions_SDL.h"

void score_write(player_t* player){
    FILE *score_file;
    int error = 0;

    score_file = fopen("scores.txt", "a+");

    if(score_file == NULL){
        printf("error ! = %d", errno);
        error = 1;
    }

    if(error == 0){
        fprintf(score_file, "%d - ", player->score);
    }

    fclose(score_file);
}

void score_read(SDL_Renderer* renderer, world_t* world){
    FILE *score_file;
    int error = 0;
    char scores[100];
    char tmp[100];

    if((score_file = fopen("scores.txt", "r")) == NULL){
        printf("error: %d", errno);
        error = 1;
    }
    if(error == 0){
        fgets(scores, 100, (FILE*)score_file);
        apply_text(renderer, 10, 300, 1000, 200, scores, world->font);
        fclose(score_file);
    }
}
