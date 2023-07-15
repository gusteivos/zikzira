#include "renderer.h"


SDL_mutex *renderer_mutex = NULL;

bool       renderer_auto_resize = false;

SDL_mutex *rendering_surface_mutex = NULL;


SDL_Rect      renderer_rect = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 180 };

SDL_Renderer *renderer      = NULL;


Uint32       rendering_surface_format = SDL_PIXELFORMAT_RGBA32;

SDL_Rect     rendering_surface_rect   = { 0, 0, 640, 360 };

SDL_Surface *rendering_surface        = NULL;


bool setup_renderer(SDL_Window *window, int index, Uint32 flags)
{

    renderer_mutex          = SDL_CreateMutex();

    if (renderer_mutex          == NULL)
    {

        fprintf(stderr, "Error creating mutex to protect the renderer: %s\n", SDL_GetError());

        return false;

    }

    
    rendering_surface_mutex = SDL_CreateMutex();

    if (rendering_surface_mutex == NULL)
    {
    


        return false;
    
    }


    renderer = SDL_CreateRenderer(window, index, flags);

    if (renderer == NULL)
    {
    
        fprintf(stderr, "Error creating mutex to protect the rendering surface: %s\n", SDL_GetError());
        
        SDL_DestroyMutex(renderer_mutex);


        SDL_DestroyMutex(rendering_surface_mutex);


        return false;
    
    }


    rendering_surface = SDL_CreateRGBSurfaceWithFormat(0, rendering_surface_rect.w, rendering_surface_rect.h, 32, rendering_surface_format);

    if (rendering_surface == NULL)
    {

        fprintf(stderr, "Error creating mutex to protect the rendering surface: %s\n", SDL_GetError());

        return false;

    }


    return true;

}

void update_renderer_attributes()
{

    SDL_Window *window_ = SDL_RenderGetWindow(renderer);

    SDL_GetWindowPosition(window_, &renderer_rect.x, &renderer_rect.y);

    if (renderer_auto_resize)
    {

        SDL_GetWindowSize(window_, &renderer_rect.w, &renderer_rect.h);

    }

    SDL_RenderSetLogicalSize(renderer, renderer_rect.w, renderer_rect.h);

    return;

}

void quit_renderer()
{

    SDL_DestroyMutex(renderer_mutex);

    renderer_mutex = NULL;


    SDL_DestroyMutex(rendering_surface_mutex);

    rendering_surface_mutex = NULL;

    
    SDL_DestroyRenderer(renderer);
    
    renderer = NULL;


    SDL_FreeSurface(rendering_surface);

    rendering_surface = NULL;

}
