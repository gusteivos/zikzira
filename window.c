#include <window.h>


bool window_is_open              = false;

bool window_handler_ignore_mouse = false;


Uint32   window_flags = 0x00;

SDL_Rect window_rect  = WINDOW_RECT_DEFAULT_VALUE;

SDL_Rect window_min_rect = { -1, -1, 320, 180 };

SDL_Rect window_max_rect = { -1, -1, 640, 360 };


SDL_Window   *window = NULL;

SDL_SysWMinfo window_sysinfo;


bool setup_window(const char *title, Uint32 flags)
{

    if ((window = SDL_CreateWindow(title, window_rect.x, window_rect.y, window_rect.w, window_rect.h, flags)) == NULL)
    {

        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());

        return false;

    }

    window_is_open = true;


    SDL_VERSION(&window_sysinfo.version);

    if (SDL_GetWindowWMInfo(window, &window_sysinfo) == SDL_FALSE)
    {

        fprintf(stderr, "Failed to get sysinfo from window: %s\n", SDL_GetError());

        return false;

    }


    return true;

}


void update_window_attributes()
{

    window_flags = SDL_GetWindowFlags(window);

    SDL_GetWindowSize    (window, &window_rect.w, &window_rect.h);

    SDL_GetWindowPosition(window, &window_rect.x, &window_rect.y);


    return;

}

void handle_window(SDL_WindowEvent *window_event)
{

    switch (window_event->event)
    {

    case SDL_WINDOWEVENT_RESIZED:

        if (window_rect.w < window_min_rect.w)
        {

            if (window_rect.x > mouse_global_point.x && !window_handler_ignore_mouse)
            {

                SDL_SetWindowPosition(window, window_rect.x -= (window_min_rect.w - window_rect.w), window_rect.y);

            }


            window_rect.w = window_min_rect.w;

            SDL_SetWindowSize(window, window_min_rect.w, window_rect.h);

        }


        if (window_rect.h < window_min_rect.h)
        {

            if (window_rect.y > mouse_global_point.y && !window_handler_ignore_mouse)
            {

                SDL_SetWindowPosition(window, window_rect.x, window_rect.y -= (window_min_rect.h - window_rect.h));

            }


            window_rect.h = window_min_rect.h;

            SDL_SetWindowSize(window, window_rect.w, window_min_rect.h);

        }


        update_mouse();

        if (window_rect.w > window_max_rect.w)
        {

            if (mouse_global_point.x > window_rect.x + window_rect.w && !window_handler_ignore_mouse)
            {

                SDL_SetWindowPosition(window, window_rect.x += (window_rect.w - window_max_rect.w), window_rect.y);

            }


            window_rect.w = window_max_rect.w;

            SDL_SetWindowSize(window, window_max_rect.w, window_rect.h);

        }


        if (window_rect.h > window_max_rect.h)
        {

            if (mouse_global_point.y > window_rect.y + window_rect.h && !window_handler_ignore_mouse)
            {

                SDL_SetWindowPosition(window, window_rect.x, window_rect.y += (window_rect.h - window_max_rect.h));

            }


            window_rect.h = window_max_rect.h;

            SDL_SetWindowSize(window, window_rect.w, window_max_rect.h);

        }


        break;

    case SDL_WINDOWEVENT_MOVED:

        window_rect.x = window_event->data1;

        window_rect.y = window_event->data2;

        break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:

        window_rect.w = window_event->data1;

        window_rect.h = window_event->data2;

        break;

    case SDL_WINDOWEVENT_MINIMIZED:



        break;

    case SDL_WINDOWEVENT_MAXIMIZED:



        break;

    case SDL_WINDOWEVENT_CLOSE:
        
        window_is_open = false;

        break;

    default:

#ifndef NDEBUG

        printf("unhandled window event: %d\n", window_event->event);

#endif

        break;

    }


    return;

}


void quit_window()
{

    SDL_DestroyWindow(window);


    window_is_open = false;


    window_flags = 0x00;

    window_rect = (SDL_Rect)WINDOW_RECT_DEFAULT_VALUE;


    return;

}
