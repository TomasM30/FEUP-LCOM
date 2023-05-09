#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>

#include "data_types.h"
#include "menu.h"
#include "chess.h"
#include "../devices/dispatcher.h"

GameState state;

int game_init();

int game_run();

int game_exit();

#endif
