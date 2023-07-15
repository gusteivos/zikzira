#include <input.h>


const Uint8 *kb_state = NULL;


Uint32    mouse_state    = 0;

SDL_Point mouse_position = { 0, 0 };


bool setup_keyboard()
{

    kb_state = SDL_GetKeyboardState(NULL);
    
    if (kb_state == NULL)
    {
    
        fprintf(stderr, "Erro ao obter o estado do teclado: %s\n", SDL_GetError());
    
        return false;
    
    }

    return true;

}

void update_mouse()
{

    mouse_state = SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

    return;

}
