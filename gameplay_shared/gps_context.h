
#ifndef GPS_CONTEXT_H
#define GPS_CONTEXT_H

    #include "gps_format.h"

    #include <stdint.h>


    typedef struct gps_context
    {

        int            format_list_length;

        gps_format_t **format_list;


        uint16_t background_canvas_x_offset;

        uint16_t background_canvas_y_offset;

        sprite_anim_t *background_canvas;


        SDL_Rect board_offset;

        uint16_t board_x_offset;

        uint16_t board_y_offset;


        uint16_t board_frame_x_offset;

        uint16_t board_frame_y_offset;

        sprite_anim_t *board_frame;

        
        uint16_t next_pieces_x_offset;

        uint16_t next_pieces_y_offset;


        uint16_t next_pieces_frame_x_offset;

        uint16_t next_pieces_frame_y_offset;

        sprite_anim_t *next_pieces_frame;


        sprite_t *i_cursor;

        sprite_t *x_cursor;

        sprite_t *y_cursor;

    } gps_context_t;


    extern gps_context_t *create_gps_context(sprite_anim_t *bg_canvas, sprite_anim_t *gp_board_frame);


    extern void add_format_on_gps_context(gps_context_t *ctx, gps_format_t *format);


    extern gps_format_t *rmv_format_from_gps_context(gps_context_t *ctx, int index);


    extern void destroy_gps_context(gps_context_t *ctx);

#endif
