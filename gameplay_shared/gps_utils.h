
#ifndef GPS_UTILS_H
#define GPS_UTILS_H

    #include "gps_format.h"
    #include "gps_board.h"


    extern void render_gps_board_with_offset(SDL_Surface *surface, gps_board_t *board, uint16_t off_x, uint16_t off_y, int format_list_length, gps_format_t **format_list, bool scale);

#endif
