#include "key_delays.h"

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

void destroy_key_delay_list(key_delay_t *head)
{

    while (head != NULL)
    {
        key_delay_t *temp = head;
        head = head->next;
        free(temp);
    }

}

bool add_key_delay(key_delay_t **head, Uint8 key, float delay)
{

    if (head == NULL)
    {
    
        key_delay_t *new_key_delay = create_key_delay(key, delay);
    
        if (new_key_delay == NULL)
        {
            return false; // Falha na alocação da nova peça
        }
    
        *head = new_key_delay;
        return true;
    
    }

    key_delay_t *current = *head;

    // Verifica se a lista já possui a peça com a chave especificada
    while (current != NULL)
    {
        if (current->key == key)
        {
            return false; // A peça já existe na lista
        }
        current = current->next;
    }

    key_delay_t *new_key_delay = create_key_delay(key, delay);
    if (new_key_delay == NULL)
    {
        return false; // Falha na alocação da nova peça
    }

    new_key_delay->next = *head;
    *head = new_key_delay;
    return true;
}

void remove_key_delay(key_delay_t **head, Uint8 key)
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
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void update_key_delays(key_delay_t **head, float delta)
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

                free(temp);
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }

    }

}
