
#ifndef KEYBOARD_H
#define KEYBOARD_H

    #ifdef __ANDROID__

        #include <SDL_keyboard.h>
       
    #else
    
        #include <SDL2/SDL_keyboard.h>
       
    #endif


    #include <stdbool.h>
    #include <stdio.h>


    #define PRINT_KEYBOARD_THINGS


    extern int number_of_keyboard_state_keys;

    extern const Uint8 *keyboard_state;


    extern bool setup_keyboard(void);


    extern void quit_keyboard(void);

#endif
