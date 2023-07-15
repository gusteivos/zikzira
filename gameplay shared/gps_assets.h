
#ifndef GPS_ASSETS_H
#define GPS_ASSETS_H

    #include "gps_format.h"


    typedef struct gps_assets
    {

        int            format_list_size;
        
        gps_format_t **format_list;

        
        int background_canvas_frames;

        float time_per_background_canvas_frames;

        sprite_t *background_canvas_spr;

    } gps_assets_t;


    extern gps_assets_t *create_gps_assets(void);


    extern void add_format_on_gps_assets(gps_assets_t *assets, gps_format_t *new_format);

    extern gps_format_t *rmv_format_from_gps_assets(gps_assets_t *assets, int format_index);

#endif
