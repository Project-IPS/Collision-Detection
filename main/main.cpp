#include "world.hpp"
#include "shapes.hpp"
#include "vec2.hpp"
int main()
{
    World collisionWorld;

    // shape-1
    std::vector<vec2> points2;
    points2.push_back(vec2(0.75,0.5));
    points2.push_back(vec2(0.75,-0.5));
    points2.push_back(vec2(-0.25,0.5));
    points2.push_back(vec2(-0.25,-0.5));
    vec2 center2 = vec2(0.25,0);
    auto rect2 = Rectangle(points2, center2);
    collisionWorld.addShapes(rect2);

    // shape-2
    std::vector<vec2> points1;
    points1.push_back(vec2(1,1));
    points1.push_back(vec2(1,-1));
    points1.push_back(vec2(-1,1));
    points1.push_back(vec2(-1,-1));
    vec2 center = vec2(0,0);
    auto rect = Rectangle(points1, center);
    collisionWorld.addShapes(rect);

     // shape-3
    std::vector<vec2> points3;
    points3.push_back(vec2(2,2));
    points3.push_back(vec2(2,-2));
    points3.push_back(vec2(-2,2));
    points3.push_back(vec2(-2,-2));
    auto rect3 = Rectangle(points3, center);
    collisionWorld.addShapes(rect3);

    // compute all collision
    collisionWorld.Compute();
}