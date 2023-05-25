#ifndef SP_H
#define SP_H

#include <lcom/lcf.h>
#include "SERIALPORT.H"
#include "queue.h"

Queue *getreceive_queue();
Queue *getsend_queue();
int serial_port_subscribe_int(uint8_t *bit_no);
int serial_port_unsubscribe_int();
int serial_port_start();
int serial_port_end();
int serial_port_exit();
int serial_port_ih();
int serial_port_send_data(uint8_t data);
int serial_port_send_queue_data();
int serial_port_read_data();

#endif

