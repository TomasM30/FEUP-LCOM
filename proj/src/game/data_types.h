#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef enum {
    MENU, 
    GAME,
    EXIT
} GameState;


typedef enum {
    EMPTY,
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
} Type;

typedef enum {
    WHITE,
    BLACK
} Color;

typedef struct {
    Type type;
    Color color;
} Piece;

#endif
