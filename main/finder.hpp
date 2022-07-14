#ifndef FINDER_HPP
#define FINDER_HPP

#include"shapes.hpp"
#include "world.hpp"
#include "vec2.hpp"

class Finder
{
    public:
    Finder() = default;
    Finder(World& world, Circle c, vec2 prev) : collisionWorld(world), c(c), prev(prev)
    {
        
    }

    vec2 calculate()
    {
        collisionWorld.setCircle(c, prev);
        collisionWorld.Compute();
        return collisionWorld.currPos;

    }


    private:
    World collisionWorld;
    Circle c;
    vec2 prev;

};

#endif