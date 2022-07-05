#include "world.hpp"
#include "shapes.hpp"
#include "vec2.hpp"
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include "config.hpp"
#include"print.hpp"
using namespace rapidjson;
int main()
{   
   

  
    //defining the collision world with the obtained value
    World collisionWorld;
    
    //define a config object
    Config config;
    config.setup();
    int NumRec = config.getNumRec();
    //Initialize and get data
    std::vector<std::vector<vec2>> points(NumRec, std::vector<vec2>(4));
    config.setRectangles(points);
    
    vec2 center;
    float radius;
    config.setCircle(center, radius);

    //Define shapes
    for(int i = 0; i<config.getNumRec(); i++)
    {
        auto rect = Rectangle(points[i]);
        collisionWorld.addShapes(rect);
    }
    auto c = Circle(center, radius);
    collisionWorld.setCircle(c, vec2(-2, 0));
    
    printshapes(collisionWorld.shapes);
    //Compute all collision
   collisionWorld.Compute();
}