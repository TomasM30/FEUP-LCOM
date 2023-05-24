#ifndef CLOCK_H
#define CLOCK_H

#include <lcom/lcf.h>
#include "../sprites/sprite.h"

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

#endif
