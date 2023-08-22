#include "mouse.h"


Uint32    mouse_state = 0x00;

SDL_Point mouse_point = { 0, 0 };


Uint32    mouse_global_state = 0x00;

SDL_Point mouse_global_point = { 0, 0 };


Uint32    mouse_relative_state = 0x00;

SDL_Point mouse_relative_point = { 0, 0 };


void update_mouse(SDL_Point mouse_point_offset)
{

    mouse_state = SDL_GetMouseState(&mouse_point.x, &mouse_point.y);

    mouse_point.x += mouse_point_offset.x;

    mouse_point.y += mouse_point_offset.y;


    mouse_global_state = SDL_GetGlobalMouseState(&mouse_global_point.x, &mouse_global_point.y);


    mouse_relative_state = SDL_GetRelativeMouseState(&mouse_relative_point.x, &mouse_relative_point.y);


    // printf("Mouse na janela: %d, %d\n", mouse_point.x, mouse_point.y);
    // printf("Mouse global: %d, %d\n", mouse_global_point.x, mouse_global_point.y);
    // printf("Mouse relativo: %d, %d\n", mouse_relative_point.x, mouse_relative_point.y);

    return;

}
