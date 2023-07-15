
#ifndef INPUT_H
#define INPUT_H

    #ifdef __ANDROID__

        #include <SDL_keyboard.h>
        #include <SDL_mouse.h>
        #include <SDL_rect.h>
        #include <SDL_touch.h>

    #else
    
        #include <SDL2/SDL_keyboard.h>
        #include <SDL2/SDL_mouse.h>
        #include <SDL2/SDL_rect.h>
        #include <SDL2/SDL_touch.h>
    
    #endif


    #include <stdbool.h>
    #include <stdio.h>


    extern const Uint8 *kb_state;


    extern Uint32    mouse_state;

    extern SDL_Point mouse_position;


    extern bool setup_keyboard(void);

    extern void update_mouse  (void);

#endif
