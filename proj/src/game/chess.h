#ifndef CHESS_H
#define CHESS_H

#include <lcom/lcf.h>
#include "clock.h"
#include "../sprites/sprite.h"

extern Sprite *board_img;
extern Sprite *sel_img;
extern Sprite *bB; 
extern Sprite *bK;      
extern Sprite *bN;
extern Sprite *bP;
extern Sprite *bQ;
extern Sprite *bR;
extern Sprite *wB;
extern Sprite *wK;
extern Sprite *wN;
extern Sprite *wP;
extern Sprite *wQ;
extern Sprite *wR;

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

static Piece board[8][8]; // board matrix
static bool white_turn; // true if white's turn, false if black's turn
static bool selected; // true if a piece is selected, false otherwise
static int sel_row = -1, sel_col = -1; // selected piece coordinates
static Piece prev[8][8]; // previous board matrix
static bool game_over; // true if game is over, false otherwise


void load_board();

int draw_board();

int draw_piece(int i, int j, uint32_t color);

int draw_pieces();

void select_piece(int row, int col);

void mouse_select_piece(int x, int y);

void keyboard_select_piece();

void deselect_piece();

bool is_selected();

Position get_selected();

int draw_selected();

void move_piece(int row, int col);

void mouse_move_piece(int xf, int yf);



bool is_valid_move(int xf, int yf);

Position *get_valid_moves(int *size);

Position get_king_position();

bool is_check();

bool is_checkmate();

void copy_board(Piece dest[8][8], Piece src[8][8]);

void undo_move();

void set_game_over(bool clock_timeout);


/* Piece movement functions */

Position *get_valid_king_moves(int *size);

Position *get_valid_queen_moves(int *size);

Position *get_valid_bishop_moves(int *size);

Position *get_valid_knight_moves(int *size);

Position *get_valid_rook_moves(int *size);

Position *get_valid_pawn_moves(int *size);


/* Auxiliary drawing functions */

int draw_king(int x, int y, uint32_t color);

int draw_queen(int x, int y, uint32_t color);

int draw_bishop(int x, int y, uint32_t color);

int draw_knight(int x, int y, uint32_t color);

int draw_rook(int x, int y, uint32_t color);

int draw_pawn(int x, int y, uint32_t color);

#endif
