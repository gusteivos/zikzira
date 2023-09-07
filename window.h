
#ifndef WINDOW_H
#define WINDOW_H


    #include <input/mouse.h>


    #ifdef __ANDROID__

        #include <SDL.h>
        #include <SDL_syswm.h>

    #else
    
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_syswm.h>

    #endif


    #include <stdbool.h>
    #include <stdio.h>


    #define WINDOW_RECT_DEFAULT_VALUE { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360 }


    extern bool window_is_open;

    extern bool window_handler_ignore_mouse;


    extern Uint32   window_flags;

    extern SDL_Rect window_rect;

    extern SDL_Rect window_min_rect;

    extern SDL_Rect window_max_rect;


    extern SDL_Window   *window;

    extern SDL_SysWMinfo window_sysinfo;


    extern bool setup_window(const char *title, Uint32 flags);
    

    extern void update_window_attributes(void);

    extern void handle_window(SDL_WindowEvent *window_event);


    extern void quit_window(void);

#endif

