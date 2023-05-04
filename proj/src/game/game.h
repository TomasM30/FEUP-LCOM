#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>

#include "../devices/dispatcher.h"

typedef enum {
    MENU,
    GAME, 
    EXIT
} GameState;

static GameState state;




#endif
