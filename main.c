#include "main.h"


#ifndef __ANDROID__

static void set_working_directory_to_binary_directory();

#endif


int main(int argc, char *argv[])
{

#ifndef __ANDROID__

    set_working_directory_to_binary_directory();

#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0)
    {
    
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());

        return 1;

    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Mix_Init(MIX_INIT_MP3);

        /*temp: */
            gameloop_is_running = true;

    if (setup_window(WINDOW_TITLE, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN) == false)
    {
        
        Mix_Quit();
        
        IMG_Quit();

        SDL_Quit();

        return 1;

    }

    if (setup_renderer(window, -1, SDL_RENDERER_ACCELERATED)                == false)
    {

        SDL_DestroyWindow(window);

        Mix_Quit();
        
        IMG_Quit();

        SDL_Quit();

        return 1;

    }

    setup_keyboard();

    if ((gameloop_thread = SDL_CreateThread(gameloop_thread_routine, "gameloop thread", NULL)) == NULL)
    {
        
        fprintf(stderr, "Failed to create gameloop thread: %s\n", SDL_GetError());

        quit_renderer();

        SDL_DestroyWindow(window);

        Mix_Quit();
        
        IMG_Quit();

        SDL_Quit();

        return 1;

    }

    SDL_Event event;

    while (gameloop_is_running)
    {

        update_window_attributes();

        update_mouse();

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            
            case SDL_QUIT:

                gameloop_is_running = false;

                break;

            case SDL_WINDOWEVENT:

                if (event.window.windowID == SDL_GetWindowID(window))
                {

                    switch (event.window.event)
                    {

                    case SDL_WINDOWEVENT_EXPOSED:
                        
                        main_try_render(window);
                        
                        break;

                    case SDL_WINDOWEVENT_RESIZED:

                        window_rect.w = event.window.data1;
                        
                        window_rect.h = event.window.data2;

                        break;

                    case SDL_WINDOWEVENT_MOVED:
                        
                        window_rect.x = event.window.data1;
                        
                        window_rect.y = event.window.data2;

                        break;

                    default:
                        break;

                    }

                }

                break;

            default:
                break;

            }

        update_renderer_attributes();

        main_try_render           (window);

        SDL_Delay(1);

    }

    SDL_WaitThread(gameloop_thread, NULL);

    quit_renderer();

    SDL_DestroyWindow(window);

    IMG_Quit();

    Mix_Quit();
    
    SDL_Quit();
    
    return 0;

}

void main_try_render(SDL_Window *window_)
{

    if (SDL_TryLockMutex(renderer_mutex) == 0)
    {

        // if (SDL_TryLockMutex(rendering_surface_mutex) == 0)
        {

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, rendering_surface);

            if (texture == NULL)
                printf("Failed to create texture: %s\n", SDL_GetError());
            else
            {

                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, texture, NULL, NULL);

                SDL_RenderPresent(renderer);

                SDL_DestroyTexture(texture);

            }

            // SDL_UnlockMutex(rendering_surface_mutex);

        }

        SDL_UnlockMutex(renderer_mutex);

    }

    return;

}


#ifndef __ANDROID__

static void set_working_directory_to_binary_directory()
{

    char current_binary_directory[MAX_PATH];

#ifdef _WIN32

    GetModuleFileName(NULL, current_binary_directory, sizeof(current_binary_directory));

    char *last_backslash = strrchr(current_binary_directory, '\\');

    if (last_backslash != NULL) *last_backslash = '\0';

#else
    
    char executable_path[PATH_MAX];

    ssize_t executable_path_length = readlink("/proc/self/exe", executable_path, sizeof(executable_path) - 1);

    if (executable_path_length != -1)
    {

        executable_path[executable_path_length] = '\0';

        char *last_slash = strrchr(executable_path, '/');

        if (last_slash != NULL) *last_slash = '\0';

    }

    realpath(executable_path, current_binary_directory);

#endif

    if (chdir(current_binary_directory) != 0) fprintf(stderr, "Failed to set working directory\n");

    return;

}

#endif


#if defined(_WIN32) && !defined(NDEBUG)

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);

    return main(__argc, __argv);

}

#endif
