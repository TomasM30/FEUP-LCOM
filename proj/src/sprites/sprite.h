#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include "../devices/video/video.h"

#include "../imgs/board.xpm"
#include "../imgs/pieces/bB.xpm"
#include "../imgs/pieces/bK.xpm"
#include "../imgs/pieces/bN.xpm"
#include "../imgs/pieces/bP.xpm"
#include "../imgs/pieces/bQ.xpm"
#include "../imgs/pieces/bR.xpm"
#include "../imgs/pieces/wB.xpm"
#include "../imgs/pieces/wK.xpm"
#include "../imgs/pieces/wN.xpm"
#include "../imgs/pieces/wP.xpm"
#include "../imgs/pieces/wQ.xpm"
#include "../imgs/pieces/wR.xpm"

#define PX_PER_SQUARE 108

typedef struct {
    uint16_t x, y;
    uint16_t height, width;
    uint32_t *colors;
} Sprite;

Sprite *board_img;
Sprite *bB;
Sprite *bK;
Sprite *bN;
Sprite *bP;
Sprite *bQ;
Sprite *bR;
Sprite *wB;
Sprite *wK;
Sprite *wN;
Sprite *wP;
Sprite *wQ;
Sprite *wR;

Sprite* cursor;

Sprite *create_sprite(xpm_map_t xpm);

void destroy_sprite(Sprite *sp);

int draw_sprite(Sprite *sp, int x, int y);

void load_sprites();

void dump_sprites();

#endif
