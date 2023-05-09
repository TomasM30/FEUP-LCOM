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


Piece board[8][8];
int selected_x, selected_y;


void load_board();

int draw_board();

int draw_pieces();

void select_piece(int x, int y);

void move_piece(int xf, int yf);

#endif
