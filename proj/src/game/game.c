#include "game.h"

int game_init() {
    if (vg_start(VBE_864p_DC)) return 1;

    load_sprites();

    load_board();

    return 0;
}

int game_run() {
    if (game_init()) return 1;
    
    if (dispatcher()) return 1;

    if (game_exit()) return 1;

    return 0;
}

int game_exit() {
    if (vg_exit()) return 1;

    dump_sprites();

    return 0;
}
