#include "gameplay.h"

gps_assets_t *gameplay_assets = NULL;

gps_board_t  *gameplay_board  = NULL;


float test_spr_tim = 1.0f;

sprite_t *can_spr = NULL;


bool render_gameplay_board();

void fill_gameplay_board_holes();


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
        can_spr = load_sprite("C:\\Users\\gc514\\Documentos\\zikzira2\\build\\win32\\bin\\content\\images\\canvas.png");

        srand(time(NULL));

        for (int y = 0; y < 13; y++)
        {

            for (int x = 0; x < 6; x++)
            {

                set_gps_board_a(gameplay_board, x, y, (rand() % (gameplay_assets->format_list_size - 0)) + 0);

            }

        }

    return 0;

}


int update_gameplay(float dt)
{



    return 0;

}

int render_gameplay(float dt)
{

    if (SDL_FillRect(rendering_surface, &rendering_surface_rect, SDL_MapRGBA(rendering_surface->format, 0, 0, 0, 255)) != 0)
    {

        return 1;

    }


    int output_value = 0;

    SDL_BlitSurface(can_spr->surface, &can_spr->source_rectangle, rendering_surface, &can_spr->destination_rectangle);
    
    render_gameplay_board();

    return output_value;

}

int late_update_gameplay(float dt)
{

    return 0;

}


void quit_gameplay(void)
{



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

                        // board_ind[x][y] = board_ind[x][y - 1];

                        set_gps_board_b(gameplay_board, x, y, get_gps_board_b(gameplay_board, x, y - 1));
                
                        // board_ind_pos[x][y] = board_ind_pos[x][y - 1];

                        set_gps_board_b(gameplay_board, x, y - 1, (SDL_FPoint){ x, y - 1 });

                        // board_ind_pos[x][y - 1] = (SDL_FPoint) { x, y - 1 };

                        // board_ind[x][y - 1] = -1;

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

                if (board_cell_type != GPS_CLEANING_A_VALUE)
                {

                    sprite_t  *board_cell_type_sprite   = gameplay_assets->format_list[board_cell_type]->spr;

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
