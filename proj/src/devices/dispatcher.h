#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <lcom/lcf.h>

#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "mouse/mouse.h"
#include "serial_port/serial_port.h"
#include "rtc/rtc.h"

#include "../game/game.h"


static uint8_t irq_set_timer, irq_set_keyboard, irq_set_mouse;
// static uint8_t irq_set_serial_port, irq_set_rtc;

int subscribe_devices();

int unsubscribe_devices();

int dispatcher(GameState *state);

#endif
