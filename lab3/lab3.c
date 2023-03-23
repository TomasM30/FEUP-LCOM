#ifndef _LAB3
#define _LAB3

#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <keyboard.h>
#include <utils.h>
#include <lcom/timer.h>
#include "i8042.h"

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


/*
    NOTES:
        KBC IN_BUF & OUT_BUF port: 0x60
        KBC Status port: 0x64

        need to check bit 7 and 6 of status register for errors (if they are set) in IH
        
        if bit 1 of status is set, dont write to IN_BUF on either 0x60 or 0x64

        kbd_test_scan():
            return when reading breakcode of ESC (0x81)
            first byte of 2b scan codes is usually 0xE0
            subscribe to interrupts (global variables to use in IH)
            use IRQ_REENABLE | IRQ_EXCLUSIVE in sys_irqsetpolicy()
            read only 1 byte per interrupt

        


*/

extern uint8_t read_byte;
int counter = 0;
int r;
uint8_t irq_set;  
message msg;
int ipc_status;
uint8_t bytes[2];
int i = 0;

int(kbd_test_scan)() {
  
  if (kbc_subscribe_int(&irq_set) != 0) return 1;
  

  while(read_byte != KBC_ESC){

    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver receive failed with: %d,r ");
      continue;
    }

    if(is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(irq_set)){
            kbc_ih();

            if (read_byte == 0xE0){
              bytes[i] = read_byte;
              i++;
              continue;
            }

            bytes[i] = read_byte;
            kbd_print_scancode(!(read_byte & SCAN_MK_OR_BR), i+1, bytes);
            i = 0;
          }
          break;
        default:
          break;
      }
    }

    tickdelay(micros_to_ticks(DELAY_US+5000));
    
  }

  kbd_print_no_sysinb(counter);
  return 0;
}


int(kbd_test_poll)() {
  
  do{


    tickdelay(micros_to_ticks(DELAY_US));
  }while (read_byte != KBC_ESC);

  return 0;
}

uint8_t timer_irq_set;
int cnt;

int(kbd_test_timed_scan)(uint8_t n) {
  if (kbc_subscribe_int(&irq_set) != 0) return 1;
  if (timer_subscribe_int(&timer_irq_set) != 0) return 1;

  while(read_byte != KBC_ESC && (cnt/60.0 < n)){
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver receive failed with: %d,r ");
      continue;
    }
     if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE){
        if (msg.m_notify.interrupts & BIT(irq_set)){
          kbc_ih();

          if (read_byte == 0xE0){
            bytes[i] = read_byte;
            i++;
            continue;
          }

          bytes[i] = read_byte;
          kbd_print_scancode(!(read_byte & SCAN_MK_OR_BR), i+1, bytes);
          i = 0;

          cnt = 0;

        }
        else if (msg.m_notify.interrupts & BIT(timer_irq_set))
        {
          timer_int_handler();
        }
        
     }
  }

  if (kbc_unsubscribe_int() != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;

  kbd_print_no_sysinb(counter);

  return 0;
}

#endif
