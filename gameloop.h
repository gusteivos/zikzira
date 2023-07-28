
#ifndef GAMELOOP_H
#define GAMELOOP_H

    #include "assets.h"

    #include <gameplay/gameplay.h>

    // TODO:
        // enum gameloop_rendering_sync_type
        // {

        //     PER_GAMELOOP_SYNC,
        //     PER_RENDERLOOP_SYNC,
        //     PER_FULL_LOOK_SYNC

        // };


    extern bool   gameloop_is_running;

    extern Sint64 gameloop_target_fps;


    extern SDL_Thread *gameloop_thread;


    extern int gameloop_thread_routine(void *);


    extern void gameloop_start (void);


    extern void gameloop_update     (float dt);
    
    extern void gameloop_render     (float dt);

    extern void gameloop_late_update(float dt);


    extern void gameloop_quit  (void);

#endif
