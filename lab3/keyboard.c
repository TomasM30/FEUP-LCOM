#include <lcom/lcf.h>

#include <keyboard.h>
#include "utils.h"

#include "i8042.h"


int hook_id = 0;

uint8_t read_byte;

int (kbc_subscribe_int)(uint8_t *bit_no){
    *bit_no = hook_id;

    if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) return 1;

    return 0;
}

int (kbc_unsubscribe_int)(){
    if (sys_irqrmpolicy(&hook_id) != 0) return 1;
    return 0;
}

void (kbc_ih)(){
    uint8_t stat;

    if (util_sys_inb(KBC_STATUS, &stat) != 0) return;
    if ((stat & KBC_ST_OBF) == 0){
        if (util_sys_inb(KBC_OUT_BUF, &read_byte)!= 0) return;

        if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) return;   
    }

}
