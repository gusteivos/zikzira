#include "sprite_anim.h"


sprite_anim_t *load_sprite_anim(const char *path, SDL_Rect src_rect, int num_frames, float frame_delay)
{

    sprite_t *new_spr = load_sprite(path);


    sprite_anim_t *new_anim = create_sprite_anim(new_spr, src_rect, num_frames, frame_delay);
    
    if (new_anim == NULL)
    {

        fprintf(stderr, "TODO: ");

        if (new_spr != NULL) destroy_sprite(new_spr);

    }


    return new_anim;

}

sprite_anim_t *create_sprite_anim(sprite_t *spr, SDL_Rect src_rect, int num_frames, float frame_delay)
{

    if (spr == NULL || num_frames <= 0 || frame_delay < 0.0f)
    {

        fprintf(stderr, "");

        return NULL;

    }

    spr->source_rectangle = src_rect;


    sprite_anim_t *new_anim = (sprite_anim_t *)malloc(sizeof(sprite_anim_t));
    
    if (new_anim == NULL)
    {
    
        fprintf(stderr, "Memory allocation failed for sprite animation.\n");
    
        return NULL;
    
    }

    new_anim->animate_horizontal_vertical = true;

    new_anim->can_animate = true;

    new_anim->spr = spr;
 
    new_anim->num_frames = num_frames;

    new_anim->current_frame = 0;

    new_anim->frame_delay = frame_delay;


    return new_anim;

}


void update_sprite_anim(sprite_anim_t *anim, float delta_time)
{

    if (anim == NULL)
    {

        fprintf(stderr, "");

        return;

    }


    if (anim->can_animate)
    {

        anim->elapsed_frame_time += delta_time;

        if (anim->elapsed_frame_time >= anim->frame_delay)
        {
    
            anim->elapsed_frame_time = 0.0;

            anim->current_frame = (anim->current_frame + 1) % anim->num_frames;

            if (anim->animate_horizontal_vertical)
            {
    
                int frame_width = anim->spr->source_rectangle.w;
    
                anim->spr->source_rectangle.x = anim->current_frame * frame_width;
    
            }
            else
            {
    
                int frame_height = anim->spr->source_rectangle.h;
    
                anim->spr->source_rectangle.y = anim->current_frame * frame_height;
            }
    
        }
    
    }

    return;

}


void destroy_sprite_anim(sprite_anim_t *anim, bool destroy_spr)
{
 
    if (anim == NULL) return;

    if (destroy_spr && anim->spr != NULL) destroy_sprite(anim->spr);

    free(anim);

    anim = NULL;

    return;

}
