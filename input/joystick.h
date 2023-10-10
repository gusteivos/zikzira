
#ifndef JOYSTICK_H
#define JOYSTICK_H

    #ifdef __ANDROID__

        #include <SDL_joystick.h>
       
    #else
    
        #include <SDL2/SDL_joystick.h> 
       
    #endif


    #include <stdio.h>
    #include <stdlib.h>


    typedef struct joystick
    {

        int              iid;

        SDL_JoystickGUID uid;


        const char *name;


        SDL_Joystick *sdl_joystick;

        
        int    num_of_buttons;

        Uint8 *buttons;


        int     num_of_axes;

        Sint16 *axes;

    } joystick_t;
    

    joystick_t *open_joystick(int index);


    void update_joystick_button_states(joystick_t *joy);

    void update_joystick_axi_states(joystick_t *joy);


    void close_joystick(joystick_t *joy);

#endif
