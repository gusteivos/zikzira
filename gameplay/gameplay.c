#include "gameplay.h"


gps_context_t *gameplay_context = NULL;


gps_board_t *gameplay_board = NULL;


void reset_gameplay()
{

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

    clear_gps_board_b(gameplay_board);

    clear_gps_board_c(gameplay_board);


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

        board_frame_destination_rectangle.x += gameplay_context->board_frame_x_offset;

        board_frame_destination_rectangle.y += gameplay_context->board_frame_y_offset;


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
    

    if (gameplay_board != NULL)
    {

        for (int y = 0; y < gameplay_board->height; y++)
            for (int x = 0; x < gameplay_board->width; x++)
            {

                int cell_type = get_gps_board_a(gameplay_board, x, y);

                if (cell_type != GPS_BOARD_CLEANING_A_VALUE)
                {

                    sprite_t *cell_type_sprite = gameplay_context->format_list[(cell_type + 1) % gameplay_context->format_list_length]->spr->spr;


                    SDL_FPoint cell_type_sprite_position = get_gps_board_b(gameplay_board, x, y);


                    SDL_Rect  cell_type_destination_rectangle = cell_type_sprite->destination_rectangle;

                    cell_type_destination_rectangle.x += gameplay_context->board_x_offset;

                    cell_type_destination_rectangle.y += gameplay_context->board_y_offset;

                    cell_type_destination_rectangle.x += x * cell_type_destination_rectangle.w;

                    cell_type_destination_rectangle.y += y * cell_type_destination_rectangle.h;


                    SDL_BlitScaled(cell_type_sprite->surface, &cell_type_sprite->source_rectangle, rendering_surface, &cell_type_destination_rectangle);


                }

            }

    }


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



    return 0;

}


void quit_gameplay()
{

    destroy_gps_context(gameplay_context);

    return;

}
