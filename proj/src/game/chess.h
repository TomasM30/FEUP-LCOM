#ifndef CHESS_H
#define CHESS_H

#include <lcom/lcf.h>
#include "data_types.h"
#include "../devices/video/video.h"
#include "../sprites/sprite.h"

extern Sprite *board_img;
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

static Piece board[8][8]; // board matrix
static bool white_turn = true; // true if white's turn, false if black's turn
static bool selected; // true if a piece is selected, false otherwise
static int sel_row = -1, sel_col = -1; // selected piece coordinates


void load_board();

int draw_board();

int draw_pieces();

void select_piece(int x, int y);

void deselect_piece();

bool is_selected();

void move_piece(int xf, int yf);

bool is_valid_move(int xf, int yf);

int draw_piece(int i, int j, uint32_t color);

int draw_king(int x, int y, uint32_t color);

int draw_queen(int x, int y, uint32_t color);

int draw_bishop(int x, int y, uint32_t color);

int draw_knight(int x, int y, uint32_t color);

int draw_rook(int x, int y, uint32_t color);

int draw_pawn(int x, int y, uint32_t color);

#endif
