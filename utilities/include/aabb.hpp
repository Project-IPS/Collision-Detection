#ifndef AABB_H
#define AABB_H

#include"vec2.hpp"
#include <vector>

class AABB
{
    public:
    vec2 min;
    vec2 max;

    AABB(): min(vec2(0.0f, 0.0f)), max(vec2(0.0f, 0.0f)){}
    AABB(vec2& min, vec2& max): min(min), max(max) {}

    bool overlapsWith(AABB& other)
    {
        return max.x > other.min.x &&
			   min.x < other.max.x &&
			   max.y > other.min.y &&
			   min.y < other.max.y;
    } 
};
#endif