#include "utils.h"


float lerp(float start, float end, float ratio)
{

    return start + ratio * (end - start);

}

float lerp_threshold(float start, float end, float ratio, float threshold)
{

    float interpolated_value = start + ratio * (end - start);


    interpolated_value = (fabsf(interpolated_value) <= threshold) ? end : interpolated_value;


    return interpolated_value;

}


int render_surface_in_surface_with_offset(SDL_Surface *src, SDL_Rect *src_rect, SDL_Surface *dst, SDL_Rect *dst_rect, int offset_x, int offset_y)
{

    if (!src || !dst)
    {

        fprintf(stderr, "TODO: \n");

        return 1;

    }

    SDL_Rect destination_rectangle = *dst_rect;

    destination_rectangle.x += offset_x;

    destination_rectangle.y += offset_y;


    SDL_BlitScaled(src, src_rect, dst, &destination_rectangle);


    return 0;

}

void utils_msleep(long long milliseconds)
{

#ifdef _WIN32

    timeBeginPeriod(1);

    Sleep((DWORD)milliseconds);
    
    timeEndPeriod(1);

#else

    struct timespec timeToWait;
    
    timeToWait.tv_sec = milliseconds / 1000;
    timeToWait.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&timeToWait, NULL);

#endif


    return;

}

void utils_nsleep(long long nanoseconds)
{

    struct timespec timeToWait;

    timeToWait.tv_sec  = nanoseconds / 1000000000;
    timeToWait.tv_nsec = nanoseconds % 1000000000;

#ifdef _WIN32

        HANDLE timer;
        LARGE_INTEGER li;

        li.QuadPart = -timeToWait.tv_nsec;

        timer = CreateWaitableTimer(NULL, TRUE, NULL);
        SetWaitableTimer(timer, &li, 0, NULL, NULL, 0);

        WaitForSingleObject(timer, INFINITE);

        CloseHandle(timer);

#elif
    
    nanosleep(&timeToWait, NULL);

#endif


    return;

}

BOOLEAN nanodsleep(LONGLONG ns)
{
    /* Declarations */
    HANDLE timer;	/* Timer handle */
    LARGE_INTEGER li;	/* Time defintion */
    /* Create timer */
    if(!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
        return FALSE;
    /* Set timer properties */
    li.QuadPart = -ns;
    if(!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)){
        CloseHandle(timer);
        return FALSE;
    }
    /* Start & wait for timer */
    WaitForSingleObject(timer, INFINITE);
    /* Clean resources */
    CloseHandle(timer);
    /* Slept without problems */
    return TRUE;
}

