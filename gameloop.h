
#ifndef GAMELOOP_H
#define GAMELOOP_H

    #include "assets.h"

    #include <gameplay.h>
    

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
