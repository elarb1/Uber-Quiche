#ifndef TIMER_H
#define TIMER_H

void timeReset(chrono_t* t);

player_t playerReset(player_t p);

int completeSeconde(int ms);

void counter(chrono_t* chrono);

chrono_t saveChrono(chrono_t* t);

#endif
