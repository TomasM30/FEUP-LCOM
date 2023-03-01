#include <lcom/lcf.h>

#include <stdint.h>

#define TIMER_0 0x40
#define TIMER_CTRL 0x43

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t n = 0;
  if (sys_inb(port, &n) != 0) return 1;
  *value = (uint8_t) n;
  return 0;
}
