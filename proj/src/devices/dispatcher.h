#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <lcom/lcf.h>

#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "mouse/mouse.h"
#include "video/video.h"
#include "serial_port/serial_port.h"
#include "rtc/rtc.h"

#include "../game/game.h"
#include "../game/chess.h"

static uint8_t irq_set_timer, irq_set_keyboard, irq_set_mouse, irq_set_serial_port, irq_set_rtc;
extern int timer_counter;
extern uint8_t scancode;
extern uint8_t byte_index;
extern struct packet packet;
extern int mouse_x, mouse_y;

extern GameState state;
extern bool selected;


int subscribe_devices();

int unsubscribe_devices();

int dispatcher();

void timer_handler();

void keyboard_handler();

void mouse_handler();

void serial_port_handler();

void rtc_handler();

#endif
