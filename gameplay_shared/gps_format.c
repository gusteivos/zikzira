#include "gps_format.h"


gps_format_t *create_gps_format(bool animated, sprite_anim_t *spr)
{

    if (spr == NULL)
    {

        fprintf(stderr, "");

        return NULL;

    }


    gps_format_t *new_format = (gps_format_t *)malloc(sizeof(gps_format_t));

    if (new_format == NULL)
    {

        fprintf(stderr, "");

        return NULL;

    }

    new_format->spr = spr;

    new_format->spr->spr->destination_rectangle.w = GPS_FORMAT_WIDTH ;

    new_format->spr->spr->destination_rectangle.h = GPS_FORMAT_HEIGHT;


    new_format->spr->can_animate = animated;


    return new_format;

}
