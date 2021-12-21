#include "score.h"

void points_manager(player_t* player){
    /*if(collision_quiche == 1){
        player->score ++;
    } 
    if(collision_back == 1){
        player->score --;
    }
    if(player->chrono[lap] <= benchmark){ //benchmark est le temps de tour reference
        player->score++;
    }
    */

}

void score_write(player_t* player){
    FILE *score_file;
    char name[20];
    int error = 0;

    score_file = fopen("/scores/scores.txt", "a+");

    if(score_file == NULL){
        printf("error");
        error = 1;
    }
    if(error == 0){
        printf("Entrez votre nom: ");
        scanf("%s", &name);
        fprintf("score de %s: %d", name, player->score);
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
        printf("%s", scores)
        fclose(score_file);
    }
}