
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
    #include "input/joystick.h"
    #include "window.h"


    #define WINDOW_TITLE "by gusteivos gp and ninca."


    #define GAME_NAME "zikzira"


    #define MAIN_QUIT_KEY 0b10000000000000000000000000000000

    #define MAIN_QUIT_WIN 0b01000000000000000000000000000000

    #define MAIN_QUIT_REN 0b00100000000000000000000000000000

    #define MAIN_QUIT_MIX 0b00000000000000000000000000000100

    #define MAIN_QUIT_IMG 0b00000000000000000000000000000010

    #define MAIN_QUIT_SDL 0b00000000000000000000000000000001

    #define MAIN_QUIT_ALL 0b11111111111111111111111111111111


    extern bool init_main(void);


    extern void quit_main(uint32_t quit);

#endif
