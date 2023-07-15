
#ifndef RENDERING_H
#define RENDERING_H

    #ifdef __ANDROID__
    
        #include <SDL.h>

    #else

        #include <SDL2/SDL.h>

    #endif


    #include <stdbool.h>
    #include <stdio.h>


    extern SDL_mutex *renderer_mutex;

    extern bool       renderer_auto_resize;

    extern SDL_mutex *rendering_surface_mutex;


    extern SDL_Rect      renderer_rect;

    extern SDL_Renderer *renderer;


    extern Uint32       rendering_surface_format;

    extern SDL_Rect     rendering_surface_rect;

    extern SDL_Surface *rendering_surface;


    extern bool setup_renderer(SDL_Window *, int, Uint32);
    
    extern void update_renderer_attributes(void);

    extern void quit_renderer(void);

#endif
