#include "gps_context.h"

gps_context_t *create_gps_context(sprite_anim_t *bg_canvas, sprite_anim_t *gp_board_frame)
{

    if (bg_canvas == NULL) return NULL;


    gps_context_t *new_ctx = (gps_context_t *)malloc(sizeof(gps_context_t));

    if (new_ctx == NULL)
    {

        fprintf(stderr, "TODO:");

        return NULL;

    }

    new_ctx->background_canvas_x_offset = 0;

    new_ctx->background_canvas_y_offset = 0;

    new_ctx->background_canvas = bg_canvas;


    new_ctx->board_x_offset = 0;

    new_ctx->board_y_offset = 0;

    new_ctx->board_frame = gp_board_frame;


    return new_ctx;

}


void destroy_gps_context(gps_context_t *ctx)
{

    if (ctx == NULL) return;

        /*Todo: */
    
    ctx = NULL;


    return;

}
