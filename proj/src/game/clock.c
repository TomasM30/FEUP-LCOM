#include "clock.h"

int draw_clocks() {
    if (draw_sprite(clock_background, 940, 34)) return 1;

    if (draw_sprite(clock_background, 940, 790)) return 1;

    return 0;
}
