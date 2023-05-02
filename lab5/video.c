#include "video.h"

int (set_graphics_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ah = 0x4F;
    reg86.al = 0x02;    

    reg86.bx = submode | BIT(14);

    if (sys_int86(&reg86) != 0) {
        printf("Failed to set graphics mode\n");
        return 1;
    }

    return 0;
}

int (set_text_mode)() {
    reg86_t reg86;                       
    memset(&reg86, 0, sizeof(reg86));   
    
    reg86.intno = 0x10;                 
    reg86.ah = 0x00;                    
    reg86.al = 0x03;                    
               
    reg86.bx = 0x0000;                  
    
    if(sys_int86(&reg86) != 0) {       
        printf("Set text mode failed\n");
        return 1;
    }
    
    return 0;
}

int (set_frame_buffer)(uint16_t mode) {
    memset(&mode_info, 0, sizeof(mode_info));
    if (vbe_get_mode_info(mode, &mode_info) != 0) return 1;

    unsigned int bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    unsigned int frame_size = mode_info.XResolution * mode_info.YResolution * bytes_per_pixel;

    struct minix_mem_range mr;
    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + frame_size;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) return 1;
  
        
    frame_buffer = vm_map_phys(SELF, (void*) mr.mr_base, frame_size);
    if (frame_buffer == NULL) return 1;

    return 0;
}

void (normalize_color)(uint32_t *color) {
    if (mode_info.BitsPerPixel != 32) *color = *color & (BIT(mode_info.BitsPerPixel) - 1);
}

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if(x > mode_info.XResolution || y > mode_info.YResolution) return 1;

    unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;

    unsigned int index = (mode_info.XResolution * y + x) * BytesPerPixel;

    if (memcpy(&frame_buffer[index], &color, BytesPerPixel) == NULL) return 1;

    return 0;
}

int (draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (unsigned i = 0 ; i < len ; i++)   
        if (draw_pixel(x + i, y, color) != 0) return 1;

    return 0;
}

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for(unsigned i = 0; i < height ; i++)
        if (draw_hline(x, y+i, width, color) != 0) return 1;

    return 0;
}
