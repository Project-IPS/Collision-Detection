#include "world.hpp"
#include "shapes.hpp"
#include "vec2.hpp"
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include "config.hpp"
#include"print.hpp"
#include "finder.hpp"
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
    //config.setRectangles(points);


    std::vector<vec2> points1;
    points1.push_back(vec2(2,0));
    points1.push_back(vec2(3,-1));
    points1.push_back(vec2(4,0));
    points1.push_back(vec2(3,1));
   // vec2 center = vec2(0,0);
    auto rect = Rectangle(points1);
    collisionWorld.addShapes(rect);

    // std::vector<vec2> points2;
    // points2.push_back(vec2(-2,-2));
    // points2.push_back(vec2(2,-2));
    // points2.push_back(vec2(2,2));
    // points2.push_back(vec2(-2,2));
    // //vec2 center2 = vec2(0.25,0);
    // auto rect2 = Rectangle(points2);
    // collisionWorld.addShapes(rect2);
    
    vec2 center =vec2(3.5,0.25);
    float radius = 0.0014;
    auto c = Circle(center, radius);
    //config.setCircle(center, radius);
    //collisionWorld.setCircle(c, vec2(2,0));

    //Define shapes
    // for(int i = 0; i<config.getNumRec(); i++)
    // {
    //     auto rect = Rectangle(points[i]);
    //     collisionWorld.addShapes(rect);
    // }

    //auto c = Circle(center, radius);
    Finder fin = Finder(collisionWorld, c, vec2(0, 0));
    vec2 newPos = fin.calculate();
    
}