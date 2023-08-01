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


    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);

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


    SDL_SetWindowTitle(window, GAME_NAME);


    /*Temp: */
        SDL_SetRenderDrawColor(renderer, 155, 255, 155, 255);


    SDL_Event event;

    while (gameloop_is_running)
    {

        update_mouse();


        update_window_attributes();

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
                        
                            printf("TODO: SDL_WINDOWEVENT_EXPOSED \n");
                            
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


        if (!gameloop_enable_render_sync_variable || gameloop_can_render == false)
        {

#ifdef GAMELOOP_SYNC_BY_MUTEX  
      
            if (SDL_TryLockMutex(renderer_mutex) == 0)

#endif
        
#ifdef GAMELOOP_SYNC_BY_SPINLOCK  
      
            if (SDL_AtomicTryLock(&renderer_spin_lock) == SDL_TRUE)

#endif

            {

#ifdef GAMELOOP_SYNC_BY_MUTEX  
      
                // SDL_LockMutex(renderer_mutex);

#endif
                
#ifdef GAMELOOP_SYNC_BY_SPINLOCK
      
                // SDL_AtomicLock(&renderer_spin_lock);

#endif

                SDL_RenderClear(renderer);

                render_surface_in_renderer(rendering_surface, renderer);


                gameloop_can_render = true;

                
#ifdef GAMELOOP_SYNC_BY_MUTEX  
      
                SDL_UnlockMutex(renderer_mutex);

#endif

#ifdef GAMELOOP_SYNC_BY_SPINLOCK
      
                SDL_AtomicUnlock(&renderer_spin_lock);

#endif


            }

            SDL_RenderPresent(renderer);

        }


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

void render_surface_in_renderer(SDL_Surface *surface_, SDL_Renderer *renderer_)
{

    if (surface_ != NULL && renderer_ != NULL)
    {

        SDL_Texture *texture_from_surface_ = SDL_CreateTextureFromSurface(renderer_, surface_);

        if (texture_from_surface_ == NULL)
        {

            printf("Failed to create texture_from_surface_: %s\n", SDL_GetError());

        }
        else
        {

            SDL_RenderCopy(renderer_, texture_from_surface_, NULL, NULL);

            SDL_RenderPresent(renderer_);

            SDL_DestroyTexture(texture_from_surface_);

        }

    }
    else
    {

        fprintf(stderr, "TODO: ");

    }


    return;

}


#ifndef __ANDROID__

static void set_working_directory_to_binary_directory()
{

    char *current_binary_directory = SDL_GetBasePath();

    if (current_binary_directory == NULL)
    {

        fprintf(stderr, "TODO.\n");
  
        return;

    }


    if (chdir(current_binary_directory) != 0)
    {

        fprintf(stderr, "Failed to set working directory.\n");

    }

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
