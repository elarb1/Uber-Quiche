#include "score.h"
#include "errno.h"

void score_write(player_t* player){
    FILE *score_file;
    char name[20];
    int error = 0;

    score_file = fopen("scores.txt", "a+");

    if(score_file == NULL){
        printf("error ! = %d", errno);
        error = 1;
    }

    if(error == 0){
        fprintf(score_file, "%d", player->score);
    }

    fclose(score_file);
}

void score_read(){
    FILE *score_file;
    int error = 0;
    char scores[100];

    if((score_file = fopen("/scores/scores.txt", "r")) == NULL){
        printf("error");
        error = 1;
    }
    if(error == 0){
        fgets(scores, 100, (FILE*)score_file);
        printf("%s", scores);
        fclose(score_file);
    }
}
