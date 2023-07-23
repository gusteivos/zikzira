
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

    #include "input.h"
    #include "music.h"
    #include "renderer.h"
    #include "sound.h"
    #include "window.h"

    #include <gameplay_shared/gps_assets.h>
    #include <gameplay_shared/gps_board.h>

    #include <key_delays.h>

    #include <math.h>
    #include <time.h>


    extern gps_assets_t *gameplay_assets;

    extern gps_board_t  *gameplay_board;


    extern int start_gameplay(gps_assets_t *assets);


    extern int update_gameplay     (float dt);
    
    extern int render_gameplay     (float dt);

    extern int late_update_gameplay(float dt);


    extern void quit_gameplay(void);

#endif
