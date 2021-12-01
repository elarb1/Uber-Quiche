#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "chrono.h"

void timeReset(chrono_t* t){
    t->min = 0;
    t->sec = 0;
    t->ms = 0;
}

void playerReset(player_t* p){
    p->vie = 0;
    p->score = 0;
    p->lap = 0;

    for(int i = 0; i < MAX_LAPS; i++){
        p->chronoLap[i].min = 0;
        p->chronoLap[i].sec = 0;
        p->chronoLap[i].ms = 0;
    }
}

int completeSeconde(int ms, chrono_t* t){
    t->ms += ms;

    if(t->ms == 1000){
        return 1;
    }

    return 0;
}

void counter(chrono_t* t){ //fonction comptant les secondes
    t->sec++;

    if(t->sec > 59){ //reset des secondes à 60, minute+1
        t->sec = 0;
        t->min++;
    }
}
