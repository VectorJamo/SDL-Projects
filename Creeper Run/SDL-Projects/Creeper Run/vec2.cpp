#include "vec2.h"
#include <math.h>

vec2::vec2()
:x(0.0f), y(0.0f)
{
}
vec2::vec2(float x, float y)
:x(x), y(y)
{
}

void vec2::Normalize()
{
    float magnitude = sqrt(x*x + y*y);
    
    x = x / magnitude;
    y = y / magnitude;
}