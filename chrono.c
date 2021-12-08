#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "chrono.h"

void timeReset(chrono_t* t){
    t->min = 0;
    t->sec = 0;
}

void playerReset(player_t* p){
    p->vie = 0;
    p->score = 0;
    p->lap = 0;

    for(int i = 0; i < MAX_LAPS; i++){
        p->chronoLap[i].min = 0;
        p->chronoLap[i].sec = 0;
    }
}

void counterP(player_t* p, int i){ //fonction comptant les secondes
    while(p->chronoLap[i].sec > 59){ //reset des secondes à 60, minute+1
        p->chronoLap[i].sec -= 60;
        p->chronoLap[i].min++;
    }
}

void counterT(chrono_t* t){
    if(t->sec > 59){
        t->sec = 0;
        t->min++;
    }
}