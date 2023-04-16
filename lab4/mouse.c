#include "mouse.h"
#include "utils.h"

int hook_id = 0;
extern uint8_t bytes[3];
extern uint8_t packet;

int (mouse_subscribe_int)(uint8_t * bit_no){
    hook_id = *bit_no;
    if (sys_irqsetpolicy(MOUSE_IRQ, MOUSE_POLICIES, &hook_id) != 0) return 1;

    return 0;
}

int (mouse_unsubscribe_int)(){
    if (sys_irqrmpolicy(&hook_id) != 0) return 1;
    return 0;
}

void (mouse_ih)(){
    if (check_out_buf() != 0) return;
    util_sys_inb(MOUSE_OUT_BUF, &packet);
}

int (check_out_buf)(){
    uint8_t status;
    int i = 25;

    while(i > 0){
        if (util_sys_inb(MOUSE_IN_BUF, &status) != 0) return 1;
        if (!(status & BIT(1))) return 0;
        i--;
    }

    return 1;
}
