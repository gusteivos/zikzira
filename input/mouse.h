
#ifndef MOUSE_H
#define MOUSE_H

    #ifdef __ANDROID__

        #include <SDL_mouse.h>
        #include <SDL_rect.h>
    
    #else
    
        #include <SDL2/SDL_mouse.h>
        #include <SDL2/SDL_rect.h>
    
    #endif


    #include <stdbool.h>
    #include <stdio.h>


    extern Uint32    mouse_state;

    extern SDL_Point mouse_point;

    
    extern Uint32    mouse_global_state;

    extern SDL_Point mouse_global_point;

    
    extern Uint32    mouse_relative_state;

    extern SDL_Point mouse_relative_point;

    
    extern void update_mouse(void);

#endif
