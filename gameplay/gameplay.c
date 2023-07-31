#include "gameplay.h"


static key_delay_t *key_delay_gameplay_list = NULL;


gps_context_t *gameplay_context = NULL;


gps_board_t *gameplay_board = NULL;


gps_board_t *gameplay_next_pieces = NULL;


void reset_gameplay()
{

    key_delay_gameplay_list = NULL;


    gameplay_context = NULL;


    gameplay_board = NULL;


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


    gameplay_board = create_gps_board(6, 13);

    if (gameplay_context == NULL)
    {

        fprintf(stderr, "TODO: ");

        return 1;

    }

    // clear_gps_board_a(gameplay_board);

        clear_gps_board_a_value(gameplay_board, 0);

    clear_gps_board_b(gameplay_board);

    clear_gps_board_c(gameplay_board);

    /*Temp: */
        
        gameplay_next_pieces = create_gps_board(1, 3);

            // clear_gps_board_a(gameplay_next_pieces);

                clear_gps_board_a_value(gameplay_next_pieces, 1);

        clear_gps_board_b(gameplay_next_pieces);

        clear_gps_board_c(gameplay_next_pieces);
        

    return 0;

}


int update_gameplay     (float dt)
{



    if (gameplay_context->background_canvas != NULL)
        update_sprite_anim(gameplay_context->background_canvas, dt);

    if (gameplay_context->board_frame != NULL)
        update_sprite_anim(gameplay_context->board_frame, dt);


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
                        , NULL
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

        board_frame_destination_rectangle.x += gameplay_context->board_frame_x_offset;

        board_frame_destination_rectangle.y += gameplay_context->board_frame_y_offset;


        if (SDL_BlitScaled(gameplay_context->board_frame->spr->surface
                        , NULL
                        ,  rendering_surface
                        , &board_frame_destination_rectangle) != 0)
        {

#ifndef NDEBUG

        fprintf(stderr, "The board_frame reeds cannot be rendered, %s.\n", SDL_GetError());

#endif

        }

    }


    if (gameplay_context->next_pieces_frame != NULL)
    {

        SDL_Rect next_pieces_frame_destination_rectangle = gameplay_context->next_pieces_frame->spr->destination_rectangle;

        next_pieces_frame_destination_rectangle.x += gameplay_context->next_pieces_frame_x_offset;

        next_pieces_frame_destination_rectangle.y += gameplay_context->next_pieces_frame_y_offset;


        if (SDL_BlitScaled(gameplay_context->next_pieces_frame->spr->surface
                        ,  NULL
                        ,  rendering_surface
                        , &next_pieces_frame_destination_rectangle) != 0)
        {

#ifndef NDEBUG

        fprintf(stderr, "The board_frame reeds cannot be rendered, %s.\n", SDL_GetError());

#endif

        }

    }

    
    render_gps_board_with_offset(rendering_surface, gameplay_board,
                                 gameplay_context->board_x_offset, gameplay_context->board_y_offset,
                                 gameplay_context->format_list_length, gameplay_context->format_list,
                                 false);


    render_gps_board_with_offset(rendering_surface, gameplay_next_pieces,
                                 gameplay_context->next_pieces_x_offset, gameplay_context->next_pieces_y_offset,
                                 gameplay_context->format_list_length, gameplay_context->format_list,
                                 false);


    if (gameplay_context->i_cursor != NULL)
    {

        SDL_Rect i_cursor_destination_rectangle = gameplay_context->i_cursor->destination_rectangle;

        i_cursor_destination_rectangle.x += gameplay_context->board_x_offset;

        i_cursor_destination_rectangle.y += gameplay_context->board_y_offset;


        SDL_BlitScaled(gameplay_context->i_cursor->surface, &gameplay_context->i_cursor->source_rectangle, rendering_surface, &i_cursor_destination_rectangle);

    }

    if (gameplay_context->x_cursor != NULL)
    {

        SDL_Rect x_cursor_destination_rectangle = gameplay_context->x_cursor->destination_rectangle;

        x_cursor_destination_rectangle.x += gameplay_context->board_x_offset;

        x_cursor_destination_rectangle.y += gameplay_context->board_y_offset;
    
        x_cursor_destination_rectangle.y -= gameplay_context->i_cursor->destination_rectangle.h;
        

        SDL_BlitScaled(gameplay_context->x_cursor->surface, &gameplay_context->x_cursor->source_rectangle, rendering_surface, &x_cursor_destination_rectangle);

    }

    if (gameplay_context->y_cursor != NULL)
    {

        SDL_Rect y_cursor_destination_rectangle = gameplay_context->x_cursor->destination_rectangle;

        y_cursor_destination_rectangle.x += gameplay_context->board_x_offset;

        y_cursor_destination_rectangle.y += gameplay_context->board_y_offset;
    
        y_cursor_destination_rectangle.x -= gameplay_context->i_cursor->destination_rectangle.w;
        

        SDL_BlitScaled(gameplay_context->y_cursor->surface, &gameplay_context->y_cursor->source_rectangle, rendering_surface, &y_cursor_destination_rectangle);

    }



    return 0;

}

int late_update_gameplay(float dt)
{

    update_key_delays_in_list(&key_delay_gameplay_list, dt);


    return 0;

}


void quit_gameplay()
{

    destroy_key_delay_list(key_delay_gameplay_list);

    destroy_gps_context(gameplay_context);


    return;

}
