#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

#define TIMER_0 0x40
#define TIMER_CTRL 0x43

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  uint8_t timer_reg;

  switch (timer){
    case 0: timer_reg = TIMER_0; break;
    case 1: timer_reg = TIMER_1; break;
    case 2: timer_reg = TIMER_2; break;
  }

  timer = 1<<((int)timer+1);

  uint8_t rb_word = 0xE0;  // (11000000 em binário)   Criar a bit mask da read-back word, como o status não nos interessa o 5 bit fica set a 1
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
