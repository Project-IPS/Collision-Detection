#ifndef VEC2_H
#define VEC2_H

struct vec2
{
    public:
    float x;
    float y;

    vec2() = default;
    vec2(float x_in, float y_in)
    {
        x = x_in;
        y = y_in;
    }
};

#endif