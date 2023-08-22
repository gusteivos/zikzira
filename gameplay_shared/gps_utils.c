#include "gps_utils.h"


void render_gps_board_with_offset(SDL_Surface *surface, gps_board_t *board, uint16_t off_x, uint16_t off_y, int format_list_length, gps_format_t **format_list, bool scale)
{

    if (!surface || !board || format_list_length <= 0 || !format_list)
    {

        fprintf(stderr, "TODO: \n");

        return;

    }


    for (int y = 0; y < board->height; y++)
        for (int x = 0; x < board->width; x++)
        {

            int cell_type = get_gps_board_a(board, x, y);

            if (cell_type != GPS_BOARD_CLEANING_A_VALUE)
            {

                sprite_t *cell_type_sprite = format_list[(cell_type + 1) % format_list_length]->spr->spr;


                SDL_Rect  cell_type_destination_rectangle = cell_type_sprite->destination_rectangle;

                cell_type_destination_rectangle.x += off_x;

                cell_type_destination_rectangle.y += off_y;

                cell_type_destination_rectangle.x += x * GPS_FORMAT_WIDTH;

                cell_type_destination_rectangle.y += y * GPS_FORMAT_HEIGHT;


                if (scale)
                {

                    SDL_BlitScaled(cell_type_sprite->surface, &cell_type_sprite->source_rectangle, surface, &cell_type_destination_rectangle);

                }
                else
                {

                    SDL_BlitSurface(cell_type_sprite->surface, &cell_type_sprite->source_rectangle, surface, &cell_type_destination_rectangle);

                }

            }

        }


    return;

}


void render_gps_board_with_b_and_offset(SDL_Surface *surface, gps_board_t *board, uint16_t off_x, uint16_t off_y, int format_list_length, gps_format_t **format_list, bool scale)
{

    if (!surface || !board || format_list_length <= 0 || !format_list)
    {

        fprintf(stderr, "TODO: \n");

        return;

    }


    for (int y = 0; y < board->height; y++)
        for (int x = 0; x < board->width; x++)
        {

            int cell_type = get_gps_board_a(board, x, y);

            if (cell_type != GPS_BOARD_CLEANING_A_VALUE)
            {

                sprite_t *cell_type_sprite = format_list[(cell_type + 1) % format_list_length]->spr->spr;


                SDL_FPoint cell_type_sprite_position = get_gps_board_b(board, x, y);


                SDL_Rect  cell_type_destination_rectangle = cell_type_sprite->destination_rectangle;

                cell_type_destination_rectangle.x += off_x;

                cell_type_destination_rectangle.y += off_y;

                cell_type_destination_rectangle.x += cell_type_sprite_position.x * GPS_FORMAT_WIDTH;

                cell_type_destination_rectangle.y += cell_type_sprite_position.y * GPS_FORMAT_HEIGHT;


                if (scale)
                {

                    SDL_BlitScaled(cell_type_sprite->surface, &cell_type_sprite->source_rectangle, surface, &cell_type_destination_rectangle);

                }
                else
                {

                    SDL_BlitSurface(cell_type_sprite->surface, &cell_type_sprite->source_rectangle, surface, &cell_type_destination_rectangle);

                }

            }

        }


    return;

}
