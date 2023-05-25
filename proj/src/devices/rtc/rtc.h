#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define RTC_IRQ 8

#define RTC_SECONDS 0
#define RTC_MINUTES 2
#define RTC_HOURS 4
#define RTC_DAY 7
#define RTC_MONTH 8
#define RTC_YEAR 9

#define RTC_A 10
#define RTC_B 11
#define RTC_C 12
#define RTC_D 13

#define RTC_A_UIP BIT(7)
#define RTC_B_SET BIT(7)
#define RTC_B_UIE BIT(4)
#define RTC_C_UF BIT(4)

int (rtc_subscribe_int)(uint8_t *bit_no);
int (rtc_unsubscribe_int)();
int (can_read_datetime)();
int (read_datetime)(uint8_t reg);
int (rtc_ih)();
int (enable_update_interrupts)(bool enable);


#endif 

