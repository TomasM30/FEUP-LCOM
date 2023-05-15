#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "kbc.h"
#include "../video/video.h"
#include "../../sprites/sprite.h"

extern Sprite *cursor;

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

int (mouse_write_cmd)(uint8_t cmd);

void (mouse_sync_bytes)();

void (mouse_parse_packet)();

void (mouse_update_position)();

int (mouse_draw_cursor)();

#endif
