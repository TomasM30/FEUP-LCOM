#ifndef LAB3_KBC_H
#define LAB3_KBC_H

#include <lcom/lcf.h>
#include "i8042.h"

#define DELAY_US 20000

int (kbc_subscribe_int)(uint8_t *bit_no);

int (kbc_unsubscribe_int)();

int (kbc_get_status)(uint8_t *st);

int (kbc_read_data)(uint8_t *data);

int (kbc_write)(int port, uint8_t data);

void (kbc_ih)();

#endif
