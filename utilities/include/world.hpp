#ifndef WORLD_H
#define WORLD_H

#include<vector>
#include"shapes.hpp"
#include"aabb.hpp"
#include"bvh.hpp"
#include"bvhnode.hpp"
#include"broadphase.hpp"
#include<iostream>
#include "print.hpp"
#include "narrowphase.cpp"
#include"resolution.hpp"
class World
{
    public:
    std::vector<Rectangle> shapes;
    std::vector<PotentialContact> collisionArray;
    Circle pointer;
    vec2 prevPos;
    vec2 currPos;

    void addShapes(Rectangle& obj)
    {
        shapes.push_back(obj);
    }

    void Compute()
    { 
        BVH bvh =  BVH(shapes);
        bvh.buildTree(bvh.root, 0, shapes.size() - 1);
        getPotentialContacts(bvh.root, collisionArray, pointer);
        Dispatcher dispatch;
        dispatch.dispatch(collisionArray);
        std::vector<PotentialContact> narrowphaseArray = dispatch.getcollisionInfo();

        for(int i =0; i< narrowphaseArray.size(); i++)
        {
            resolveCollision(currPos, prevPos, narrowphaseArray[i].body2 , narrowphaseArray[i].body1);

        }


        // call dispatcher to narrowphase
        printshapes(shapes);
        printbuildtree(bvh.root);
        printcollisions(collisionArray);
    } 
};
#endif