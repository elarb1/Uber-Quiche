#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

//reset fait de 2 manières, on garde ce qui vous convient

void timeReset(timer_t* t){
    t->min = 0;
    t->sec = 0;
    t->ms = 0;
}

player_t playerReset(player_t p){
    p.vie = 0;
    p.score = 0;

    return p;
}

int completeSeconde(int ms){
    t->ms += ms;

    if(t->ms == 1000){
        return 1;
    }

    return 0;
}

void counter(timer_t* chrono){ //fonction comptant les secondes
    chrono->sec++;

    if(chrono->sec > 59){ //reset des secondes à 60, minute+1
        sec = 0;
        min++;
    }
}
