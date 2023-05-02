#ifndef MOUSE_H
#define MOUSE_H

#include "lcom/lcf.h"
#include "kbc.h"
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (mouse_write)(uint8_t cmd);

void (mouse_ih)();

void (mouse_sync_bytes)();

void (mouse_parse_packet)();

#endif
