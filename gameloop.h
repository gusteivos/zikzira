
#ifndef GAMELOOP_H
#define GAMELOOP_H

    #include "assets.h"

    #include <gameplay/gameplay.h>


    #define GAMELOOP_SYNC_BY_MUTEX

    // #define GAMELOOP_SYNC_BY_SPINLOCK


    extern bool   gameloop_enable_render_sync_variable;

    extern bool   gameloop_is_running;

    extern bool gameloop_can_render;

    extern Sint64 gameloop_target_fps;

    extern SDL_Thread *gameloop_thread;


    extern SDL_SpinLock renderer_spin_lock;


    extern int gameloop_thread_routine(void *);


    extern void gameloop_start (void);


    extern void gameloop_update     (float dt);
    
    extern void gameloop_render     (float dt);

    extern void gameloop_late_update(float dt);


    extern void gameloop_quit  (void);

#endif
