
#ifndef UTILS_H
#define UTILS_H

    #include <math.h>
    
    
    #define DEG_TO_RAD (M_PI / 180.0)

    #define RAD_TO_DEG (180.0 / M_PI)

    
    extern float lerp(float start, float end, float ratio);

    extern float lerp_threshold(float start, float end, float ratio, float threshold);
    
#endif
