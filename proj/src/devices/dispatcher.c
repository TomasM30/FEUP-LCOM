#include "dispatcher.h"

int subscribe_devices() {
    if (timer_subscribe_int(&irq_set_timer)) {
        printf("Error subscribing timer interrupts\n");
        return 1;
    }

    if (keyboard_subscribe_int(&irq_set_keyboard)) {
        printf("Error subscribing keyboard interrupts\n");
        return 1;
    }

    if (mouse_subscribe_int(&irq_set_mouse)) {
        printf("Error subscribing mouse interrupts\n");
        return 1;
    }

    return 0;
}

int unsubscribe_devices() {
    if (timer_unsubscribe_int()) {
        printf("Error unsubscribing timer interrupts\n");
        return 1;
    }

    if (keyboard_unsubscribe_int()) {
        printf("Error unsubscribing keyboard interrupts\n");
        return 1;
    }

    if (mouse_unsubscribe_int()) {
        printf("Error unsubscribing mouse interrupts\n");
        return 1;
    }

    return 0;
}

int dispatcher(GameState *state) {
    int ipc_status;
    message msg;
    uint8_t r;
    
    if (subscribe_devices()) return 1;

    while (true) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("Error driver_receive failed with: %d\n", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_set_timer) {
                        timer_int_handler();
                    }

                    if (msg.m_notify.interrupts & irq_set_keyboard) {
                        keyboard_ih();
                    }

                    if (msg.m_notify.interrupts & irq_set_mouse) {
                        mouse_ih();
                    }

                    break;
                default:
                    break;
            }
        } else {
            printf("Error received message was not notification\n");
        }
    }

    if (unsubscribe_devices()) return 1;

    return 0;
}

