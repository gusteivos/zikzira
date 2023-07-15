
#ifndef SPRITE_H
#define SPRITE_H

    
    #ifdef __ANDROID__
    
        #include <SDL.h>
        #include <SDL_image.h>

    #else

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>

    #endif


    #include <stdio.h>
    #include <stdbool.h>


    typedef struct sprite
    {

        SDL_Rect source_rectangle;

        SDL_Rect destination_rectangle;

        SDL_Surface *surface;

    } sprite_t;


    extern sprite_t *load_sprite  (const char *file_path);


    extern sprite_t *create_sprite(SDL_Rect src_rect, SDL_Rect dst_rect, SDL_Surface *surface);

    
    extern void      destroy_sprite(sprite_t *spr);

#endif
