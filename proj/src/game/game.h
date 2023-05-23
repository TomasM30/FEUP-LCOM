#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>

#include "data_types.h"
#include "menu.h"
#include "chess.h"
#include "../devices/dispatcher.h"
#include "../sprites/sprite.h"

GameState state;
extern Sprite *background;

int init_game();

int run_game();

int exit_game();

int draw_background();

#endif
