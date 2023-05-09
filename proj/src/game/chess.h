#ifndef CHESS_H
#define CHESS_H

#include <lcom/lcf.h>
#include "data_types.h"
#include "..devices/video.h"

Piece board[8][8];


int draw_board();

int draw_pieces();

void select_piece(int x, int y);

void move_piece(int xf, int yf);

#endif
