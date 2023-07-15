#include <window.h>


Uint32      window_flags = 0x00;

SDL_Rect    window_rect  = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360 };

SDL_Window *window       = NULL;


bool setup_window            (const char *title, Uint32 flags)
{

    if ((window = SDL_CreateWindow(title, window_rect.x, window_rect.y, window_rect.w, window_rect.h, flags)) == NULL)
    {

        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());

        return false;

    }

    return true;

}

void update_window_attributes()
{

    window_flags = SDL_GetWindowFlags(window);
    
    SDL_GetWindowSize                (window, &window_rect.w, &window_rect.h);

    SDL_GetWindowPosition            (window, &window_rect.x, &window_rect.y);

    return;

}
