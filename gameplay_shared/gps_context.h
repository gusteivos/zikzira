
#ifndef GPS_CONTEXT_H
#define GPS_CONTEXT_H

    #include "gps_format.h"

    #include <stdint.h>


    typedef struct gps_context
    {

        int            format_list_size;

        gps_format_t **format_list;


        uint16_t background_canvas_x_offset;

        uint16_t background_canvas_y_offset;

        sprite_anim_t *background_canvas;


        uint16_t gameplay_board_x_offset;

        uint16_t gameplay_board_y_offset;

        sprite_anim_t *gameplay_board_frame;


        sprite_t *in_cursor;

        sprite_t *x_cursor;

        sprite_t *y_cursor;

    } gps_context_t;


    extern gps_context_t *create_gps_context(sprite_anim_t *bg_canvas, sprite_anim_t *gp_board_frame);


    extern void destroy_gps_context(gps_context_t *ctx);

#endif
