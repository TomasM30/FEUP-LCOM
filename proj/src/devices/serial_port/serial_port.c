#include "serial_port.h"

int serial_port_hook_id = 4;
static Queue *receive_queue;
static Queue *send_queue;
static bool isHolding = true;

Queue *getreceive_queue(){
    return receive_queue;
}

int serial_port_subscribe_int(uint8_t *bit_no){
    *bit_no = BIT(serial_port_hook_id);
    if(sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &serial_port_hook_id) != 0){
        printf("Error subscribing\n");
        return 1;
    }
    return 0;
}

int serial_port_unsubscribe_int(){
    if(sys_irqrmpolicy(&serial_port_hook_id) != 0){
        printf("Error unsubscribing\n");
        return 1;
    }
    return 0;
}

int serial_port_start(){
    receive_queue = createQueue(256);
    send_queue = createQueue(256);
    uint8_t fcr = (FCR_ENABLE|FCR_CLEAR_RCVR|FCR_CLEAR_XMIT);
    if(sys_outb(COM1_BASE_ADDR + FCR, fcr) != 0){
        printf("Error starting serial port\n");
        return 1;
    }
    uint8_t ier = (IER_RDAI|IER_THREI);
    if(sys_outb(COM1_BASE_ADDR + IER, ier) != 0){
        printf("Error starting serial port\n");
        return 1;
    }
    uint8_t lcr = LCR_CONFIG;
    if(sys_outb(COM1_BASE_ADDR + LCR, lcr) != 0){
        printf("Error starting serial port\n");
        return 1;
    }
    return 0;
}

int serial_port_end(){
    uint8_t ier;
    if(util_sys_inb(COM1_BASE_ADDR + IER, &ier) != 0){
        printf("Error ending serial port\n");
        return 1;
    }
    ier &= ~(IER_RDAI|IER_THREI|IER_RLSI);
    if(sys_outb(COM1_BASE_ADDR + IER, ier) != 0){
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
    if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != 0){
        return 1;
    }
    if(!(iir & IIR_NO_INT)){
        if(iir & IIR_RDA){
            printf("RDA\n");
            while(serial_port_read_data());
            if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != 0){
                return 1;
            }
        }
        if (iir & IIR_THRE){
            printf("THRE\n");
            serial_port_send_queue_data();
            if(util_sys_inb(COM1_BASE_ADDR + IIR, &iir) != 0){
                return 1;
            }
        }
    }
    return 0;
}

int serial_port_send_data(uint8_t data){
    push(send_queue, data);
    if(isHolding){
        serial_port_send_queue_data();
    }
    return 0;
}

int serial_port_send_queue_data(){
    if(isEmpty(send_queue)){
        printf("queue is empty\n");
        isHolding = true;
        return 1;
    }
    uint8_t lsr;
    while(!isEmpty(send_queue)){
        if(sys_outb(COM1_BASE_ADDR + THR, front(send_queue)) != 0){
            printf("Error sending data\n");
            return 1;  
        }
        pop(send_queue);

        if(util_sys_inb(COM1_BASE_ADDR + LSR, &lsr) != 0){
                printf("Error sending data\n");
                return 1;
        }
        if(lsr & LSR_THRE){
            isHolding = true;
        } else {
            isHolding = false;
            return 1;
        }
    }
    return 0;
}


int serial_port_read_data(){
    uint8_t lsr, data;
    if(util_sys_inb(COM1_BASE_ADDR + LSR, &lsr) != 0){
        printf("Error reading data\n");
        return 1;
    }
    if(lsr & LSR_RDA){
        if(util_sys_inb(COM1_BASE_ADDR + RBR, &data) != 0){
            printf("Error reading data\n");
            return 1;
        }
        if(!(lsr & (SER_OVERRUN_ERR|SER_PARITY_ERR|SER_FRAME_ERR))){
            printf("pushed data\n");
            printf("%c", data);
            push(receive_queue, data);
            return 0;
        }
    }
    return 1;
}


void printData(){
    while(!isEmpty(getreceive_queue())){
        printf("%s", front(receive_queue));
        pop(receive_queue);
    }
}


