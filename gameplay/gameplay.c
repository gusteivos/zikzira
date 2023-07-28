#include "gameplay.h"


gps_context_t *gameplay_context = NULL;


void reset_gameplay()
{

    gameplay_context = NULL;

    return;

}


int start_gameplay(gps_context_t *context)
{

    if (context == NULL)
    {

        fprintf(stderr, "TODO: ");

        return 1;

    }

    gameplay_context = context;


    return 0;

}


int update_gameplay     (float dt)
{



    return 0;

}

int render_gameplay     (float dt)
{

    if (gameplay_context->background_canvas != NULL)
    {

        SDL_Rect background_canvas_destination_rectangle = gameplay_context->background_canvas->spr->destination_rectangle;

        background_canvas_destination_rectangle.x += gameplay_context->background_canvas_x_offset;

        background_canvas_destination_rectangle.y += gameplay_context->background_canvas_y_offset;


        if (SDL_BlitScaled(gameplay_context->background_canvas->spr->surface
                        , &gameplay_context->background_canvas->spr->source_rectangle
                        ,  rendering_surface
                        , &background_canvas_destination_rectangle) != 0)
        {

#ifndef NDEBUG

        fprintf(stderr, "The background_canvas reeds cannot be rendered, %s.\n", SDL_GetError());

#endif

        }

    }


    if (gameplay_context->board_frame != NULL)
    {

        SDL_Rect board_frame_destination_rectangle = gameplay_context->board_frame->spr->destination_rectangle;

        board_frame_destination_rectangle.x += gameplay_context->board_x_offset;

        board_frame_destination_rectangle.y += gameplay_context->board_y_offset;


        if (SDL_BlitScaled(gameplay_context->board_frame->spr->surface
                        , &gameplay_context->board_frame->spr->source_rectangle
                        ,  rendering_surface
                        , &board_frame_destination_rectangle) != 0)
        {

#ifndef NDEBUG

        fprintf(stderr, "The board_frame reeds cannot be rendered, %s.\n", SDL_GetError());

#endif

        }

    }
    

    return 0;

}

int late_update_gameplay(float dt)
{



    return 0;

}


void quit_gameplay()
{

    destroy_gps_context(gameplay_context);

    return;

}
