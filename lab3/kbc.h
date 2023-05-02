#ifndef LAB3_KBC_H
#define LAB3_KBC_H

#include <lcom/lcf.h>
#include "i8042.h"

#define DELAY_US 20000

int (kbc_get_status)(uint8_t *st);

int (kbc_read_data)(uint8_t *data);

int (kbc_write_cmd)(int port, uint8_t data);

#endif
