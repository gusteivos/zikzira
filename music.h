
#ifndef MUSIC_H
#define MUSIC_H

    #ifdef __ANDROID__
    
        #include <SDL_mixer.h>

    #else

        #include <SDL2/SDL_mixer.h>

    #endif

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>


    #define MAX_MUSIC_LIST_LENGTH 16


    extern int         music_list_length;

    extern Mix_Music **music_list;

    /**
     * Loads a music file from the specified file path and adds it to the music list.
     *
     * @param file_path The file path of the music to load.
     * @return Returns true if the music was loaded and added successfully, false otherwise.
     */
    extern int  load_music             (const char *file_path);

    /**
     * Adds a music to the music list.
     *
     * @param music A pointer to the music to be added.
     * @return Returns true if the music was added successfully, false if the music list is full.
     */
    extern int  add_to_music_list      (Mix_Music *music);

    /**
     * Plays the music from the music list at the specified index.
     *
     * @param index The index of the music in the music list to play.
     * @param loops The number of times the music should loop (-1 for infinite looping).
     * @return Returns true if the music was played successfully, false otherwise.
     */
    extern bool play_music             (int index, int loops);

    /**
     * Removes a music from the music list at the specified index.
     *
     * @param index The index of the music to remove.
     * @return Returns true if the music was successfully removed, false otherwise.
     */
    extern bool rmv_from_music_list    (int index);

    /**
     * Removes all music from the music list and frees the memory.
     */
    extern void rmv_all_from_music_list(void);

#endif
