#include <lcom/lcf.h>

#ifndef _LCOM_MOUSE_H
#define _LCOM_MOUSE_H

#define MOUSE_OUT_BUF 0x60
#define MOUSE_IN_BUF 0x64
#define MOUSE_WRITE_REQUEST 0xD4

#define MOUSE_SUCCESS 0xFA
#define MOUSE_ERROR 0xFE
#define MOUSE_ENABLE_REP 0xF4
#define MOUSE_DISABLE_REP 0xF5
#define MOUSE_READ_DATA 0xEB  //mouse replies with ACK and then 3 bytes of data

#define MOUSE_IRQ 12
#define MOUSE_POLICIES (IRQ_REENABLE | IRQ_EXCLUSIVE)

#define MOUSE_LB BIT(0)
#define MOUSE_RB BIT(1)
#define MOUSE_MB BIT(2)
#define MOUSE_X_SIGN BIT(4)
#define MOUSE_Y_SIGN BIT(5)
#define MOUSE_X_OVF BIT(6)
#define MOUSE_Y_OVF BIT(7)

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (check_out_buf)();


#endif
