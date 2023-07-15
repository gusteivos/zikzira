#include "assets.h"

void *assets_get_file_content(const char *file_path, long *file_size)
{

    FILE *file = fopen(file_path, "rb");

    if (file == NULL)
    {

        fprintf(stderr, "Failed to read file: %s, in \"assets_get_file_content\".", file_path);

        return NULL;

    }


    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    fseek(file, 0, SEEK_SET);


    void *file_content = malloc(*file_size);

    if (file_content == NULL)
    {

        fprintf(stderr, "Failed to allocate memory for file content in \"assets_get_file_content\".");

        fclose(file);

        return NULL;

    }

    fread(file_content, 1, *file_size, file);


    fclose(file);


    return file_content;

}

char *assets_get_file_content_null(const char *file_path, long *file_size)
{

    void *file_content = assets_get_file_content(file_path, file_size);

    if (file_content == NULL)
    {

        fprintf(stderr, "");

        return NULL;

    }
    

    char *file_content_null = (char *)malloc(*file_size + 1);
    
    if (file_content_null == NULL)
    {
    
        fprintf(stderr, "Failed to allocate memory for file content in \"assets_get_file_content_null\".");
        
        free(file_content);
        
        return NULL;
    
    }

    memcpy(file_content_null, file_content, *file_size);

    file_content_null[*file_size] = '\0';


    free(file_content);


    return file_content_null;

}


char *get_path_from_assets(char *folder, char *file_name)
{

    size_t folder_str_len    = strlen(folder);

    size_t file_name_str_len = strlen(file_name);


    size_t out_str_len = sizeof(ASSETS_FOLDER) + folder_str_len + file_name_str_len + 1;


    char *out_str = (char *)malloc(out_str_len);

    if (out_str == NULL)
    {

        fprintf(stderr, "Failed to allocate memory when getting path from assets: %s, %s.", folder, file_name);

        return NULL;

    }


    strcpy(out_str, ASSETS_FOLDER);

    strcat(out_str, folder);

    strcat(out_str, file_name);


    out_str[out_str_len] = '\0';


    return out_str;

}

char *get_file_path_from_assets(char *folder, char *subfolder, char *file_name)
{

    size_t folder_str_len    = strlen(folder);

    size_t subfolder_str_len = strlen(subfolder);


    size_t fss_str_len = sizeof(ASSETS_FOLDER) + folder_str_len + subfolder_str_len + 1;


    char *fss_str = (char *)malloc(fss_str_len);

    if (fss_str == NULL)
    {

        fprintf(stderr, ": %s, %s.", folder, subfolder);

        return NULL;

    }


    strcpy(fss_str, folder);

    strcat(fss_str, subfolder);

    fss_str[fss_str_len] = '\0';


    char *file_path = get_path_from_assets(fss_str, file_name);

    free(fss_str);

    if (file_path == NULL)
    {

        fprintf(stderr, "Failed to get image file path: %s, %s.", fss_str, file_name);
    
        return NULL;
    
    }


    return file_path;

}
