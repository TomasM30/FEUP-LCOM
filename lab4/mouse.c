#include "mouse.h"

int mouse_id = 2;
struct packet pp;
uint8_t packet[3];
uint8_t byte;
uint8_t idx;

int (mouse_subscribe_int)(uint8_t *bit_no) {
    *bit_no = BIT(mouse_id);

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_id);
}

int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_id);
}

int (mouse_write)(uint8_t cmd) {
    uint8_t ack_flag; uint8_t attempts = 5;

    do {
        attempts--;
        if (kbc_write_cmd(KBC_IN_BUF_CMD, 0xD4) != 0) return 1;
        if (kbc_write_cmd(KBC_OUT_BUF, cmd) != 0) return 1;
        tickdelay(DELAY_US);
        if (kbc_read_data(&ack_flag) != 0) return 1;
        if (ack_flag == KBC_ACK) return 0;
    } while (ack_flag != KBC_ACK && attempts);


    return 1;
}

void (mouse_sync_bytes)() {
    if ((idx == 0) && (byte & BIT(3))) {
        packet[idx] = byte;
        idx++;
    }

    else if (idx > 0) {
        packet[idx] = byte;
        idx++;
    }
}

void (mouse_parse_packet)() {
    for (int i = 0; i < 3; i++) {
        packet[i] = packet[i];
    }
    
    pp.rb = packet[0] & BIT(1);
    pp.mb = packet[0] & BIT(2);
    pp.lb = packet[0] & BIT(0);
    pp.delta_x = (packet[0] & BIT(4)) ? (0xFF00 | packet[1]) : (packet[1]);
    pp.delta_y = (packet[0] & BIT(5)) ? (0xFF00 | packet[2]) : (packet[2]);
    pp.x_ov = packet[0] & BIT(6);
    pp.y_ov = packet[0] & BIT(7);
}

void (mouse_ih)() {
    kbc_read_data(&byte);
}
