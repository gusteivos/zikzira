#include "gps_board.h"


gps_board_t *create_gps_board(int width, int height)
{

    if (width <= 0 || height <= 0)
    {

        fprintf(stderr, "");

        return NULL;

    }


    gps_board_t *new_board = (gps_board_t *)malloc(sizeof(gps_board_t));

    if (new_board == NULL)
    {

        fprintf(stderr, "");

        return NULL;

    }


    new_board->width  = width;

    new_board->height = height;


    new_board->a = (int *)malloc(sizeof(int) * (new_board->width * new_board->height));

    if (new_board->a == NULL)
    {

        fprintf(stderr, "");

        free(new_board);

        return NULL;

    }


    new_board->b = (SDL_FPoint *)malloc(sizeof(SDL_FPoint) * (new_board->width * new_board->height));

    if (new_board->b == NULL)
    {

        fprintf(stderr, "");

        free(new_board->a);

        free(new_board);

        return NULL;

    }


    new_board->c = (bool *)malloc(sizeof(bool) * (new_board->width * new_board->height));

    if (new_board->c == NULL)
    {

        fprintf(stderr, "");

        free(new_board->b);

        free(new_board->a);

        free(new_board);

        return NULL;

    }


    return new_board;

}

    
void clear_gps_board_a_value(gps_board_t *board, int value)
{

    if (board == NULL)
    {
    
        fprintf(stderr, "");

        return;

    }


    long int q = board->width * board->height;

    for (long int w = 0; w < q; w++)
    {

        board->a[w] = value;

    }


    return;

}

void set_gps_board_a        (gps_board_t *board, int x, int y, int value)
{

    if (board == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {

        fprintf(stderr, "todo: \n");

        return;

    }


    long int index = (y * board->width) + x;

    board->a[index] = value;


    return;

}

int  get_gps_board_a        (gps_board_t *board, int x, int y)
{

    if (board == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {

        fprintf(stderr, "");

        return GPS_BOARD_CLEANING_A_VALUE;

    }


    long int index = (y * board->width) + x;

    return board->a[index];

}


void       set_gps_board_position_in_b_values(gps_board_t *board)
{

    if (board == NULL)
    {

        fprintf(stderr, "");

        return;

    }


    for (int y = 0; y < board->height; y++)
    {

        for (int x = 0; x < board->width; x++)
        {

            long int index = (y * board->width) + x;

            board->b[index] = (SDL_FPoint){ x, y };

        }

    }

    return;

}

void       set_gps_board_b                   (gps_board_t *board, int x, int y, SDL_FPoint value)
{

    if (board == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {

        fprintf(stderr, "");

        return;

    }


    long int index = (y * board->width) + x;

    board->b[index] = value;


    return;

}

SDL_FPoint get_gps_board_b(gps_board_t *board, int x, int y)
{

    if (board == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {

        fprintf(stderr, "");

        return (SDL_FPoint){ x, y };

    }


    long int index = (y * board->width) + x;

    return board->b[index];

}


void clear_gps_board_c(gps_board_t *board)
{

    if (board == NULL || board->c == NULL)
    {

        fprintf(stderr, "Invalid board or board data.\n");

        return;

    }


    int size = board->width * board->height;

    for (int i = 0; i < size; i++)
    {

        board->c[i] = false;

    }

}

void set_gps_board_c(gps_board_t *board, int x, int y, bool value)
{

    
    if (board == NULL || board->c == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {
    
        fprintf(stderr, "Invalid board or board data.\n");
    
        return;
    
    }

    int index = (y * board->width) + x;

    board->c[index] = value;

}

bool get_gps_board_c(gps_board_t *board, int x, int y)
{
    
    if (board == NULL || board->c == NULL || x < 0 || x >= board->width || y < 0 || y >= board->height)
    {
    
        fprintf(stderr, "Invalid board or board data.\n");
    
        return false;
    
    }

    int index = (y * board->width) + x;

    return board->c[index];

}


bool traverse_left_to_right_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values)
{

    if (board == NULL || board->a == NULL || board->c == NULL)
    {
    
        fprintf(stderr, "Invalid board or board data.\n");
    
        return false;
    
    }


    bool defined_c = false;

    for (int y = 0; y < board->height; y++)
    {

        int previous_value = -1;

        unsigned int count = 0;

        for (int x = 0; x < board->width; x++)
        {

            int cell = get_gps_board_a(board, x, y);

            if (cell == previous_value && cell != GPS_BOARD_CLEANING_A_VALUE)
            {
            
                count++;
            
            }
            else
            {
            
                if (count >= minimum_number_equal_values)
                {
            
                    for (unsigned int i = x - count; i < x; i++)
                    {

                        set_gps_board_c(board, i, y, true);

                    }

                    defined_c = true;

                }

                count = 1;

                previous_value = cell;

            }

        }

        if (count >= minimum_number_equal_values)
        {

            for (unsigned int i = board->width - count; i < board->width; i++)
            {

                set_gps_board_c(board, i, y, true);

            }

            defined_c = true;

        }

    }

    return defined_c;
}

/*Consertar: */
    bool traverse_top_to_bottom_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values)
    {
        if (board == NULL || board->a == NULL || board->c == NULL)
        {
            fprintf(stderr, "Invalid board or board data.\n");
            return false;
        }

        bool defined_c = false;

        for (int x = 0; x < board->width; x++)
        {
            int previous_value = -1;
            unsigned int count = 0;

            for (int y = 0; y < board->height; y++)
            {
                int cell = get_gps_board_a(board, x, y);

                if (cell == previous_value && cell != GPS_BOARD_CLEANING_A_VALUE)
                {
                    count++;
                }
                else
                {

                    if (count >= minimum_number_equal_values)
                    {

                        for (unsigned int i = y - count; i < y; i++)
                        {
                    
                            set_gps_board_c(board, x, i, true);
                    
                        }
                    
                        defined_c = true;
                    
                    }

                    count = 1;
                    previous_value = cell;
                }
            }

            if (count >= minimum_number_equal_values)
            {
                for (unsigned int i = board->height - count; i < board->height; i++)
                {
                    set_gps_board_c(board, x, i, true);
                }
                defined_c = true;
            }
        }

        return defined_c;
    }

    bool traverse_diagonal_left_to_right_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values)
    {
        if (board == NULL || board->a == NULL || board->c == NULL)
        {
            fprintf(stderr, "Invalid board or board data.\n");
            return false;
        }

        bool defined_c = false;

        // Percorrer as diagonais começando pelas diagonais superiores
        for (int diagonal_start_x = 0; diagonal_start_x < board->width; diagonal_start_x++)
        {
            for (int diagonal_start_y = 0; diagonal_start_y < board->height; diagonal_start_y++)
            {
                int previous_value = -1;
                unsigned int count = 0;

                // Percorrer a diagonal
                for (int i = 0; i < board->width && (i + diagonal_start_x) < board->width && (i + diagonal_start_y) < board->height; i++)
                {
                    int x = diagonal_start_x + i;
                    int y = diagonal_start_y + i;

                    int cell = get_gps_board_a(board, x, y);

                    if (cell == previous_value && cell != GPS_BOARD_CLEANING_A_VALUE)
                    {
                        count++;
                    }
                    else
                    {
                        if (count >= minimum_number_equal_values)
                        {
                            for (unsigned int j = i - count; j < i; j++)
                            {
                                int x_to_set = diagonal_start_x + j;
                                int y_to_set = diagonal_start_y + j;
                                set_gps_board_c(board, x_to_set, y_to_set, true);
                            }
                            defined_c = true;
                        }

                        count = 1;
                        previous_value = cell;
                    }
                }

                if (count >= minimum_number_equal_values)
                {
                    for (unsigned int j = board->width - diagonal_start_x - count; j < board->width - diagonal_start_x; j++)
                    {
                        int x_to_set = diagonal_start_x + j;
                        int y_to_set = diagonal_start_y + j;
                        set_gps_board_c(board, x_to_set, y_to_set, true);
                    }
                    defined_c = true;
                }
            }
        }

        return defined_c;
    }

bool traverse_diagonal_right_to_left_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values)
{
    if (board == NULL || board->a == NULL || board->c == NULL)
    {
        fprintf(stderr, "Invalid board or board data.\n");
        return false;
    }

    bool defined_c = false;

    // Percorrer as diagonais começando pelas diagonais superiores
    for (int diagonal_start_x = board->width - 1; diagonal_start_x >= 0; diagonal_start_x--)
    {
        for (int diagonal_start_y = 0; diagonal_start_y < board->height; diagonal_start_y++)
        {
            int previous_value = -1;
            unsigned int count = 0;

            // Percorrer a diagonal
            for (int i = 0; i < board->width && (diagonal_start_x - i) >= 0 && (i + diagonal_start_y) < board->height; i++)
            {
                int x = diagonal_start_x - i;
                int y = diagonal_start_y + i;

                int cell = get_gps_board_a(board, x, y);

                if (cell == previous_value && cell != GPS_BOARD_CLEANING_A_VALUE)
                {
                    count++;
                }
                else
                {
                    if (count >= minimum_number_equal_values)
                    {
                        for (unsigned int j = i - count; j < i; j++)
                        {
                            int x_to_set = diagonal_start_x - j;
                            int y_to_set = diagonal_start_y + j;
                            set_gps_board_c(board, x_to_set, y_to_set, true);
                        }
                        defined_c = true;
                    }

                    count = 1;
                    previous_value = cell;
                }
            }

            if (count >= minimum_number_equal_values)
            {
                for (unsigned int j = board->width - diagonal_start_x - count; j < board->width - diagonal_start_x; j++)
                {
                    int x_to_set = diagonal_start_x - j;
                    int y_to_set = diagonal_start_y + j;
                    set_gps_board_c(board, x_to_set, y_to_set, true);
                }
                defined_c = true;
            }
        }
    }

    return defined_c;
}


void destroy_gps_board(gps_board_t *board)
{

    if (board == NULL) return;

    if (board->a != NULL)
    {

        free(board->a);
    
        board->a = NULL;
    
    }

    if (board->b != NULL)
    {
    
        free(board->b);
        
        board->b = NULL;
    
    }

    if (board->c != NULL)
    {

        free(board->c);

        board->c = NULL;

    }

    free(board);
    
}
