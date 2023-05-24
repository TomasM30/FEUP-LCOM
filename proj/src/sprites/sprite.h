#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include "../devices/video/video.h"
#include "../imgs/cursor.xpm"
#include "../imgs/background.xpm"
#include "../imgs/logo.xpm"
#include "../imgs/buttons/single_machine.xpm"
#include "../imgs/buttons/double_machine.xpm"
#include "../imgs/buttons/quit.xpm"
#include "../imgs/buttons/return.xpm"
#include "../imgs/buttons/undo.xpm"
#include "../imgs/clock_background.xpm"
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

#define SQUARE_SIZE 108

typedef struct {
    uint16_t height, width;
    int x, y;  
    uint32_t *colors;
} Sprite;


Sprite *cursor;
Sprite *background;
Sprite *logo;
Sprite *single_machine;
Sprite *double_machine;
Sprite *quit;
Sprite *return_button;
Sprite *undo;
Sprite *clock_background;
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


Sprite *create_sprite(xpm_map_t xpm);

void destroy_sprite(Sprite *sp);

int draw_sprite(Sprite *sp, int x, int y);

void load_sprites();

void dump_sprites();

#endif
