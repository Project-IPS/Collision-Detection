#include "world.hpp"
#include "shapes.hpp"
#include "vec2.hpp"
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
using namespace rapidjson;
int main()
{

  //parsing and reading json file
  std::ifstream ifs ;
  ifs.open(R"(/mnt/c/projects/Collision-Detection/trial.json)");

   if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        return EXIT_FAILURE;
    }

    IStreamWrapper isw { ifs };
   //const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    Document document{};
    document.ParseStream(isw);
    const Value& shapes = document["shapes"];
    const Value& Rec = shapes["Rectangle"];
    const Value& Cir = shapes["Circle"];
    const Value& cen = Cir["center"];
    const Value& p1 = Rec["p1"];
    const Value& p2 = Rec["p2"];
    const Value& p3 = Rec["p3"];
    const Value& p4 = Rec["p4"];
    const Value& p5 = Rec["p5"];

   // printf("hello = %i\n", p1["x"].GetInt());
    
  
    

    //defining the collision world with the obtained value
    World collisionWorld;

    //Circle 
    vec2 centerc = vec2(cen["x"].GetInt(),cen["y"].GetInt());
    float radius = Cir["radius"].GetInt();
    Circle c = Circle(centerc, radius);
    collisionWorld.setCircle(c, vec2(-2,0));



    // shape-1
    std::vector<vec2> points1;
    points1.push_back(vec2(p1["x"].GetInt(),p1["y"].GetInt()));
    points1.push_back(vec2(p2["x"].GetInt(),p2["y"].GetInt()));
    points1.push_back(vec2(p3["x"].GetInt(),p3["y"].GetInt()));
    points1.push_back(vec2(p4["x"].GetInt(),p4["y"].GetInt()));
    vec2 center = vec2(p5["x"].GetInt(),p5["y"].GetInt());
    auto rect = Rectangle(points1, center);
    collisionWorld.addShapes(rect);

 

    // compute all collision
    collisionWorld.Compute();
}