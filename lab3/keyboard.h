#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

#define DELAY_US 20000

int (kbc_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();

void(kbc_ih)();

#endif
