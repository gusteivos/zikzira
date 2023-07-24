
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

    #include <key_delays.h>
    #include <input.h>
    
    #include <music.h>
    #include <sound.h>

    #include <window.h>
    #include <renderer.h>


    


    extern void reset_gameplay();
    
    extern int start_gameplay(gps_context_t *context);


    extern int update_gameplay     (float dt);
    
    extern int render_gameplay     (float dt);

    extern int late_update_gameplay(float dt);


    extern void quit_gameplay(void);


#endif
