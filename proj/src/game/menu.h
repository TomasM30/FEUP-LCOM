#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include "../sprites/sprite.h"

extern Sprite* logo;
extern Sprite* single_machine;
extern Sprite* double_machine;
extern Sprite* quit;


int draw_main_menu();

int draw_game_menu();

#endif
