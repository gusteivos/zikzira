
#ifndef MAIN_H
#define MAIN_H

    #ifdef _WIN32

        #include <direct.h>
        #include <windows.h>
    
    #else

        #ifndef __ANDROID__
    
            #include <unistd.h>
            #include <limits.h>
        
            #ifndef PATH_MAX
            
                #define PATH_MAX 4096
            
            #endif

            #define MAX_PATH PATH_MAX

        #endif

    #endif

    #include "gameloop.h"
    #include "input/keyboard.h"
    #include "input/mouse.h"
    #include "window.h"

    
    #define WINDOW_TITLE "by gusteivos gp and ninca."


    #define GAME_NAME "zikzira" 


    extern bool init_main(void);

#endif
