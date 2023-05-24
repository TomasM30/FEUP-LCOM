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


int draw_clocks();

#endif
