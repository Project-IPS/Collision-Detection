#ifndef NARROWPHASE_HPP
#define NARROWPHASE_HPP
#include<vector>
#include"shapes.hpp"

struct Contact
{
    // stores information about the detected collision contact point
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
        // code to detect whether a point is inside the rectangle or not
    }

    bool intersectCircle(Circle c, vec2 A, vec2 B)
    {
        // code to detect whether a ray intersects a circle or not
    }
};



#endif