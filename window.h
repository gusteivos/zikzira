
#ifndef WINDOW_H
#define WINDOW_H

    #ifdef __ANDROID__

        #include <SDL.h>

    #else
    
        #include <SDL2/SDL.h>

    #endif


    #include <stdbool.h>
    #include <stdio.h>


    extern Uint32      window_flags;

    extern SDL_Rect    window_rect;

    extern SDL_Window *window;


    extern bool setup_window            (const char *, Uint32);
    

    extern void update_window_attributes(void);

#endif
