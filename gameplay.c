#include "gameplay.h"

gps_assets_t *gameplay_assets = NULL;


gps_board_t  *gameplay_board  = NULL;


int gameplay_next_pieces_board_x_ofset = 0;

int gameplay_next_pieces_board_y_ofset = 0;

gps_board_t  *gameplay_next_pieces_board = NULL;


int x = 0;

int y = 0;


bool render_gameplay_board();

int render_gameplay_next_pieces_board();

void fill_gameplay_board_holes();

void render_cursors();

void randomize_next_pieces_board(int range)
{

    gameplay_next_pieces_board = create_gps_board(1, 3);

    clear_gps_board_b(gameplay_next_pieces_board);

    srand(time(NULL));

    for (int y = 0; y < gameplay_next_pieces_board->height; y++)
    {
    
        for (int x = 0; x < gameplay_next_pieces_board->width; x++)
        {
    
            int value = rand() % range;
    
            set_gps_board_a(gameplay_next_pieces_board, x, y, value);
    
        }
    
    }

}

/*Temp: */
    float test_spr_tim = 1.0f;


SDL_FPoint lerp_threshold(SDL_FPoint start_value, SDL_FPoint target_value, float ratio, float threshold)
{

    SDL_FPoint interpolated_value;

    float dx = target_value.x - start_value.x;
    float dy = target_value.y - start_value.y;

    interpolated_value.x = start_value.x + ratio * dx;
    interpolated_value.y = start_value.y + ratio * dy;

    if (fabsf(dx) <= threshold) {
        interpolated_value.x = target_value.x;
    }

    if (fabsf(dy) <= threshold) {
        interpolated_value.y = target_value.y;
    }

    return interpolated_value;

}

int start_gameplay(gps_assets_t *assets)
{

    /*TODO: */
        gameplay_assets = assets;


    gameplay_board = create_gps_board(6, 13);

    if (gameplay_board == NULL)
    {

        /*TODO: */

        return 2;

    }

    clear_gps_board_a(gameplay_board);

    clear_gps_board_b(gameplay_board);

    clear_gps_board_c(gameplay_board);


    /*Temp: */

        gameplay_next_pieces_board = create_gps_board(1, 3);

        clear_gps_board_b(gameplay_next_pieces_board);

        srand(time(NULL));

        for (int y = 0; y < gameplay_board->height; y++)
        {

            for (int x = 0; x < gameplay_board->width; x++)
            {

                set_gps_board_a(gameplay_board, x, y, (rand() % (gameplay_assets->format_list_size - 0)) + 0);

            }

        }
    
        for (int y = 0; y < gameplay_next_pieces_board->height; y++)
        {

            for (int x = 0; x < gameplay_next_pieces_board->width; x++)
            {

                set_gps_board_a(gameplay_next_pieces_board, x, y, (rand() % (gameplay_assets->format_list_size - 0)) + 0);

            }

        }
    
    return 0;

}


int update_gameplay(float dt)
{

    if (gameplay_next_pieces_board != NULL) destroy_gps_board(gameplay_next_pieces_board);

    randomize_next_pieces_board(5);

    if (kb_state[SDL_SCANCODE_D] && x < gameplay_board->width - 1)
    {

        x++;

    }

    if (kb_state[SDL_SCANCODE_A] && x > 0)
    {

        x--;

    }

    if (kb_state[SDL_SCANCODE_S] && y < gameplay_board->height - 1)
    {

        y++;

    }

    if (kb_state[SDL_SCANCODE_W] && y > 0)
    {

        y--;

    }

    bool bb = true;

    for (int y = 0; y < gameplay_board->height; y++)
    {

        for (int x = 0; x < gameplay_board->width; x++)
        {

            if (get_gps_board_b(gameplay_board, x, y).y != y)
            {

                bb = false;

                set_gps_board_b(gameplay_board, x, y, lerp_threshold(get_gps_board_b(gameplay_board, x, y), (SDL_FPoint){ x, y }, 5 * dt, 0.01f));
         
            }

        }
    
    }

    if (bb)
    {

        clear_gps_board_c(gameplay_board);

        if (traverse_left_to_right_define_c_based_on_a(gameplay_board, 3) == true)
            goto remove;
        
        clear_gps_board_c(gameplay_board);

        if (traverse_top_to_bottom_define_c_based_on_a(gameplay_board, 3) == true)
            goto remove;

        clear_gps_board_c(gameplay_board);

        if (traverse_diagonal_left_to_right_define_c_based_on_a(gameplay_board, 3) == true)
            goto remove;

remove:
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

    update_sprite_anim(gameplay_assets->background_canvas, dt);

    return 0;

}


void print_sdl_rect(SDL_Rect rect)
{
    printf("X: %d, Y: %d, Width: %d, Height: %d\n", rect.x, rect.y, rect.w, rect.h);
}

int render_gameplay(float dt)
{

    int output_value = 0x0;


    if (SDL_FillRect(rendering_surface, &rendering_surface_rect, SDL_MapRGBA(rendering_surface->format, 0, 0, 0, 255)) != 0)
    {

        output_value     |= 0b00000001;

    }


    if (gameplay_assets->background_canvas != NULL)
    {

        SDL_Rect background_canvas_destination_rectangle = gameplay_assets->background_canvas->spr->destination_rectangle;
        
        if (SDL_BlitScaled(gameplay_assets->background_canvas->spr->surface
                        , &gameplay_assets->background_canvas->spr->source_rectangle
                        ,  rendering_surface
                        , &background_canvas_destination_rectangle) != 0)
        {

            output_value |= 0b00000010;

#ifndef NDEBUG

            fprintf(stderr, "The background_canvas reeds cannot be rendered, %s.\n", SDL_GetError());

#endif

        }

    }
    else
    {

        output_value     |= 0b00000100;

    }


    /*Todo: temps ?*/
        render_gameplay_board();

        render_gameplay_next_pieces_board();

        render_cursors();


    return output_value;

}


int late_update_gameplay(float dt)
{



    return 0;

}


void quit_gameplay(void)
{ 

    if (gameplay_board             != NULL) destroy_gps_board(gameplay_board);

    if (gameplay_next_pieces_board != NULL) destroy_gps_board(gameplay_next_pieces_board);

    /*Todo: */

    return;

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

bool render_gameplay_board()
{

    if (gameplay_board != NULL)
    {

        /*Temp: */
            int of_set_x = (rendering_surface->w * 0.5f) - (GPS_FORMAT_WIDTH  * gameplay_board->width ) * 0.5f;

            int of_set_y = (rendering_surface->h * 0.5f) - (GPS_FORMAT_HEIGHT * gameplay_board->height) * 0.5f;

        for (int y = 0; y < gameplay_board->height; y++)
        {

            for (int x = 0; x < gameplay_board->width; x++)
            {

                int board_cell_type = get_gps_board_a(gameplay_board, x, y);

                if (board_cell_type != GPS_BOARD_CLEANING_A_VALUE)
                {

                    sprite_t  *board_cell_type_sprite   = gameplay_assets->format_list[board_cell_type]->spr->spr;

                    SDL_FPoint board_cell_type_position = get_gps_board_b(gameplay_board, x, y);

                    board_cell_type_sprite->destination_rectangle.x = of_set_x + (board_cell_type_position.x * board_cell_type_sprite->destination_rectangle.w);
                    board_cell_type_sprite->destination_rectangle.y = of_set_y + (board_cell_type_position.y * board_cell_type_sprite->destination_rectangle.h);

                    SDL_BlitScaled(board_cell_type_sprite->surface, NULL, rendering_surface, &board_cell_type_sprite->destination_rectangle);

                }

            }

        }

        return true;

    }

    return false;

}

int render_gameplay_next_pieces_board()
{

    if (gameplay_next_pieces_board != NULL)
    {

        /*Temp: */


        for (int y = 0; y < gameplay_next_pieces_board->height; y++)
        {

            for (int x = 0; x < gameplay_next_pieces_board->width; x++)
            {

                int board_cell_type = get_gps_board_a(gameplay_next_pieces_board, x, y);

                if (board_cell_type != GPS_BOARD_CLEANING_A_VALUE)
                {

                    sprite_t *board_cell_type_sprite   = gameplay_assets->format_list[board_cell_type]->spr->spr;

                    SDL_FPoint board_cell_type_position = get_gps_board_b(gameplay_next_pieces_board, x, y);

                    board_cell_type_sprite->destination_rectangle.x = board_cell_type_position.x * board_cell_type_sprite->destination_rectangle.w;
                    board_cell_type_sprite->destination_rectangle.y = board_cell_type_position.y * board_cell_type_sprite->destination_rectangle.h;

                    SDL_BlitScaled(board_cell_type_sprite->surface, NULL, rendering_surface, &board_cell_type_sprite->destination_rectangle);

                }

            }

        }

        return 1;

    }
    
    return 0;

}

void render_cursors()
{

    if (gameplay_assets->x_cursor != NULL)
    {

        gameplay_assets->x_cursor->destination_rectangle.y = 59;

        gameplay_assets->x_cursor->destination_rectangle.x = 272 + gameplay_assets->x_cursor->destination_rectangle.w * x;

        // printf("%d\n", x);

        SDL_BlitScaled(gameplay_assets->x_cursor->surface, NULL, rendering_surface, &gameplay_assets->x_cursor->destination_rectangle);

    }

    if (gameplay_assets->y_cursor != NULL)
    {

        gameplay_assets->y_cursor->destination_rectangle.x = 272 - 17;

        gameplay_assets->y_cursor->destination_rectangle.y = 59 + 1 + 16 + gameplay_assets->y_cursor->destination_rectangle.w * y;

        // printf("%d\n", y);

        SDL_BlitScaled(gameplay_assets->y_cursor->surface, NULL, rendering_surface, &gameplay_assets->y_cursor->destination_rectangle);

    }

    if (gameplay_assets->in_cursor != NULL)
    {
        
        gameplay_assets->in_cursor->destination_rectangle.x = (rendering_surface->w * 0.5f) - (GPS_FORMAT_WIDTH  * gameplay_board->width ) * 0.5f + (GPS_FORMAT_WIDTH * x);

        gameplay_assets->in_cursor->destination_rectangle.y = (rendering_surface->h * 0.5f) - (GPS_FORMAT_HEIGHT * gameplay_board->height) * 0.5f + (GPS_FORMAT_WIDTH * y);

        SDL_BlitScaled(gameplay_assets->in_cursor->surface, NULL, rendering_surface, &gameplay_assets->in_cursor->destination_rectangle);

    }

}
