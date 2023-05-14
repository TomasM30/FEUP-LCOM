#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef enum {
    MENU, 
    GAME,
    QUIT
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
    UNDEFINED,
    WHITE,
    BLACK
} Color;

typedef struct {
    Type type;
    Color color;
} Piece;

typedef struct {
    int row;
    int col;
} Position;

#endif
