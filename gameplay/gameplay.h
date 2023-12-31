
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

    #include <input/keyboard.h>
    #include <input/keyboard_delay.h>
    #include <input/mouse.h>

    #include <music.h>
    #include <sound.h>

    #include <window.h>
    #include <renderer.h>

    #include <utils.h>

    #include <gameplay_shared/gps_context.h>
    #include <gameplay_shared/gps_utils.h>

    
    extern gps_context_t *gameplay_context;


    extern gps_board_t *gameplay_board;


    extern gps_board_t *gameplay_next_pieces_board;

    extern gps_board_t *gameplay_current_pieces_board;


    extern void reset_gameplay(void);
    

    extern int start_gameplay(gps_context_t *context);


    extern int update_gameplay     (float dt);
    
    extern int render_gameplay     (float dt);

    extern int late_update_gameplay(float dt);


    extern void quit_gameplay(void);


#endif
