#include "main.h"

void render_surface_in_renderer(SDL_Surface *surface_, SDL_Renderer *renderer_);


bool init_main()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) != 0)
    {

        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());


        return false;

    }


    int IMG_flags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (IMG_Init(IMG_flags) != IMG_flags)
    {

        fprintf(stderr, "Failed to initialize SDL image: %s\n", IMG_GetError());

        SDL_Quit();


        return false;

    }


    int Mix_flags = MIX_INIT_MP3;

    if (Mix_Init(Mix_flags) != Mix_flags)
    {

        fprintf(stderr, "Failed to initialize SDL mixer: %s\n", Mix_GetError());

        IMG_Quit();

        SDL_Quit();


        return false;

    }


    return true;

}

int main(int argc, char *argv[])
{


    joystick_t *test_joystick = NULL;


    if (init_main())
    {

        /*



        */

            gameloop_is_running = true;


        test_joystick = open_joystick(0);

        if (test_joystick != NULL)
        {

            printf("joy name: %s\n", test_joystick->name);

            printf("joy iid : %d\n", test_joystick->iid);

            char guidString[33];

            SDL_GUIDToString(test_joystick->uid, guidString, sizeof(guidString));

            printf("joy uid : %s\n", guidString);

        }


    }
    else
    {

        fprintf(stderr, "Failed to initialize.\n");


        return 1;

    }


    if (!setup_keyboard())
    {

        fprintf(stderr, "Error when keyboard setup: %s\n", SDL_GetError());


        quit_main(MAIN_QUIT_MIX | MAIN_QUIT_IMG | MAIN_QUIT_SDL);


        return 1;

    }


    if (!setup_window(WINDOW_TITLE, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    {

        fprintf(stderr, "Error when window setup: %s\n", SDL_GetError());


        quit_main(MAIN_QUIT_MIX | MAIN_QUIT_IMG | MAIN_QUIT_SDL |
                  MAIN_QUIT_KEY);


        return 1;

    }


    if (!setup_renderer(window, -1, SDL_RENDERER_ACCELERATED))
    {

        fprintf(stderr, "Error when renderer setup: %s\n", SDL_GetError());


        quit_main(MAIN_QUIT_MIX | MAIN_QUIT_IMG | MAIN_QUIT_SDL |
                  MAIN_QUIT_KEY | MAIN_QUIT_WIN);


        return 1;

    }


    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);

    if ((gameloop_thread = SDL_CreateThread(gameloop_thread_routine, "gameloop thread", NULL)) == NULL)
    {

        fprintf(stderr, "Failed to create gameloop thread: %s\n", SDL_GetError());


        quit_main(MAIN_QUIT_ALL);


        return 1;

    }


    SDL_SetWindowTitle(window, GAME_NAME);


    SDL_Event event;

    while (gameloop_is_running)
    {


        update_joystick_button_states(test_joystick);
        update_joystick_axi_states(test_joystick);

        update_window_attributes();

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {

            case SDL_QUIT:

                gameloop_is_running = false;

                break;

            case SDL_WINDOWEVENT:

                if (event.window.windowID == SDL_GetWindowID(window))
                {

                    handle_window(&event.window);

                }
                else
                {

                    fprintf(stderr, "window with id: %u unhandled. \n", event.window.windowID);

                }

                break;

            default:
                break;

            }

        }


        if (window_is_open)
        {

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

                    // SDL_    rendering_surface

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


            utils_nano_sleep(1000);

        }

    }


    SDL_WaitThread(gameloop_thread, NULL);


    quit_main(MAIN_QUIT_ALL);


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


void quit_main(uint32_t quit)
{

    if (quit | MAIN_QUIT_SDL && !(quit & (MAIN_QUIT_MIX | MAIN_QUIT_IMG | MAIN_QUIT_REN | MAIN_QUIT_WIN | MAIN_QUIT_KEY)))
    {

        quit_renderer();

        quit_window  ();

        quit_keyboard();


        Mix_Quit();

        IMG_Quit();


        SDL_Quit();


        return;

    }


    if (quit | MAIN_QUIT_REN) quit_renderer();

    if (quit | MAIN_QUIT_WIN) quit_window  ();

    if (quit | MAIN_QUIT_KEY) quit_keyboard();


    if (quit | MAIN_QUIT_MIX) Mix_Quit();

    if (quit | MAIN_QUIT_IMG) IMG_Quit();


    if (quit | MAIN_QUIT_SDL) SDL_Quit();


    return;

}


#if defined(_WIN32) && !defined(NDEBUG)

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);

    return main(__argc, __argv);

}

#endif
