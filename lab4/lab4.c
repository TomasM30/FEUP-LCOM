// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "utils.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int r, ipc_status, i = 0;
message msg;
uint8_t bytes[3];
uint8_t irq_set, output, packet;

int (mouse_enable_data_reporting_ours)(){
    int tries = 3;
    while(output != MOUSE_SUCCESS && tries--){
        if (check_out_buf() != 0) return 1;
        if (sys_outb(MOUSE_IN_BUF, MOUSE_WRITE_REQUEST) != 0) return 1;
        if (check_out_buf() != 0) return 1;
        if (sys_outb(MOUSE_OUT_BUF, MOUSE_ENABLE_REP) != 0) return 1;
        if (check_out_buf() != 0) return 1;
        if (util_sys_inb(MOUSE_OUT_BUF, &output) != 0) return 1;
    }
    return 0;
}

int (mouse_disable_data_reporting)(){
    int tries = 3;
    while(output != MOUSE_SUCCESS && tries--){
        if (check_out_buf() != 0) return 1;
        if (sys_outb(MOUSE_IN_BUF, MOUSE_WRITE_REQUEST) != 0) return 1;
        if (check_out_buf() != 0) return 1;   
        if (sys_outb(MOUSE_OUT_BUF, MOUSE_DISABLE_REP) != 0) return 1;
        if (check_out_buf() != 0) return 1;
        if (util_sys_inb(MOUSE_OUT_BUF, &output) != 0) return 1;
    }
    return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    if (mouse_subscribe_int(&irq_set) != 0) return 1;
    mouse_enable_data_reporting_ours();
    
    while(cnt > 0){
        if ((r = driver_receive(ANY, &msg, &ipc_status))!= 0){
            printf("driver receive failed with %d,r");
            continue;
        }
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE){
            if (msg.m_notify.interrupts == BIT(irq_set)){
                mouse_ih();
                bytes[i] = packet;
                i++;
            }
        }

        if (i == 3){
            struct packet pp;
            pp.bytes[0] = bytes[0];
            pp.bytes[1] = bytes[1];
            pp.bytes[2] = bytes[2];
            pp.lb = bytes[0] & MOUSE_LB;
            pp.rb = bytes[0] & MOUSE_RB;
            pp.mb = bytes[0] & MOUSE_MB;
            pp.x_ov = bytes[0] & MOUSE_X_OVF;
            pp.y_ov = bytes[0] & MOUSE_Y_OVF;

            if (bytes[0] & MOUSE_X_SIGN) pp.delta_x = bytes[1] | 0xFF00; else pp.delta_x = bytes[1];
            if (bytes[0] & MOUSE_Y_SIGN) pp.delta_y = bytes[2] | 0xFF00; else pp.delta_y = bytes[2];


            mouse_print_packet(&pp);
            cnt--;
            i = 0;
        }
    }

   mouse_disable_data_reporting();
   if (mouse_unsubscribe_int() != 0) return 1;
   return 0; 
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
