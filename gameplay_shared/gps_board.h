
#ifndef GPS_BOARD_H
#define GPS_BOARD_H

    #ifdef __ANDROID__
    
        #include <SDL_rect.h>

    #else

        #include <SDL2/SDL_rect.h>

    #endif

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>


    #define GPS_BOARD_CLEANING_A_VALUE -1

    
    typedef struct gps_board
    {
        
        int        *a;

        SDL_FPoint *b;

        bool       *c;
        
        int width ;
        
        int height;

    } gps_board_t;
    

    extern gps_board_t *create_gps_board(int width, int height);

    
    extern void clear_gps_board_a_value(gps_board_t *board, int value);

    extern void set_gps_board_a        (gps_board_t *board, int x, int y, int value);

    extern int  get_gps_board_a        (gps_board_t *board, int x, int y);
    

    extern void       set_gps_board_position_in_b_values(gps_board_t *board);
    
    extern void       set_gps_board_b                   (gps_board_t *board, int x, int y, SDL_FPoint value);

    extern SDL_FPoint get_gps_board_b                   (gps_board_t *board, int x, int y);

    
    extern void clear_gps_board_c(gps_board_t *board);

    extern void set_gps_board_c  (gps_board_t *board, int x, int y, bool value);

    extern bool get_gps_board_c  (gps_board_t *board, int x, int y);


    extern bool traverse_left_to_right_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values);

    extern bool traverse_top_to_bottom_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values);
    
    extern bool traverse_diagonal_left_to_right_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values);

    extern bool traverse_diagonal_right_to_left_define_c_based_on_a(gps_board_t *board, int minimum_number_equal_values);


    extern void destroy_gps_board(gps_board_t *board);


    #define clear_gps_board_a(board) clear_gps_board_a_value           (board, GPS_BOARD_CLEANING_A_VALUE)
    
    #define clear_gps_board_b(board) set_gps_board_position_in_b_values(board)

#endif
