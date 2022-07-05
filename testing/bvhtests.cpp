#include <catch2/catch_test_macros.hpp>
#include"world.hpp"
#include"aabb.hpp"
#include"shapes.hpp"
#include"vec2.hpp"
#include"bvhnode.hpp"
#include"bvh.hpp"
#include"print.hpp"

TEST_CASE( "bvh", "[bvh]" ) {
    World collisionWorld;

    std::vector<vec2> points1;
    points1.push_back(vec2(-1,-1));
    points1.push_back(vec2(1,-1));
    points1.push_back(vec2(1,1));
    points1.push_back(vec2(-1,1));
    vec2 center = vec2(0,0);
    auto rect = Rectangle(points1);
    collisionWorld.addShapes(rect);

    std::vector<vec2> points2;
    points2.push_back(vec2(0.75,0.5));
    points2.push_back(vec2(0.75,-0.5));
    points2.push_back(vec2(-0.25,0.5));
    points2.push_back(vec2(-0.25,-0.5));
    vec2 center2 = vec2(0.25,0);
    auto rect2 = Rectangle(points2);
    collisionWorld.addShapes(rect2);

    auto shapes = collisionWorld.shapes;
    BVH bvh = BVH(shapes);
    bvh.buildTree(bvh.root, 0, shapes.size() - 1);
    
    
    Rectangle r;


    REQUIRE(bvh.root != nullptr);
    printbuildtree(bvh.root);
    
    
}

