#include "gps_assets.h"

gps_assets_t *create_gps_assets()
{

    gps_assets_t *assets = (gps_assets_t *)malloc(sizeof(gps_assets_t));

    if (assets == NULL)
    {

        fprintf(stderr, "");

        return NULL;

    }

    assets->format_list_size = 0;

    assets->format_list      = NULL;



    return assets;

}


void add_format_on_gps_assets(gps_assets_t *assets, gps_format_t *new_format)
{

    assets->format_list_size++;

    assets->format_list = (gps_format_t **)realloc(assets->format_list, sizeof(gps_format_t *) * assets->format_list_size);

    assets->format_list[assets->format_list_size - 1] = new_format;

}

gps_format_t *rmv_format_from_gps_assets(gps_assets_t *assets, int format_index)
{

    if (assets == NULL || format_index < 0 || format_index >= assets->format_list_size)
    {
    
        fprintf(stderr, "Invalid assets or format_index\n");
    
        return NULL;
    
    }


    gps_format_t *removed_format = assets->format_list[format_index];

    for (int i = format_index; i < assets->format_list_size - 1; i++)
    {
    
        assets->format_list[i] = assets->format_list[i + 1];
    
    }

    assets->format_list_size--;

    assets->format_list = (gps_format_t **)realloc(assets->format_list, sizeof(gps_format_t *) * assets->format_list_size);


    return removed_format;
}
