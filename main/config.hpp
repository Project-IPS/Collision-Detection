#include "world.hpp"
#include "shapes.hpp"
#include "vec2.hpp"
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include<iostream>
using namespace rapidjson;

class Config
{
    public:
    Config()= default;
    std::ifstream ifs;
    Document document{};
    void setup();
    int getNumRec();
    void setRectangles(std::vector<std::vector<vec2>>& points);
    void setCircle(vec2& p1, float& radius);
    int numRec;
};

void Config::setup()
{
    ifs.open(R"(/mnt/c/projects/Collision-Detection/trial.json)"); 
    IStreamWrapper isw { ifs };
    document.ParseStream(isw);

}

int Config::getNumRec()
{
    const Value& a = document["Rectangles"];
    numRec = a.Size();
    return numRec;
}

void Config::setRectangles(std::vector<std::vector<vec2>>& points)
{
    const Value& a = document["Rectangles"];
    int i = 0;
    while(i<numRec)
    {
        const Value& b = a[i];  
        
        for(SizeType j = 0; j < b.Size(); j++)
        {
            points[i].push_back(vec2(b[j]["x"].GetFloat(),b[j]["y"].GetFloat()));
        }
        i++;
    }

}

void Config:: setCircle(vec2& p1, float& radius)
{
    const Value& a = document["Circle"];
    p1.x = a["p1"]["x"].GetFloat();
    p1.y = a["p1"]["y"].GetFloat();
    radius = a["radius"].GetFloat();

}