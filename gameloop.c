#include "gameloop.h"


Sint64 gameloop_target_fps = 1000;

bool   gameloop_is_running = false;


SDL_Thread *gameloop_thread = NULL;


int gameloop_thread_routine(void *argument)
{

    if (gameloop_is_running == false) return -1;

    
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, (8 * 1024));


    Uint64 performance_frequency      = SDL_GetPerformanceFrequency();
    
    Uint64 update_previous_frame_time = SDL_GetPerformanceCounter  ();

    Uint64 render_previous_frame_time = SDL_GetPerformanceCounter  ();
    
    Uint64 update_current_frame_time  = 0;

    Uint64 render_current_frame_time  = 0;
    
    double update_delta_time          = 0.0;

    double render_delta_time          = 0.0;

    gameloop_start();

    while (gameloop_is_running)
    {

        update_current_frame_time = SDL_GetPerformanceCounter();

        update_delta_time = ((double)update_current_frame_time - (double)update_previous_frame_time) / (double)performance_frequency;
        
        update_previous_frame_time = update_current_frame_time;

        float u_dt = (float)update_delta_time;

        /*printf("u_dt: %f\n", u_dt); */
    
        gameloop_update(u_dt);

        if (SDL_TryLockMutex(renderer_mutex) == 0)
        {

            render_current_frame_time = SDL_GetPerformanceCounter();

            render_delta_time = ((double)render_current_frame_time - (double)render_previous_frame_time) / (double)performance_frequency;
            
            render_previous_frame_time = render_current_frame_time;

            float r_dt = (float)render_delta_time;

            /*printf("r_dt: %f\n", r_dt); */

            // printf("fps: %f\n", 1.0f / r_dt);


            gameloop_render(r_dt);


            SDL_UnlockMutex(renderer_mutex);

        }

        gameloop_late_update(u_dt);

        Sint64 frame_delay = (1000 / gameloop_target_fps) - (Sint64)update_delta_time;

        if (frame_delay < 0) frame_delay = 0;

        SDL_Delay(frame_delay);

    }

    gameloop_quit();

    return 0;

}


void gameloop_start()
{

    gps_assets_t *assets = create_gps_assets();

    for (int i = 0; i < 5; i++)
    {
    
        char filename[100];

        snprintf(filename, sizeof(filename), "format-%d.png", i + 1);

        char *image_path = get_image_path_from_assets("formats/8bits/", filename);

        sprite_t *spr = load_sprite(image_path);

        add_format_on_gps_assets(assets, create_gps_format(false, spr));

        free(image_path);
    
    }

    start_gameplay(assets);

}

void gameloop_update(float dt)
{

    update_gameplay(dt);

}

void gameloop_render(float dt)
{

    render_gameplay(dt);

}

void gameloop_late_update(float dt)
{

    late_update_gameplay(dt);

}

void gameloop_quit()
{

    quit_gameplay();

}
