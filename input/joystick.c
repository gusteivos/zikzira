#include "joystick.h"


joystick_t *open_joystick(int index)
{

    joystick_t *new_joy = NULL;


    SDL_Joystick *joy = SDL_JoystickOpen(index);

    if (joy != NULL)
    {

        new_joy = malloc(sizeof(joystick_t));

        if (new_joy != NULL)
        {

            new_joy->sdl_joystick = joy;


            new_joy->iid = SDL_JoystickInstanceID(new_joy->sdl_joystick);

            new_joy->uid = SDL_JoystickGetGUID   (new_joy->sdl_joystick);


            new_joy->name = SDL_JoystickName(new_joy->sdl_joystick);


            new_joy->num_of_buttons = SDL_JoystickNumButtons(new_joy->sdl_joystick);

            new_joy->buttons        = (Uint8 *)calloc(new_joy->num_of_buttons, sizeof(Uint8));


            new_joy->num_of_axes = SDL_JoystickNumAxes(new_joy->sdl_joystick);

            new_joy->axes        = (Sint16 *)calloc(new_joy->num_of_axes, sizeof(Sint16));

        }
        else
        {

            printf("TEMP, Erro ao alocar o joystick %d: %s\n", index, SDL_GetError());


            SDL_JoystickClose(joy);

        }

    }
    else
    {

        printf("TEMP, Erro ao abrir o joystick %d: %s\n", index, SDL_GetError());

    }


    return new_joy;

}


void update_joystick_button_states(joystick_t *joy)
{

    if (joy == NULL)
    {



        return;
        
    }


    for (int button_num = 0; button_num < joy->num_of_buttons; button_num++) 
        joy->buttons[button_num] = SDL_JoystickGetButton(joy->sdl_joystick, button_num);


    return;

}

void update_joystick_axi_states(joystick_t *joy)
{

    if (joy == NULL)
    {



        return;
        
    }


    for (int axle_num = 0; axle_num < joy->num_of_axes; axle_num++)
    {

        joy->axes[axle_num] = SDL_JoystickGetAxis(joy->sdl_joystick, axle_num);


        printf("Eixo %d: %d\n", axle_num, (int)joy->axes[axle_num]);

    }


    return;

}


void close_joystick(joystick_t *joy)
{



    return;

}
