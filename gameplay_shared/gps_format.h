
#ifndef GPS_FORMAT_H
#define GPS_FORMAT_H

    #include <sprite_anim.h>


    #define GPS_FORMAT_WIDTH  16

    #define GPS_FORMAT_HEIGHT 16


    typedef struct gps_format
    {
    
        sprite_anim_t *spr;

        /*Todo: */

    } gps_format_t;
    

    extern gps_format_t *create_gps_format(bool animated, sprite_anim_t *spr);

#endif
