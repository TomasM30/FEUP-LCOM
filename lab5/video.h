#ifndef VIDEO_H
#define VIDEO_H

#include "lcom/lcf.h"
#include "vbe.h"

vbe_mode_info_t mode_info;
uint8_t *frame_buffer;

int (set_graphics_mode)(uint16_t submode);

int (set_text_mode)();

int (set_frame_buffer)(uint16_t mode);

void (normalize_color)(uint32_t *color);

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
