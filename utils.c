#include "utils.h"


float lerp(float start, float end, float ratio)
{

    return start + ratio * (end - start);

}

float lerp_threshold(float start, float end, float ratio, float threshold)
{

    float interpolated_value = start + ratio * (end - start);

    if (fabsf(interpolated_value) <= threshold)
    {

        interpolated_value = end;

    }


    return interpolated_value;

}
