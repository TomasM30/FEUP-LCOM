#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_hook_id = 0, cnt = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  //frequency cant be less or equal to 18
  if (freq <= 18){
    return 1;
  }

  /*
  * number of ticks the timer will count before each interrupt
  * frequency of the clock signal (TIMER_FREQ) / desired frequency (freq) = number of clock ticks
  */
  uint16_t div = TIMER_FREQ/freq;


  //return the timer configuration if its possible (timer_get_conf(timer, &control_word) == 0)
  uint8_t control_word = 0;
  if (timer_get_conf(timer, &control_word) != 0){
    return 1;
  }

  //counting mode bits
  control_word &= 0x0F;


  control_word |= TIMER_LSB_MSB;

  control_word |= (timer << 6);

  sys_outb(TIMER_CTRL, control_word);

  uint8_t msb = 0;
  uint8_t lsb = 0;
  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);

  switch (timer)
  {
  case 0:
    if(sys_outb(TIMER_0, lsb) != 0) return 1;
    if(sys_outb(TIMER_0, msb) != 0) return 1;
    break;
  
  case 1:
    if(sys_outb(TIMER_1, lsb) != 0) return 1;
    if(sys_outb(TIMER_1, msb) != 0) return 1;
    break;

  case 2:
    if(sys_outb(TIMER_2, lsb) != 0) return 1;
    if(sys_outb(TIMER_2, msb) != 0) return 1;
    break;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  timer_hook_id = *bit_no;

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != 0) return 1;

  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_hook_id) != 0) return 1;

  return 0;
}

void (timer_int_handler)() {
  cnt++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  uint8_t timer_reg;

  switch (timer){
    case 0: timer_reg = TIMER_0; break;
    case 1: timer_reg = TIMER_1; break;
    case 2: timer_reg = TIMER_2; break;
  }

  timer = 1<<((int)timer+1);

  uint8_t rb_word = 0xE0;  // (11100000 em binário)   Criar a bit mask da read-back word, como o status não nos interessa o 5 bit fica set a 1
  rb_word |= timer;         // Completar a read-back word com a mask do timer

  if (sys_outb(TIMER_CTRL, rb_word) != 0) return 1;

  if (util_sys_inb(timer_reg, st) != 0) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  union timer_status_field_val val;

  switch(field){
    case tsf_all:
      val.byte = st;
      break;
      
    case tsf_initial:
      st &= TIMER_LSB_MSB;

      if (st == (0x30)){
        val.in_mode = MSB_after_LSB;
      }
      else if (st == (0x20)){
        val.in_mode = MSB_only;
      }
      else if (st == (0x10)){
        val.in_mode = LSB_only;
      }
      else{
        val.in_mode = INVAL_val;
      }
      break;

    case tsf_mode:
      val.count_mode = (0x0F & st) >> 1;
      if ((0x0F & st) >> 1 == 6) val.count_mode = 2;
      else if ((0x0F & st) >> 1 == 7) val.count_mode = 3;
      break;

    case tsf_base:
      val.bcd = (st & 1) == 1;
      break;

  }

  if (timer_print_config(timer, field, val) != 0) return 1;

  return 0;
}
