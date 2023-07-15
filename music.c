#include "music.h"


int         music_list_length = 0;

Mix_Music **music_list        = NULL;


int  load_music             (const char *file_path)
{

    Mix_Music *new_music = Mix_LoadMUS(file_path);

    if (new_music == NULL)
    {

        fprintf(stderr, "Error loading the music '%s': %s\n", file_path, Mix_GetError());

        return false;

    }

    return add_to_music_list(new_music);

}

int  add_to_music_list      (Mix_Music *music)
{

    if (music_list_length >= MAX_MUSIC_LIST_LENGTH)
    {

        fprintf(stderr, "The music_list is full. Cannot add more songs, size: %d\n", music_list_length);

        return -1;

    }

    int new_music_list_size = (music_list_length + 1) * sizeof(Mix_Music *);

    Mix_Music **new_music_list = (Mix_Music **)realloc(music_list, new_music_list_size);

    if (new_music_list == NULL)
    {   

        new_music_list = (Mix_Music **)malloc(new_music_list_size);
        
        if (new_music_list == NULL)
        {

            fprintf(stderr, "Error allocating memory for music_list with length: %d and size: %d.\n", music_list_length, new_music_list_size);
         
            return -1;
        
        }
        
        for (unsigned int q = 0; q < music_list_length; q++) new_music_list[q] = music_list[q];

        free(music_list);

    }
    
    music_list = new_music_list;
    
    music_list[music_list_length] = music;

    return music_list_length++;

}

bool play_music             (int index, int loops)
{

    if (index < 0 || index >= music_list_length)
    {

        printf("Invalid index. There is no music corresponding to index %d.\n", index);
    
        return false;
    
    }

    if (Mix_PlayMusic(music_list[index], loops) == -1)
    {
    
        printf("Error playing the music: %s\n", Mix_GetError());
    
        return false;
    
    }

    return true;

}

bool rmv_from_music_list(int index)
{

    if (index < 0 || index >= music_list_length)
    {
    
        printf("Invalid index. There is no music corresponding to index %d.\n", index);
    
        return false;
    
    }

    Mix_FreeMusic(music_list[index]);

    for (unsigned int i = index; i < music_list_length - 1; i++)
        music_list[i] = music_list[i + 1];

    music_list_length--;

    music_list = realloc(music_list, music_list_length * sizeof(Mix_Music *));

    if (music_list == NULL && music_list_length > 0)
    {
    
        printf("Error freeing memory of the music list.\n");
    
        return false;
    
    }

    return true;

}

void rmv_all_from_music_list()
{

    for (int i = 0; i < music_list_length; i++)
        Mix_FreeMusic(music_list[i]);

    free(music_list);
    
    music_list_length = 0;

    music_list        = NULL;

    return;

}
