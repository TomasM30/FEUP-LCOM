#include "serial_port.h"

int serial_port_hook_id = 3;
static Queue *queue;

Queue *getQueue(){
    return queue;
}

int serial_port_subscribe_int(uint8_t *bit_no){
    *bit_no = BIT(serial_port_hook_id);
    if(sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &serial_port_hook_id) != OK){
        printf("Error subscribing\n");
        return 1;
    }
    return 0;
}

int serial_port_unsubscribe_int(){
    if(sys_irqrmpolicy(&serial_port_hook_id) != OK){
        printf("Error unsubscribing\n");
        return 1;
    }
    return 0;
}

void serial_port_start(){
    uint8_t ierSt;
    if(util_sys_inb(COM1_BASE_ADDR + IER, &ierSt) != OK){
        printf("Error starting\n");
        return;
    }
    if(sys_outb(COM1_BASE_ADDR + IER, ierSt | IER_RDAI) != OK){
        printf("Error starting\n");
        return;
    }
    queue = createQueue(256);
}

void serial_port_end(){
    deleteItems(queue);
}

int serial_port_read_status(uint8_t *st){
    if(util_sys_inb(COM1_BASE_ADDR + LSR, st) != OK){
        printf("Error reading status\n");
        return 1;
    }
    return 0;
}

int serial_port_send_data(uint8_t data){
    uint8_t st;
    if(serial_port_read_status(&st) != OK){
        printf("Error sending data\n");
        return 1;
    }
    if(st & THR_EMPTY){
        if(sys_outb(COM1_BASE_ADDR + THR, data) != OK){
            printf("Error sending data\n");
            return 1;
        }
    }
    return 0;
}

int serial_port_read_data(){
    uint8_t st;
    if(serial_port_read_status(&st) != OK){
        printf("Error reading data\n");
        return 1;
    }
    if(st & (SER_OVERRUN_ERR | SER_PARITY_ERR | SER_FRAME_ERR)){
        printf("Error reading data\n");
        return 1;
    }
    if(st & RR_READY){
        uint8_t data;
        if(util_sys_inb(COM1_BASE_ADDR + RBR, &data) != OK){
            printf("Error reading data\n");
            return 1;
        }
        push(queue, data);
        return 0;
    }
    return 1;
}

int serial_port_ih(){
    uint8_t iirSt;
    util_sys_inb(COM1_BASE_ADDR + IIR, &iirSt);
    if(!(iirSt & INT_PEND)){
        if(iirSt & INT_ID){
            if(iirSt & RX_INT){
                serial_port_read_data();
            }
        }
    }
    return 0;
}
