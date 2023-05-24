#include "menu.h"

void menu_handle_mouse() {    
    if (state == MENU) {
        if (mouse_clicked_button(single_machine)) state = GAME;

        if (mouse_clicked_button(double_machine)) state = GAME;
        
        if (mouse_clicked_button(quit)) state = QUIT;
    }

    if (state == GAME) {
        if (mouse_clicked_button(return_button)) {
            state = MENU;
            load_board();
        }
    }
}

void menu_handle_keyboard() {
    if (state == MENU) {
        if (scancode == KBC_BRK_ESC_KEY) state = QUIT;
    }

    if (state == GAME) {
        if (scancode == KBC_BRK_ESC_KEY) { 
            state = MENU;
            load_board();
        }
    }
}

int draw_menu() {
    switch (state) {
        case MENU:
            if (draw_main_menu()) return 1;
            break;
        case GAME:
            if (draw_game_menu()) return 1;
            break;
        
        default:
            break;
    }

     return 0;
}

int draw_main_menu() {
    if (draw_sprite(logo, 908, 106)) return 1;
    
    if (draw_sprite(single_machine, 908, 342)) return 1;
    
    if (draw_sprite(double_machine, 908, 422)) return 1;

    if (draw_sprite(quit, 908, 576)) return 1;

    return 0;
}

int draw_game_menu() {
    if (draw_sprite(return_button, 908, 598)) return 1;

    if (draw_sprite(undo, 908, 658)) return 1;
    
    if (draw_clocks()) return 1;

    return 0;
}
