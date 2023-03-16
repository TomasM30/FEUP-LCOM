#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

#define DELAY_US 20000

int (kbc_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();
int (kbc_get_status)(uint8_t *status);
int (kbc_read_out_buf)();

void(kbc_ih)();

#endif
