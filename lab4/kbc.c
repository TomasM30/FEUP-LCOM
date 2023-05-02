#include "kbc.h"

int hook_kbc = 1;
uint8_t scancode = 0x00;

int (kbc_subscribe_int)(uint8_t *bit_no) {
    *bit_no = hook_kbc;

    if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_kbc) != 0) return 1;

    return 0;
}

int (kbc_unsubscribe_int)() {
    if (sys_irqrmpolicy(&hook_kbc) != 0) return 1;

    return 0;
}

int (kbc_get_status)(uint8_t *st) {
    if (util_sys_inb(KBC_STAT_REG, st) != 0) return 1;

    return 0; 
}

int (kbc_read_data) (uint8_t *data) {
    uint8_t status;

    if (kbc_get_status(&status) != 0) return 1;

    if (status & KBC_OBF) {
        if (util_sys_inb(KBC_OUT_BUF, data) != 0) return 1;

        if ((status & (KBC_PARITY | KBC_TIMEOUT)) == 0 && (status & KBC_AUX) == 0) return 0;
        else return 1;
    }

    return 1;
}

int(kbc_write_cmd)(int port, uint8_t cmd) {
    uint8_t st = 0, attempts = 0;


    do {
        if (kbc_get_status(&st) != 0) {
            printf("Error getting KBC status");
            return -1;
        }

        if ((KBC_IBF & st) == 0) {
            sys_outb(port, cmd);
            return 0;
        }

        tickdelay(micros_to_ticks(DELAY_US));
        attempts++;
    } while (attempts < 5);

    return 1;
}

void (kbc_ih)() {
    if (kbc_read_data(&scancode) != 0) {
        printf("unable to read scancode");
    }
}

