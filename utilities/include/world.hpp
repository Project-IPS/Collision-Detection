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
    World() {};
    std::vector<Rectangle> shapes;
    std::vector<PotentialContact> collisionArray;
    Circle pointer;
    vec2 prevPos;
    vec2 currPos;

    void addShapes(Rectangle& obj)
    {
        shapes.push_back(obj);
    }
    void setCircle(Circle& Pointer, vec2 prevpos)
    {
        pointer = Pointer;
        currPos = pointer.center;
        prevPos = prevpos;
        //pointer.calculateAABB();

    }

    void Compute()
    { 
        std::cout<<"The initial Position is "<<currPos.x<<" "<<currPos.y<<std::endl;
        printAABB(pointer.BoundingVolume);
        BVH bvh =  BVH(shapes);
       
        bvh.buildTree(bvh.root, 0, shapes.size() - 1);
        
        //printbuildtree(bvh.root);
        
        getPotentialContacts(bvh.root, collisionArray, pointer);
        printcollisions(collisionArray); 
       
        Dispatcher dispatch;
        dispatch.dispatch(collisionArray);
        std::vector<PotentialContact> narrowphaseArray = dispatch.getcollisionInfo();
        printcollisions(narrowphaseArray); 
        
        for(int i =0; i< narrowphaseArray.size(); i++)
        {
            resolveCollision(currPos, prevPos, narrowphaseArray[i].body2 , narrowphaseArray[i].body1);

        }
        std::cout<<"The changed position is "<<currPos.x<<" "<<currPos.y<<std::endl;


        // call dispatcher to narrowphase
        
        
        
    } 
};
#endif