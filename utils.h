
#ifndef UTILS_H
#define UTILS_H

    #ifdef __ANDROID__
    
        #include <SDL.h>

    #else

        #include <SDL2/SDL.h>

    #endif


    #ifdef _WIN32

        #include <windows.h>

    #endif


    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    #include <stdbool.h>
    
    
    #define DEG_TO_RAD (M_PI / 180.0)

    #define RAD_TO_DEG (180.0 / M_PI)

    
    extern float lerp(float start, float end, float ratio);

    extern float lerp_threshold(float start, float end, float ratio, float threshold);
    

    extern int render_surface_in_surface_with_offset(SDL_Surface *src, SDL_Rect *src_rect, SDL_Surface *dst, SDL_Rect *dst_rect, int offset_x, int offset_y);


    extern bool utils_nano_sleep(long long ns);


    extern void utils_msleep(long long miliseconds);

    extern void utils_nsleep(long long nanoseconds);

#endif
