#include "keyboard.h"

int number_of_keyboard_state_keys = -1;

const Uint8 *keyboard_state = NULL;


bool setup_keyboard()
{

    if ((keyboard_state = SDL_GetKeyboardState(&number_of_keyboard_state_keys)) == NULL)
    {

        fprintf(stderr, "Error getting keyboard state: %s\n", SDL_GetError());


        return false;

    }

#if defined(PRINT_KEYBOARD_THINGS) && !defined(NDEBUG)
        
    else
    {

        printf("Number of keyboard state keys: %d\n", number_of_keyboard_state_keys);

        printf("Keyboard state pointer: %p\n", keyboard_state);

    }

#endif


    return true;

}


void quit_keyboard()
{

    number_of_keyboard_state_keys = -1;

    keyboard_state = NULL;


    return;

}
