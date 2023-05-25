#include <lcom/lcf.h>

#include "game/game.h"

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/proj/src/output.txt");

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int (proj_main_loop)(int argc, char *argv[]) {
    if (game_run()) return 1;
    
    return 0;
}
