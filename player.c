#include "structures.h"
#include "player.h"
#include "errno.h"

//condition win et lap
int hasWon(player_t* player, chrono_t tlimit){
    int result = 0;

    if(player->lap == LAPS){
        if(player->score == 4){
            player->win = 1;
            result = 1;
        }else if(player->score < 4){
            player->win = 2;
            result = 2;
        }else if((player->chronoLap[LAPS].min > tlimit.min) || (player->chronoLap[LAPS].min == tlimit.min && player->chronoLap[LAPS].sec > tlimit.sec)){
            player->win = 3;
            result = 3;
        }
    }

    return result;
}

void lap(sprite_t* kart, sprite_t* finish, player_t* player){
    if(collision2(kart, finish) == 1 && (player->deltaTime > 100)){
        player->lap += 1;
        player->deltaTime = 0;
    }
}


//ennemi
void ennemi_movement_ypos(sprite_t* ennemi, sprite_t* r){
    printf("%d \n", ennemi->vel);
    if(ennemi->y < 270){
        ennemi->vel = -1;
    }
    if(collision2(ennemi, r) == 1){
        printf("hi");
        ennemi->vel = 1;
    }
    if(ennemi->vel >0){
        ennemi->y -=1;
    }else{
        ennemi->y +=1;
    }
}

void ennemi_movement_yneg(sprite_t* ennemi, sprite_t* r){
    if(ennemi->y > 1500){
        ennemi->vel = 1;
    }
    if(collision2(ennemi, r) == 1){
        ennemi->vel = -1;
    }

    if(ennemi->vel >0){
        ennemi->y -=1;
    }else{
        ennemi->y +=1;
    }
}

void ennemi_movement_xright(sprite_t* ennemi, sprite_t* r){ //le rendering de la map est se distorte legerement et fait que la perspective de la vue est changee
    if(ennemi->x > 3000){
        ennemi->vel = 1;
    }
    if(collision2(ennemi, r) == 1){
        ennemi->vel = -1;
    }

    if(ennemi->vel >0){
        ennemi->x -=1;
    }else{
        ennemi->x +=1;
    }
}

void ennemi_movement_xleft(sprite_t* ennemi, sprite_t* r){ //le rendering de la map est se distorte legerement et fait que la perspective de la vue est changee
    if(ennemi->x < 500){
        ennemi->vel = -1;
    }
    if(collision2(ennemi, r) == 1){
        ennemi->vel = +1;
    }

    if(ennemi->vel >0){
        ennemi->x -=1;
    }else{
        ennemi->x +=1;
    }
}


//collisions
int collision(sprite_t* a, sprite_t* b){
  if( !(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) ||(b->y + b->h) < a->y)){
    b->x=0;
    b->y=0;
    b->w=0;
    b->h=0;
    b->isVisible = 1;
    return 1;
  }
  return 0;
}

int collision2(sprite_t* a, sprite_t* b){
  if(!(b->x > (a->x + a->w) || (b->x + b->w) < a->x ||  b->y > (a->y + a->h) || (b->y + b->h) < a->y)){
    return 1;
  }

  return 0;
}

int collision_test(sprite_t* a, sprite_t* b){
  if((a->x - a->w) == (b->x + b->w)){
    return 1;
  }

  return 0;
}



//score
void score_write(player_t* player){
    FILE *score_file;
    //char name[20];
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


//chrono
void timeReset(chrono_t* t){
    t->min = 0;
    t->sec = 0;
}

void playerReset(player_t* p){
    p->vie = 0;
    p->score = 0;
    p->lap = 0;

    for(int i = 0; i < LAPS; i++){
        p->chronoLap[i].min = 0;
        p->chronoLap[i].sec = 0;
    }
}

void counterP(player_t* p, int i){ //fonction comptant les secondes
    while(p->chronoLap[i].sec > 59){ //reset des secondes à 60, minute+1
        p->chronoLap[i].sec = 0;
        p->chronoLap[i].min++;
    }
}

void counterT(chrono_t *t){
    if(globaltime.sec > 59){
        globaltime.sec = 0;
        globaltime.min++;
    }
}
