#include "sprite.h"


sprite_t *load_sprite(const char *file_path)
{
    
    SDL_Surface *surface = IMG_Load(file_path);
    
    if (surface == NULL)
    {
    
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());

        return NULL;
    
    }

    return create_sprite((SDL_Rect){ 0, 0, surface->w, surface->h }, (SDL_Rect){ 0, 0, surface->w, surface->h }, surface);;

}


sprite_t *create_sprite(SDL_Rect src_rect, SDL_Rect dst_rect, SDL_Surface *surface)
{
 
    sprite_t *spr = (sprite_t *)malloc(sizeof(sprite_t));
 
    if (spr == NULL)
    {
    
        fprintf(stderr, "Memory allocation failed for sprite.\n");
    
        return NULL;
    
    }

    spr->source_rectangle      = src_rect;

    spr->destination_rectangle = dst_rect;

    spr->surface = surface;

    return spr;

}


void destroy_sprite(sprite_t *spr)
{

    if (spr == NULL) return;

    if (spr->surface != NULL) SDL_FreeSurface(spr->surface);
    
    free(spr);

    spr = NULL;

    return;

}
