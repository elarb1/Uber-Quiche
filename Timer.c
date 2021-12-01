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
    p.map = 0;
    p.chronoLap[] = {0};

    return p;
}

int completeSeconde(int ms, timer_t* t){
    t->ms += ms;

    if(t->ms == 1000){
        return 1;
    }

    return 0;
}

void counter(timer_t* t){ //fonction comptant les secondes
    t->sec++;

    if(t->sec > 59){ //reset des secondes à 60, minute+1
        sec = 0;
        min++;
    }
}

timer_t saveChrono(timer_t* t){
    return t;

    /* même chose que:
    
    timer_t newt;
    
    newt = t;

    return newt;
    */
}
