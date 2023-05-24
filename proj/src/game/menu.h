#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include "game.h"
#include "../sprites/sprite.h"

extern Sprite* logo;
extern Sprite* single_machine;
extern Sprite* double_machine;
extern Sprite* quit;
extern Sprite* return_button;
extern Sprite* undo;

extern GameState state;

void menu_handle_mouse();

void menu_handle_keyboard();

int draw_menu();

int draw_main_menu();

int draw_game_menu();

#endif
