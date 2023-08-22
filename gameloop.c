#include "gameloop.h"


Sint64 gameloop_target_fps = 60;


bool   gameloop_enable_render_sync_variable = true;

bool gameloop_can_render = false;

bool   gameloop_is_running = false;


SDL_SpinLock renderer_spin_lock = 0;


SDL_Thread *gameloop_thread = NULL;


int gameloop_thread_routine(void *argument)
{

    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);


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


        if (!gameloop_enable_render_sync_variable || gameloop_can_render == true)
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

                render_current_frame_time = SDL_GetPerformanceCounter();

                render_delta_time = ((double)render_current_frame_time - (double)render_previous_frame_time) / (double)performance_frequency;
                
                render_previous_frame_time = render_current_frame_time;

                float r_dt = (float)render_delta_time;

                /*printf("r_dt: %f\n", r_dt); */

                gameloop_render(r_dt);


                gameloop_can_render = false;


#ifdef GAMELOOP_SYNC_BY_MUTEX  
      
                SDL_UnlockMutex(renderer_mutex);

#endif

#ifdef GAMELOOP_SYNC_BY_SPINLOCK
      
                SDL_AtomicUnlock(&renderer_spin_lock);

#endif


            }



        }


        gameloop_late_update(u_dt);


        double frame_delay = (1000.0 / (double)gameloop_target_fps) - update_delta_time;


        // printf("fps: %f\n", update_delta_time);


        if (frame_delay > 0)
        {

            // utils_msleep(frame_delay);
            
            utils_nano_sleep((long long)(frame_delay * 10000.0));
            
            // SDL_Delay(frame_delay);

        }

    }

    gameloop_quit();

    return 0;

}


void gameloop_start()
{
 
    sprite_anim_t *bg_ani = load_sprite_anim(get_image_path_from_assets("", "default-background_canvas.png"), rendering_surface_rect, 1, 0);

    bg_ani->spr->destination_rectangle = rendering_surface_rect;

    
    sprite_anim_t *bf_ani = load_sprite_anim(get_image_path_from_assets("", "default-board_frame.png"), (SDL_Rect) { 0, 0, 128, 224 }, 1, 0);
    

    gps_context_t *single_gp_ctx = create_gps_context(bg_ani, bf_ani);

     
    sprite_anim_t *npf_ani = load_sprite_anim(get_image_path_from_assets("", "default-next_pieces_frame.png"), (SDL_Rect) { 0, 0, 32, 56 }, 1, 0);

    single_gp_ctx->next_pieces_frame = npf_ani;
    

    single_gp_ctx->background_canvas_x_offset = 0;
    single_gp_ctx->background_canvas_y_offset = 0;

    single_gp_ctx->board_frame_x_offset = (single_gp_ctx->background_canvas->spr->destination_rectangle.w / 2) - (single_gp_ctx->board_frame->spr->destination_rectangle.w / 2);
    single_gp_ctx->board_frame_y_offset = (single_gp_ctx->background_canvas->spr->destination_rectangle.h / 2) - (single_gp_ctx->board_frame->spr->destination_rectangle.h / 2);

    single_gp_ctx->board_x_offset = (single_gp_ctx->background_canvas->spr->destination_rectangle.w / 2) - (96  / 2);
    single_gp_ctx->board_y_offset = (single_gp_ctx->background_canvas->spr->destination_rectangle.h / 2) - (208 / 2);

    single_gp_ctx->next_pieces_frame_x_offset = single_gp_ctx->board_frame_x_offset + single_gp_ctx->board_frame->spr->destination_rectangle.w + 16;
    single_gp_ctx->next_pieces_frame_y_offset = single_gp_ctx->board_frame_y_offset + 4;

    single_gp_ctx->next_pieces_x_offset = single_gp_ctx->board_frame_x_offset + single_gp_ctx->board_frame->spr->destination_rectangle.w + 16 + 8;
    single_gp_ctx->next_pieces_y_offset = single_gp_ctx->board_frame_y_offset + 8;

    
    for (int i = 0; i < 5; i++)
    {
    
        char filename[128];

        snprintf(filename, sizeof(filename), "format-%d.png", i + 1);

        char *image_path = get_image_path_from_assets("formats/16bits/", filename);

        sprite_t *spr = load_sprite(image_path);

        sprite_anim_t *aspr = create_sprite_anim(spr, spr->source_rectangle, 1, 0.0f);

        add_format_on_gps_context(single_gp_ctx,  create_gps_format(false, aspr));
    
    }


    char *image_path = get_image_path_from_assets("", "xcursor.png");

    single_gp_ctx->x_cursor = load_sprite(image_path);

    image_path = get_image_path_from_assets("", "ycursor.png");

    single_gp_ctx->y_cursor = load_sprite(image_path);

    image_path = get_image_path_from_assets("", "incursor.png");

    single_gp_ctx->i_cursor = load_sprite(image_path);


    start_gameplay(single_gp_ctx);

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

    update_key_delays_in_list(&key_delay_default_list, dt);

    late_update_gameplay(dt);

}

void gameloop_quit()
{

    quit_gameplay();

}
