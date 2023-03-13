#include <lcom/lcf.h>

#include <stdint.h>
#include <utils.h>

int counter = 0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  // Extract the least significant byte of val and store it in *lsb
  if (lsb == NULL){
    return 1;
  }

  *lsb = (uint8_t) (val & 0xFF);

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  // Extract the most significant byte of val and store it in *msb
  if (msb == NULL){
    return 1;
  }

  *msb = (uint8_t) ((val >> 8) & 0xFF);

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t n = 0;
  if (sys_inb(port, &n) != 0) return 1;

  #ifdef _LAB3
  counter++;
  #endif

  *value = (uint8_t) n;
  return 0;
}
