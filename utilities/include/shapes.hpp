#ifndef SHAPES_H
#define SHAPES_H

#include"vec2.hpp"
#include<vector>
#include"aabb.hpp"

class Rectangle
{
    public:
    std::vector<vec2> points;
    vec2 center;
    AABB BoundingVolume;

    Rectangle() = default;
    Rectangle (std::vector<vec2>& points): points(points) 
    {
        
        calculateAABB();
    }

    void calculateAABB()
    {
        float minx, miny, maxx, maxy;
        minx = points[0].x;
        miny = points[0].y;
        maxx = minx;
        maxy = miny;

        for (int i=1; i<4; i++)
        {
            float temp_x, temp_y;
            temp_x = points[i].x;
            temp_y = points[i].y;

            if(minx > temp_x) minx = temp_x;
            if(maxx < temp_x) maxx = temp_x;

            if(miny > temp_y) miny = temp_y;
            if(maxy < temp_y) maxy = temp_y;
        }

        vec2 min = vec2(minx, miny);
        vec2 max = vec2(maxx, maxy);
        BoundingVolume = AABB(min, max);
    }  
};

class Circle
{
    public:
    vec2 center;
    float radius;
    AABB BoundingVolume;
    Circle() = default;
    Circle(vec2& center, float& radius): center(center), radius(radius) {
        calculateAABB();
    }

    void calculateAABB()
    {
        float minx, miny, maxx, maxy;
        minx = center.x - radius;
        maxx = center.x + radius;
        miny = center.y - radius;
        maxy = center.y + radius;

        vec2 min = vec2(minx, miny);
        vec2 max = vec2(maxx, maxy);
        BoundingVolume = AABB(min, max); 
    }
};

#endif