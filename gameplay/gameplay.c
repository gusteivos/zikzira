#include "gameplay.h"


gps_context_t *gameplay_context = NULL;


void reset_gameplay()
{

    gameplay_context = NULL;

    return;

}


int start_gameplay(gps_context_t *context)
{

    if (context == NULL)
    {

        fprintf(stderr, "TODO: ");

        return 1;

    }

    

    return 0;

}


int update_gameplay     (float dt)
{



    return 0;

}

int render_gameplay     (float dt)
{



    return 0;

}

int late_update_gameplay(float dt)
{



    return 0;

}


void quit_gameplay()
{

    destroy_gps_context(gameplay_context);

    return;

}
