#include "keyboard_delay.h"


key_delay_t *key_delay_default_list = NULL;


key_delay_t *create_key_delay(Uint8 key, float delay)
{

    key_delay_t *new_key_delay = (key_delay_t *)malloc(sizeof(key_delay_t));

    if (new_key_delay != NULL)
    {

        new_key_delay->key = key;

        new_key_delay->delay = delay;

        new_key_delay->next = NULL;

    }


    return new_key_delay;

}


bool add_key_delay_on_list(key_delay_t **head, Uint8 key, float delay)
{

    if (head == NULL)
    {

        key_delay_t *new_key_delay = create_key_delay(key, delay);

        if (new_key_delay == NULL) return false;

        *head = new_key_delay;


        return true;

    }

    key_delay_t *current = *head;


    while (current != NULL)
    {

        if (current->key == key) return false;

        current = current->next;

    }


    key_delay_t *new_key_delay = create_key_delay(key, delay);

    if (new_key_delay == NULL) return false;

    new_key_delay->next = *head;

    *head = new_key_delay;


    return true;

}

void remove_key_delay_from_list(key_delay_t **head, Uint8 key)
{

    key_delay_t *current = *head;

    key_delay_t *prev = NULL;

    while (current != NULL)
    {

        if (current->key == key)
        {

            if (prev != NULL)
            {

                prev->next = current->next;

            }
            else
            {

                *head = current->next;

            }

            destroy_key_delay(current);

            return;

        }

        prev = current;

        current = current->next;

    }

}

void remove_all_key_delays(key_delay_t **head, Uint8 key)
{

    key_delay_t *current = *head;

    key_delay_t *prev = NULL;

    while (current != NULL)
    {

        if (current->key == key)
        {

            if (prev != NULL)
            {

                prev->next = current->next;

            }
            else
            {

                *head = current->next;

            }

            key_delay_t *temp = current;

            current = current->next;


            destroy_key_delay(temp);

        }
        else
        {

            prev = current;

            current = current->next;

        }

    }

}

void update_key_delays_in_list(key_delay_t **head, float delta)
{

    if (head != NULL)
    {

        key_delay_t *current = *head;

        key_delay_t *prev = NULL;

        while (current != NULL)
        {

            current->delay -= delta;

            if (current->delay <= 0)
            {

                key_delay_t *temp = current;

                if (prev != NULL)
                {

                    prev->next = current->next;

                    current = prev->next;

                }
                else
                {

                    *head = current->next;

                    current = *head;

                }


                destroy_key_delay(temp);

            }
            else
            {

                prev = current;

                current = current->next;

            }

        }

    }

}


void destroy_key_delay(key_delay_t *key)
{

    if (key == NULL) return;

    free(key);

    key = NULL;


    return;

}

void destroy_key_delay_list(key_delay_t *head)
{

    while (head != NULL)
    {

        key_delay_t *temp = head;

        head = head->next;

        free(temp);

    }

}
