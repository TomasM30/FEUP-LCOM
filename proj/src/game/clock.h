#ifndef CLOCK_H
#define CLOCK_H

#include <lcom/lcf.h>
#include "data_types.h"

typedef struct {
    Time time;
    bool running;
} Clock;

Clock white_clock;
Clock black_clock;



#endif
