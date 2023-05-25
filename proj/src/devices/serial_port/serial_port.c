#include "serial_port.h"

int serial_port_hook_id = 4;
static Queue *receive_queue;
static Queue *send_queue;
static bool holding = false;

Queue *getreceive_queue(){
    return receive_queue;
}

Queue *getsend_queue(){
    return send_queue;
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

int serial_port_start(){
    send_queue = createQueue(256);
    receive_queue = createQueue(256);
    uint8_t fcr = (FCR_ENABLE|FCR_CLEAR_RCVR|FCR_CLEAR_XMIT);
    if(sys_outb(COM1_BASE_ADDR + FCR, fcr) != OK){
        printf("Error starting serial port\n");
        return 1;
    }
    uint8_t ier = (IER_RDAI|IER_THREI|IER_RLSI);
    if(sys_outb(COM1_BASE_ADDR + IER, ier) != OK){
        printf("Error starting serial port\n");
        return 1;
    }
    return 0;
}

int serial_port_end(){
    uint8_t ier;
    if(util_sys_inb(COM1_BASE_ADDR + IER, &ier) != OK){
        printf("Error ending serial port\n");
        return 1;
    }
    ier &= ~(IER_RDAI|IER_THREI|IER_RLSI);
    if(sys_outb(COM1_BASE_ADDR + IER, ier) != OK){
        printf("Error ending serial port\n");
        return 1;
    }
    return 0;
}

int serial_port_exit(){
    deleteItems(receive_queue);
    deleteItems(send_queue);
    if(serial_port_end() != 0){
        printf("Error exiting serial port\n");
        return 1;
    }
    return 0;
}

int serial_port_ih(){
    uint8_t iir;
    if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != OK){
        printf("Error reading status\n");
        return 1;
    }
    while(!(iir & IIR_NO_INT)){
        if(iir & IIR_RDA){
            while(!serial_port_read_data());
            if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != 0){
                return 1;
            }
        }
        else if(iir & IIR_THRE){
            while(!serial_port_send_queue_data());
            if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != 0){
                return 1;
            }
        }
    }
    return 0;
}

int serial_port_send_data(uint8_t data){
    push(send_queue, data);
    if(!holding){
        if(serial_port_send_queue_data() != 0){
            printf("Error sending data\n");
            return 1;
        }
    }
    return 0;
}


int serial_port_send_queue_data(){
    if(isEmpty(send_queue)){
        holding = true;
        return 1;
    }

    uint8_t data;

    while(!isEmpty(send_queue)){
        if(sys_outb(COM1_BASE_ADDR + THR, front(send_queue)) != OK){
            printf("Error sending data\n");
            return 1;
        }
        pop(send_queue);
        if(util_sys_inb(COM1_BASE_ADDR + LSR, &data) != OK){
            printf("Error reading status\n");
            return 1;
        }
        data &= LSR_THRE;
        if(data == 0){
            holding = true;
            return 1;
        } 
        else{
            holding = false;
        }
    }
    return 0;
}

int serial_port_read_data(){
    uint8_t lsr;
    uint8_t data;
    if(util_sys_inb(COM1_BASE_ADDR + LSR, &lsr) != OK){
        printf("Error reading data\n");
        return 1;
    }
    lsr &= LSR_RDA;
    if(lsr == 0){
        return 1;
    } else {
        if(util_sys_inb(COM1_BASE_ADDR + RBR, &data) != OK){
            printf("Error reading data\n");
            return 1;
        }
        if(data & (SER_OVERRUN_ERR| SER_PARITY_ERR| SER_FRAME_ERR)){
            printf("Error reading data\n");
            return 1;
        }
        push(receive_queue, data);
        return 0;
    }
}


