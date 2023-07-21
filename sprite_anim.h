
#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H

    #include "sprite.h"


    typedef struct sprite_anim
    {

        bool can_animate;

        bool animate_horizontal_vertical;


        int num_frames;

        int current_frame;
        
        float frame_delay;

        float elapsed_frame_time;


        sprite_t *spr;

    } sprite_anim_t;


    extern sprite_anim_t *load_sprite_anim(const char *path, SDL_Rect src_rect, int num_frames, float frame_delay);

    extern sprite_anim_t *create_sprite_anim(sprite_t *spr, SDL_Rect src_rect, int num_frames, float frame_delay);

    
    extern void update_sprite_anim(sprite_anim_t *anim, float delta_time);

    
    extern void destroy_sprite_anim(sprite_anim_t *anim, bool destroy_anim);

#endif
