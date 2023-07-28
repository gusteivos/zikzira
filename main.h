
#ifndef MAIN_H
#define MAIN_H

    #include <math.h>

    #ifdef _WIN32

        #include <direct.h>
        #include <windows.h>
    
    #else

        #ifndef __ANDROID__
    
            #include <unistd.h>
            #include <limits.h>
        
            #ifndef PATH_MAX
            
                #define PATH_MAX 4096
            
            #endif

            #define MAX_PATH PATH_MAX

        #endif

    #endif

    #include "gameloop.h"
    #include "input.h"
    #include "window.h"


    #define WINDOW_TITLE "by gusteivos gp."

    #define GAME_NAME "zikzira" 

    extern void render_surface_in_renderer(SDL_Surface *surface_, SDL_Renderer *renderer_);

    extern void main_try_render(SDL_Window *window_);

#endif
