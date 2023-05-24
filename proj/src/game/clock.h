#ifndef CLOCK_H
#define CLOCK_H

#include <lcom/lcf.h>
#include "../sprites/sprite.h"

extern Sprite* clock_background;

typedef struct {
    int minutes;
    int seconds;
} Time;

typedef struct {
    Time time;
    bool running;
} Clock;

static Clock white_clock;
static Clock black_clock;

void clock_init();

void clock_set(bool white_turn);

void clock_update();  

int draw_clock();

#endif
