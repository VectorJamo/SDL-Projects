#ifndef VEC2_H
#define VEC2_H

union vec2
{
    struct{
        float x, y;
    };
    struct{
        float width, height;
    };

    vec2();
    vec2(float x, float y);

    void Normalize();
};

#endif