#include "sound.h"


int sound_list_length  = 0;

Mix_Chunk **sound_list = NULL;


int  load_sound             (const char *file_path)
{

    Mix_Chunk *new_sound = Mix_LoadWAV(file_path);

    if (new_sound == NULL)
    {

        fprintf(stderr, "Error loading sound effect '%s': %s\n", file_path, Mix_GetError());

        return -1;

    }

    return add_to_sound_list(new_sound);

}

int  add_to_sound_list      (Mix_Chunk *sound)
{

    if (sound_list_length >= MAX_SOUND_LIST_LENGTH)
    {

        fprintf(stderr, "The sound list is full. Cannot add more sound effects, size: %d\n", sound_list_length);

        return -1;

    }

    int new_sound_list_size = (sound_list_length + 1) * sizeof(Mix_Chunk *);

    Mix_Chunk **new_sound_list = (Mix_Chunk **)realloc(sound_list, (sound_list_length + 1) * sizeof(Mix_Chunk *));

    if (new_sound_list == NULL)
    {   

        new_sound_list = (Mix_Chunk **)malloc(new_sound_list_size);
        
        if (new_sound_list == NULL)
        {

            fprintf(stderr, "Error allocating memory for music_list with length: %d and size: %d.\n", sound_list_length, new_sound_list_size);
         
            return -1;
        
        }
        
        for (unsigned int q = 0; q < sound_list_length; q++)
            new_sound_list[q] = sound_list[q];

        free(sound_list);

    }

    sound_list = new_sound_list;

    sound_list[sound_list_length] = sound;

    return sound_list_length++;

}

bool play_sound             (int index)
{

    return play_sound_in_channel(index, -1);

}

bool play_sound_in_channel  (int index, int channel)
{
    
    if (index < 0 || index >= sound_list_length)
    {
    
        fprintf(stderr, "Invalid index. There is no sound effect corresponding to index %d\n", index);
    
        return false;
    
    }

    if (Mix_PlayChannel(channel, sound_list[index], 0) == -1)
    {
    
        fprintf(stderr, "Error playing sound effect: %s\n", Mix_GetError());
    
        return false;
    
    }

    return true;

}

bool rmv_from_sound_list    (int index)
{

    if (index < 0 || index >= sound_list_length)
    {

        fprintf(stderr, "Invalid index. There is no sound effect corresponding to index %d\n", index);

        return false;

    }

    Mix_FreeChunk(sound_list[index]);

    for (int q = index; q < sound_list_length - 1; q++)
        sound_list[q] = sound_list[q + 1];

    sound_list_length--;

    Mix_Chunk **new_sound_list = (Mix_Chunk **)realloc(sound_list, sound_list_length * sizeof(Mix_Chunk *));

    if (new_sound_list == NULL && sound_list_length > 0)
    {

        fprintf(stderr, "Error freeing memory of sound list\n");

        return false;

    }

    sound_list = new_sound_list;

    return true;

}

void rmv_all_from_sound_list(void)
{

    for (int q = 0; q < sound_list_length; q++)
        Mix_FreeChunk(sound_list[q]);

    free(sound_list);
    
    sound_list_length = 0;
    
    sound_list        = NULL;

    return;

}
