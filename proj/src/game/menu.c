#include "menu.h"

int draw_main_menu() {
    if (draw_sprite(logo, 908, 106)) return 1;
    
    if (draw_sprite(single_machine, 908, 342)) return 1;
    
    if (draw_sprite(double_machine, 908, 422)) return 1;

    if (draw_sprite(quit, 908, 576)) return 1;

    return 0;
}
