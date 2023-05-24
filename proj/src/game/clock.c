#include "clock.h"

void clock_init() {
    white_clock.time.minutes = 5;
    white_clock.time.seconds = 0;
    white_clock.running = false;

    black_clock.time.minutes = 5;
    black_clock.time.seconds = 0;
    black_clock.running = false;
}

void clock_set(bool white_turn) {
    if (white_turn) {
        white_clock.running = true;
        black_clock.running = false;
    }
    else {
        white_clock.running = false;
        black_clock.running = true;
    }
}

void clock_update() {
    if (white_clock.running) {
        if (white_clock.time.seconds == 0) {
            if (white_clock.time.minutes == 0) {
                white_clock.running = false;
                return;
            }
            white_clock.time.minutes--;
            white_clock.time.seconds = 59;
        }
        else white_clock.time.seconds--;
    }

    if (black_clock.running) {
        if (black_clock.time.seconds == 0) {
            if (black_clock.time.minutes == 0) {
                black_clock.running = false;
                return;
            }
            black_clock.time.minutes--;
            black_clock.time.seconds = 59;
        }
        else black_clock.time.seconds--;
    }
}

int draw_clock() {
    if (draw_sprite(clock_background, 940, 34)) return 1;

    if (draw_sprite(clock_background, 940, 790)) return 1;

    return 0;
}
