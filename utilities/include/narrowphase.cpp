#ifndef NARROWPHASE_HPP
#define NARROWPHASE_HPP
#include<vector>
#include<cmath>
#include"shapes.hpp"
#include"vec2.hpp"
struct Contact
{
    // stores information about the detected collision contact point
    vec2 contactPoint;
    vec2 normal;
    double penetrationDepth;
};

struct Collisiondata
{
    public:
    std::vector<Contact> dataArray;

};

class Dispatcher
{
    public:
    std::vector<Collisiondata> collisionInfo; 

    void dispatch(Circle& c, Rectangle& r)
    {
        //dispatches objects to right functions
    }   
};

class Checkcollisions
{
    public:

    bool circle_rectangle(Circle& c, Rectangle& r)
    {
        // check for collision and update collisionInfo array
        return pointInRectangle( c.center, r) ||
        intersectCircle(c, r.points[0], r.points[1]) ||
        intersectCircle(c, r.points[1], r.points[2]) ||
        intersectCircle(c, r.points[2], r.points[3]) ||
        intersectCircle(c, r.points[3], r.points[0]);
    }

    bool pointInRectangle(vec2 centerofcircle, Rectangle rect)
    {
        // code to detect whether a point is inside the rectangle or not.Assuming counterclockwise function
        bool test = true;
        for( int i = 0; i< 4; i++)
        {
            float x1 = rect.points[i].x;
            float x2 = rect.points[(i+1)%4].x;
            float y1 = rect.points[i].y;
            float y2 = rect.points[(i+1)%4].y;
            float A = -( y2 - y1);
            float B = x2 - x1;
            float C = -(A*x1 + B*y1);
            float D = A*centerofcircle.x + B*centerofcircle.y + C;
            test = test && (D>=0);
        }
        return test;
    }

    bool intersectCircle(Circle c, vec2 p1, vec2 p2)
    {
        // code to detect whether a ray intersects a circle or not
        float A = p2.y - p1.y;
        float B = p1.x - p2.x;
        float C = p1.y*(p2.x - p1.x) - p2.x*(p2.y - p1.y);

        return (perpendicularDistance(A, B, C, c.center) <= c.radius);
    }

    float perpendicularDistance(float A, float B, float C, vec2 point)
    {
        float distance = std::abs(A*point.x +B*point.y + C)/(std::abs(std::sqrt(A*A +B*B)));
        return distance;
    }
};
#endif