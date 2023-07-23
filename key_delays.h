
#ifndef KEY_DELAYS_H
#define KEY_DELAYS_H

    #include "input.h"

    #include <stdlib.h>


    typedef struct key_delay
    {
        
        Uint8 key;

        float delay;


        struct key_delay *next;

    } key_delay_t;

    extern key_delay_t *key_delay_default_list;

    key_delay_t *create_key_delay(Uint8 key, float delay);
    void destroy_key_delay_list(key_delay_t *head);
    bool add_key_delay(key_delay_t **head, Uint8 key, float delay);
    void remove_key_delay(key_delay_t **head, Uint8 key);
    void update_key_delays(key_delay_t **head, float delta);

#endif
