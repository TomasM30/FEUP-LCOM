#include <lcom/lcf.h>

#include <keyboard.h>
#include "utils.h"

#include "i8042.h"


int hook_id = 0;
extern int counter;

uint8_t read_byte;

int (kbc_subscribe_int)(uint8_t *bit_no){
    hook_id = *bit_no;

    if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) return 1;

    return 0;
}

int (kbc_unsubscribe_int)(){
    if (sys_irqrmpolicy(&hook_id) != 0) return 1;
    return 0;
}

void (kbc_ih)(){
    uint8_t stat;
    kbc_get_status(&stat);
    counter++;
    if ((stat & KBC_ST_OBF)){
        if (util_sys_inb(KBC_OUT_BUF, &read_byte)!= 0) return;
        counter++;
        if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) return;   
    }
    return;
}

int (kbc_get_status)(uint8_t *status){
    return util_sys_inb(KBC_STATUS, status);   
}

int (kbc_read_out_buf)(){
    return util_sys_inb(KBC_OUT_BUF, &read_byte);
}
