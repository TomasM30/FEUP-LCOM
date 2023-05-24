#ifndef SP_H
#define SP_H

#include <lcom/lcf.h>
#include "SERIALPORT.H"
#include "queue.h"

int serial_port_subscribe_int(uint8_t *bit_no);
int serial_port_unsubscribe_int();
void serial_port_start();
void serial_port_end();
int serial_port_read_status(uint8_t *st);
int serial_port_send_data(uint8_t data);
int serial_port_read_data();
int serial_port_ih();

#endif

