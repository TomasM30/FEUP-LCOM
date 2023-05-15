#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>

#include "data_types.h"
#include "menu.h"
#include "chess.h"
#include "clock.h"
#include "../devices/dispatcher.h"

GameState state;

int init_game();

int run_game();

int exit_game();

#endif
