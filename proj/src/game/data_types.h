#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef enum {
    MENU, 
    GAME,
    QUIT
} GameState;

typedef struct {
    int minutes;
    int seconds;
} Time;

#endif
