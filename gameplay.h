
#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

    #include "input.h"
    #include "music.h"
    #include "renderer.h"
    #include "sound.h"
    #include "window.h"

    #include <gameplay_shared/gps_assets.h>
    #include <gameplay_shared/gps_board.h>

    #include <assets.h>

    #include <key_delays.h>

    #include <math.h>
    #include <time.h>


    extern gps_assets_t *gameplay_assets;

    extern gps_board_t  *gameplay_board;


    extern int tstart_gameplay(gps_assets_t *assets);


    extern int tupdate_gameplay     (float dt);
    
    extern int trender_gameplay     (float dt);

    extern int tlate_update_gameplay(float dt);


    extern void tquit_gameplay(void);

#endif
