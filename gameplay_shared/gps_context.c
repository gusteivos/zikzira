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


    new_ctx->board_frame_x_offset = 0;

    new_ctx->board_frame_y_offset = 0;

    new_ctx->board_frame = gp_board_frame;


    new_ctx->board_frame_x_offset = 0;
    
    new_ctx->board_frame_y_offset = 0;

    new_ctx->next_pieces_frame = NULL;
    

    new_ctx->format_list_length = 0;

    new_ctx->format_list = NULL;


    return new_ctx;

}


void add_format_on_gps_context(gps_context_t *ctx, gps_format_t *format)
{

    if (ctx == NULL || format == NULL)
    {

        fprintf(stderr, "Invalid context or format\n");

        return;

    }


    ctx->format_list_length++;

    ctx->format_list = (gps_format_t **)realloc(ctx->format_list, sizeof(gps_format_t *) * ctx->format_list_length);

    ctx->format_list[ctx->format_list_length - 1] = format;


    return;

}


gps_format_t *rmv_format_from_gps_context(gps_context_t *ctx, int index)
{

    if (ctx == NULL || index < 0 || index >= ctx->format_list_length)
    {

        fprintf(stderr, "Invalid context or index\n");

        return NULL;

    }


    gps_format_t *removed_format = ctx->format_list[index];

    for (int i = index; i < ctx->format_list_length - 1; i++)
    {

        ctx->format_list[i] = ctx->format_list[i + 1];

    }


    ctx->format_list_length--;

    ctx->format_list = (gps_format_t **)realloc(ctx->format_list, sizeof(gps_format_t *) * ctx->format_list_length);


    return removed_format;

}


void destroy_gps_context(gps_context_t *ctx)
{

    if (ctx == NULL) return;

        /*Todo: */
    
    ctx = NULL;


    return;

}
