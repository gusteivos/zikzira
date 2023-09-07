#include "utils.h"


float lerp(float start, float end, float ratio)
{

    return start + ratio * (end - start);

}

float lerp_threshold(float start, float end, float ratio, float threshold)
{

    float interpolated_value = start + ratio * (end - start);


    interpolated_value = (fabsf(interpolated_value - end) <= threshold) ? end : interpolated_value;


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

static long long toInteger(LARGE_INTEGER integer)
{

#ifdef INT64_MAX

        return integer.QuadPart;

#else

        return (static_cast<long long>(integer.HighPart) << 32) | integer.LowPart;

#endif

}

static LARGE_INTEGER toLargeInteger(long long value)
{
    
    LARGE_INTEGER result;

#ifdef INT64_MAX
    
        result.QuadPart = value;

#else

        result.high_part = value & 0xFFFFFFFF00000000;

        result.low_part  = value & 0xFFFFFFFF;

#endif
    
    return result;

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

bool utils_nano_sleep(long long ns)
{

    HANDLE htimer = NULL;

    if ((htimer = CreateWaitableTimer(NULL, TRUE, TEXT("utils_nano_sleep timer"))) == NULL)
    {

        printf("%d\n", GetLastError());

        return false;

    }


    LARGE_INTEGER liDueTime = toLargeInteger(-ns);

    if(SetWaitableTimer(htimer, &liDueTime, 0, NULL, NULL, TRUE) == FALSE)
    {

        CloseHandle(htimer);

        return false;

    }

    
    WaitForSingleObject(htimer, INFINITE);
    
    CloseHandle(htimer);


    return true;

}

bool nanodsleep(LONGLONG ns)
{
    
    HANDLE htimer = NULL;

    if((htimer = CreateWaitableTimer(NULL, TRUE, TEXT("nanotimer"))) == NULL)
    {
 
        printf("CreateWaitableTimer failed with error %d\n", GetLastError());
        
        return false;
    
    }


    LARGE_INTEGER liDueTime;

    liDueTime.LowPart  = (DWORD) ( -ns & 0xFFFFFFFF );
    liDueTime.HighPart = (LONG)  ( -ns >> 32 );
    

    if(!SetWaitableTimer(htimer, &liDueTime, 0, NULL, NULL, TRUE))
    {

        CloseHandle(htimer);

        return false;

    }


    WaitForSingleObject(htimer, INFINITE);
    
    CloseHandle(htimer);

    
    return true;

}

double map_value(double value, double fromMin, double fromMax, double toMin, double toMax)
{

    if (value < fromMin) {
        value = fromMin;
    } else if (value > fromMax) {
        value = fromMax;
    }

    double ratio = (value - fromMin) / (fromMax - fromMin);

    double mappedValue = toMin + (toMax - toMin) * ratio;

    return mappedValue;
    
}
