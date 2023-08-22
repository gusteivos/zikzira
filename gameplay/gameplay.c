#include "gameplay.h"


static key_delay_t *key_delay_gameplay_list = NULL;


gps_context_t *gameplay_context = NULL;


gps_board_t *gameplay_board = NULL;


gps_board_t *gameplay_next_pieces_board    = NULL;

gps_board_t *gameplay_current_pieces_board = NULL;


int current_pieces_cursor_x_position = 0;

int current_pieces_cursor_y_position = 0;


float current_pieces_fall_down_timer = 1.0f;

float current_pieces_fall_down_timer_counter = 0.0f;


bool traverse_gameplay_board(void);

void fill_gameplay_board_holes(void);

void randomize_next_pieces_board(void);


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

    clear_gps_board_a(gameplay_board);


        // for (int y = 0; y < gameplay_board->height; y++)
        // {

        //     for (int x = 0; x < gameplay_board->width; x++)
        //     {

        //         set_gps_board_a(gameplay_board, x, y, (rand() % (gameplay_context->format_list_length - 0)) + 0);

        //     }

        // }


        // clear_gps_board_a_value(gameplay_board, 0);

    clear_gps_board_b(gameplay_board);

    clear_gps_board_c(gameplay_board);

    /*Temp: */
        
        // gameplay_next_pieces_board = create_gps_board(1, 3);

            // clear_gps_board_a(gameplay_next_pieces);

                // clear_gps_board_a_value(gameplay_next_pieces_board, 1);

                // destroy_gps_board(gameplay_next_pieces_board);

                gameplay_next_pieces_board = create_gps_board(1, 3);

                randomize_next_pieces_board();

                gameplay_current_pieces_board = gameplay_next_pieces_board;

                SDL_Delay(500);

                gameplay_next_pieces_board = create_gps_board(1, 3);

                randomize_next_pieces_board();


        clear_gps_board_b(gameplay_next_pieces_board);

        clear_gps_board_c(gameplay_next_pieces_board);


    // traverse_gameplay_board();

    // for (int y = 0; y < gameplay_board->height; y++)
    // {

    //     for (int x = 0; x < gameplay_board->width; x++)
    //     {

    //         if (get_gps_board_c(gameplay_board, x, y))
    //         {

    //             set_gps_board_a(gameplay_board, x, y, -1);

    //         }

    //     }

    // }

    // fill_gameplay_board_holes();

    
    return 0;

}


bool teste = true;


int update_gameplay     (float dt)
{

    update_key_delays_in_list(&key_delay_gameplay_list, dt);


    if (keyboard_state[SDL_SCANCODE_A] && current_pieces_cursor_x_position > 0)
    {

        if (get_gps_board_a(gameplay_board, current_pieces_cursor_x_position - 1, current_pieces_cursor_y_position) == GPS_BOARD_CLEANING_A_VALUE)
            if(add_key_delay_on_list(&key_delay_gameplay_list, SDL_SCANCODE_A, 0.150f) == true)
                current_pieces_cursor_x_position--;

    }

    if (keyboard_state[SDL_SCANCODE_D] && current_pieces_cursor_x_position < gameplay_board->width - 1)
    {

        if (get_gps_board_a(gameplay_board, current_pieces_cursor_x_position + 1, current_pieces_cursor_y_position) == GPS_BOARD_CLEANING_A_VALUE)
            if(add_key_delay_on_list(&key_delay_gameplay_list, SDL_SCANCODE_D, 0.150f) == true)
                current_pieces_cursor_x_position++;

    }


    if (keyboard_state[SDL_SCANCODE_W])
    {

        if(add_key_delay_on_list(&key_delay_gameplay_list, SDL_SCANCODE_W, 0.250f) == true)
        {
            
            int a = get_gps_board_a(gameplay_current_pieces_board, 0, 1);

            set_gps_board_a(gameplay_current_pieces_board, 0, 1, get_gps_board_a(gameplay_current_pieces_board, 0, 0));
        
            set_gps_board_a(gameplay_current_pieces_board, 0, 0, get_gps_board_a(gameplay_current_pieces_board, 0, 2));

            set_gps_board_a(gameplay_current_pieces_board, 0, 2, a);

        }

    }


    if (teste)
    {

        if (keyboard_state[SDL_SCANCODE_S])
        {

            if(add_key_delay_on_list(&key_delay_gameplay_list, SDL_SCANCODE_S, 0.175f) == true)
                current_pieces_fall_down_timer_counter = 0;

        }

        if (current_pieces_fall_down_timer_counter <= 0)
        {

            if (current_pieces_cursor_y_position >= gameplay_board->height - 1 ||
                get_gps_board_a(gameplay_board, current_pieces_cursor_x_position, current_pieces_cursor_y_position + 1) != GPS_BOARD_CLEANING_A_VALUE)
            {

                for (int _y = gameplay_current_pieces_board->height; _y > 0; _y--)
                {

                    for (int _x = 0; _x < gameplay_current_pieces_board->width; _x++)
                    {

                        set_gps_board_a(gameplay_board, _x + current_pieces_cursor_x_position, (_y - 1) + (current_pieces_cursor_y_position - (gameplay_current_pieces_board->height - 1)), get_gps_board_a(gameplay_current_pieces_board, _x, _y - 1));

                    }

                }

                destroy_gps_board(gameplay_current_pieces_board);

                gameplay_current_pieces_board = gameplay_next_pieces_board;

                gameplay_next_pieces_board = create_gps_board(1, 3);

                randomize_next_pieces_board();



                clear_gps_board_c(gameplay_board);

                if (traverse_gameplay_board())
                {

                    teste = false;

                    for (int y = 0; y < gameplay_board->height; y++)
                    {

                        for (int x = 0; x < gameplay_board->width; x++)
                        {

                            if (get_gps_board_c(gameplay_board, x, y))
                            {

                                set_gps_board_a(gameplay_board, x, y, -1);

                            }

                        }

                    }

                    fill_gameplay_board_holes();

                }

                current_pieces_cursor_y_position = -1;

            }
            else
                current_pieces_cursor_y_position++;

            current_pieces_fall_down_timer_counter = current_pieces_fall_down_timer;

        }
        else
        {

            current_pieces_fall_down_timer_counter -= dt;

        }

    }
    else
    {
        
        bool tese = false;

        for (int y = 0; y < gameplay_board->height; y++)
        {

            for (int x = 0; x < gameplay_board->width; x++)
            {

                SDL_FPoint b_value = get_gps_board_b(gameplay_board, x, y);

                if (b_value.y != y)
                {

                    b_value.y = lerp_threshold(b_value.y, y, 8.5f * dt, 0.1f);
                    
                    set_gps_board_b(gameplay_board, x, y, b_value);

                    tese = true;

                }

            }

        }

        if (!tese)
        {

            clear_gps_board_c(gameplay_board);

            if (traverse_gameplay_board())
            {

                for (int y = 0; y < gameplay_board->height; y++)
                {

                    for (int x = 0; x < gameplay_board->width; x++)
                    {

                        if (get_gps_board_c(gameplay_board, x, y))
                        {

                            set_gps_board_a(gameplay_board, x, y, -1);

                        }

                    }

                }

                fill_gameplay_board_holes();

            }
            else
                teste = true;

        }

    }


    if (gameplay_context->background_canvas != NULL)
        update_sprite_anim(gameplay_context->background_canvas, dt);

    if (gameplay_context->board_frame != NULL)
        update_sprite_anim(gameplay_context->board_frame, dt);


    return 0;

}

int render_gameplay     (float dt)
{

    SDL_FillRect(rendering_surface, &rendering_surface_rect, 0x00);

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

    
    render_gps_board_with_b_and_offset(rendering_surface, gameplay_board,
                                       gameplay_context->board_x_offset, gameplay_context->board_y_offset,
                                       gameplay_context->format_list_length, gameplay_context->format_list,
                                       true);


    render_gps_board_with_offset(rendering_surface, gameplay_current_pieces_board,
                                gameplay_context->board_x_offset + (GPS_FORMAT_WIDTH  * current_pieces_cursor_x_position),
                                gameplay_context->board_y_offset + (GPS_FORMAT_HEIGHT * current_pieces_cursor_y_position) - (GPS_FORMAT_HEIGHT * (gameplay_current_pieces_board->height - 1)),
                                gameplay_context->format_list_length, gameplay_context->format_list,
                                true);


    render_gps_board_with_offset(rendering_surface, gameplay_next_pieces_board,
                                gameplay_context->next_pieces_x_offset, gameplay_context->next_pieces_y_offset,
                                gameplay_context->format_list_length, gameplay_context->format_list,
                                true);


    if (gameplay_context->i_cursor != NULL)
    {

        render_surface_in_surface_with_offset(gameplay_context->i_cursor->surface, &gameplay_context->i_cursor->source_rectangle,
                                            rendering_surface, &gameplay_context->i_cursor->destination_rectangle,
                                            gameplay_context->board_x_offset + gameplay_context->i_cursor->destination_rectangle.w * current_pieces_cursor_x_position,
                                            gameplay_context->board_y_offset + gameplay_context->i_cursor->destination_rectangle.h * current_pieces_cursor_y_position);
    
    }

    if (gameplay_context->x_cursor != NULL)
    {

        render_surface_in_surface_with_offset(gameplay_context->x_cursor->surface, &gameplay_context->x_cursor->source_rectangle,
                                            rendering_surface, &gameplay_context->x_cursor->destination_rectangle,
                                            gameplay_context->board_x_offset + GPS_FORMAT_WIDTH * current_pieces_cursor_x_position,
                                            gameplay_context->board_y_offset - gameplay_context->i_cursor->destination_rectangle.h);

    }

    if (gameplay_context->y_cursor != NULL)
    {

        render_surface_in_surface_with_offset(gameplay_context->y_cursor->surface, &gameplay_context->y_cursor->source_rectangle,
                                            rendering_surface, &gameplay_context->y_cursor->destination_rectangle,
                                            gameplay_context->board_x_offset - gameplay_context->i_cursor->destination_rectangle.w,
                                            gameplay_context->board_y_offset + GPS_FORMAT_WIDTH * current_pieces_cursor_y_position);

    }


    return 0;

}

int late_update_gameplay(float dt)
{

    update_key_delays_in_list(&key_delay_gameplay_list, dt);


    // destroy_gps_board(gameplay_next_pieces_board);

    // gameplay_next_pieces_board = create_gps_board(1, 3);

    // randomize_next_pieces_board();

    // gameplay_current_pieces_board = gameplay_next_pieces_board;


    return 0;

}


void quit_gameplay()
{

    destroy_key_delay_list(key_delay_gameplay_list);

    destroy_gps_context(gameplay_context);


    return;

}


void randomize_next_pieces_board()
{

    srand(time(NULL) + rand());

    for (int y = 0; y < gameplay_next_pieces_board->height; y++)
    {

        for (int x = 0; x < gameplay_next_pieces_board->width; x++)
        {

            set_gps_board_a(gameplay_next_pieces_board, x, y, (rand() % (gameplay_context->format_list_length - 0)) + 0);

        }

    }    

}


bool traverse_gameplay_board()
{

    if (traverse_left_to_right_define_c_based_on_a(gameplay_board, 3) == true)
        return true;

    if (traverse_top_to_bottom_define_c_based_on_a(gameplay_board, 3) == true)
        return true;

    // if (traverse_diagonal_left_to_right_define_c_based_on_a(gameplay_board, 3) == true)
    //     return true;

    // if (traverse_diagonal_right_to_left_define_c_based_on_a(gameplay_board, 3) == true)
    //     return true;


    return false;

}

void fill_gameplay_board_holes()
{

    bool holes_exist = true;

    while (holes_exist)
    {

        holes_exist = false;

        for (int x = 0; x < gameplay_board->width; x++)
        {

            for (int y = gameplay_board->height - 1; y > 0; y--)
            {

                if (get_gps_board_a(gameplay_board, x, y) < 0)
                {

                    if (get_gps_board_a(gameplay_board, x, y - 1) >= 0)
                    {

                        set_gps_board_a(gameplay_board, x, y, get_gps_board_a(gameplay_board, x, y - 1));

                        set_gps_board_b(gameplay_board, x, y, get_gps_board_b(gameplay_board, x, y - 1));

                        set_gps_board_b(gameplay_board, x, y - 1, (SDL_FPoint){ x, y - 1 });

                        set_gps_board_a(gameplay_board, x, y - 1, -1);

                        holes_exist = true;

                    }

                }

            }

        }

    }

}
