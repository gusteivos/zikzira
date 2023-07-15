
#ifndef SOUND_H
#define SOUND_H

    #ifdef __ANDROID__
    
        #include <SDL_mixer.h>

    #else

        #include <SDL2/SDL_mixer.h>

    #endif

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>


    #define MAX_SOUND_LIST_LENGTH 64


    extern int         sound_list_length;

    extern Mix_Chunk **sound_list;


    /**
     * Loads a sound effect file from the specified file path and adds it to the sound list.
     *
     * @param file_path The file path of the sound effect to load.
     * @return .
     */
    extern int  load_sound             (const char *file_path);

    /**
     * Adds a sound effect to the sound list.
     *
     * @param sound A pointer to the sound effect to be added.
     * @return .
     */
    extern int  add_to_sound_list      (Mix_Chunk *sound);

    /**
     * Plays a sound effect from the sound list at the specified index.
     *
     * @param index The index of the sound effect in the sound list to play.
     * @return Returns true if the sound effect was played successfully, false otherwise.
     */
    extern bool play_sound             (int index);

    /**
     * Plays a sound effect from the sound list at the specified index on a specific channel.
     *
     * @param index The index of the sound effect in the sound list to play.
     * @param channel The channel to play the sound effect on.
     * @return Returns true if the sound effect was played successfully, false otherwise.
     */
    extern bool play_sound_in_channel  (int index, int channel);

    /**
     * Removes a sound effect from the sound list at the specified index.
     *
     * @param index The index of the sound effect to remove.
     * @return Returns true if the sound effect was successfully removed, false otherwise.
     */
    extern bool rmv_from_sound_list    (int index);

    /**
     * Removes all sound effects from the sound list and frees the memory.
     */
    extern void rmv_all_from_sound_list(void);

#endif
