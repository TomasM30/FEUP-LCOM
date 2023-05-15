#include "sprite.h"

Sprite *create_sprite(xpm_map_t xpm) {
    Sprite *sp = (Sprite *) malloc(sizeof(Sprite));

    xpm_image_t img;
    sp->colors = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &img);

    if (sp->colors == NULL) {
        free(sp);
        return NULL;
    }

    sp->width = img.width;
    sp->height = img.height;

    return sp;
}

void destroy_sprite(Sprite *sp) {
    if (sp == NULL)
        return;

    if (sp->colors != NULL)
        free(sp->colors);

    free(sp);
}

int draw_sprite(Sprite *sp, int x, int y) {
    for (int h = 0; h < sp->height; h++) {
        for (int w = 0; w < sp->width; w++) {
            uint32_t color = sp->colors[h * sp->width + w];
            if (color != xpm_transparency_color(XPM_8_8_8_8)) {
                if (vg_draw_pixel(x + w, y + h, color)) return 1;
            }
        }
    }
    
    return 0;
}

void load_sprites() {
    board_img = create_sprite((xpm_map_t) board_xpm);
    bB = create_sprite((xpm_map_t) bB_xpm);
    bK = create_sprite((xpm_map_t) bK_xpm);
    bN = create_sprite((xpm_map_t) bN_xpm);
    bP = create_sprite((xpm_map_t) bP_xpm);
    bQ = create_sprite((xpm_map_t) bQ_xpm);
    bR = create_sprite((xpm_map_t) bR_xpm);
    wB = create_sprite((xpm_map_t) wB_xpm);
    wK = create_sprite((xpm_map_t) wK_xpm);
    wN = create_sprite((xpm_map_t) wN_xpm);
    wP = create_sprite((xpm_map_t) wP_xpm);
    wQ = create_sprite((xpm_map_t) wQ_xpm);
    wR = create_sprite((xpm_map_t) wR_xpm);

    cursor = create_sprite((xpm_map_t) cursor_xpm);
}

void dump_sprites() {
    destroy_sprite(board_img);
    destroy_sprite(bB);
    destroy_sprite(bK);
    destroy_sprite(bN);
    destroy_sprite(bP);
    destroy_sprite(bQ);
    destroy_sprite(bR);
    destroy_sprite(wB);
    destroy_sprite(wK);
    destroy_sprite(wN);
    destroy_sprite(wP);
    destroy_sprite(wQ);
    destroy_sprite(wR);
    destroy_sprite(cursor);
}
