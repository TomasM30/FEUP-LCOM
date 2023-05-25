#include "game.h"

int init_game() {
    if (vg_start(VBE_864p_DC)) return 1;

    load_sprites();

    load_board();

    // state = MENU;
    state = GAME;

    return 0;
}

int run_game() {
    if (init_game()) return 1;
    
    if (dispatcher()) return 1;

    if (exit_game()) return 1;

    return 0;
}

int exit_game() {
    if (vg_exit()) return 1;
    if(serial_port_exit() != 0) return 1;

    dump_sprites();

    return 0;
}

int draw_background() {
    if (draw_sprite(background, 864, 0)) return 1;

    return 0;
}
