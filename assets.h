
#ifndef ASSETS_H
#define ASSETS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    #define ASSETS_FOLDER "./content/"


    #define ASSETS_IMGS_FOLDER "images/"

    #define ASSETS_MUSS_FOLDER "musics/"

    #define ASSETS_SONS_FOLDER "sounds/"


    extern void *assets_get_file_content     (const char *file_path, long *file_size);

    extern char *assets_get_file_content_null(const char *file_path, long *file_size);


    extern char *get_path_from_assets     (char *folder, char *file_name);

    extern char *get_file_path_from_assets(char *folder, char *subfolder, char *file_name);


    #define get_image_path_from_assets(subfolder, file_name) get_file_path_from_assets(ASSETS_IMGS_FOLDER, subfolder, file_name)

    #define get_music_path_from_assets(subfolder, file_name) get_file_path_from_assets(ASSETS_MUSS_FOLDER, subfolder, file_name)

    #define get_sonds_path_from_assets(subfolder, file_name) get_file_path_from_assets(ASSETS_SONS_FOLDER, subfolder, file_name)

#endif
