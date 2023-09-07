
#ifndef KEYBOARD_DELAY_H
#define KEYBOARD_DELAY_H

    #include "keyboard.h"

    #include <stdlib.h>


    typedef struct key_delay
    {
        
        Uint8 key;

        float delay;

        struct key_delay *next;

    } key_delay_t;


    extern key_delay_t *key_delay_default_list;


    extern key_delay_t *create_key_delay(Uint8 key, float delay);
    

    extern bool add_key_delay_on_list(key_delay_t **head, Uint8 key, float delay);
    
    extern void remove_key_delay_from_list(key_delay_t **head, Uint8 key);
    
    extern void update_key_delays_in_list(key_delay_t **head, float delta_time);


    extern void destroy_key_delay(key_delay_t *key);

    extern void destroy_key_delay_list(key_delay_t *head);


#endif
