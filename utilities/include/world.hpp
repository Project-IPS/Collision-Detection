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
        
        printbuildtree(bvh.root);
       // printshapes(shapes);
        
        getPotentialContacts(bvh.root, collisionArray, pointer);
        printcollisions(collisionArray); 
       
        Dispatcher dispatch;
        
        
        
        
        while(collisionArray.size() != 0)
        {
            

        for(int i =0; i< collisionArray.size(); i++)
        {
            
            collisionArray[i].body1.center = currPos;
            dispatch.dispatch(collisionArray[i]);
            PotentialContact narrowphase = dispatch.getcollisionInfo();
            resolveCollision(pointer.center, prevPos, narrowphase.body2 , narrowphase.body1);
            currPos =  pointer.center; 
            pointer.calculateAABB();
            std::cout<<"The  position is "<<pointer.center.x<<" "<<pointer.center.y<<std::endl;

        }
        
        collisionArray.clear();
       
        getPotentialContacts(bvh.root, collisionArray, pointer);
         printcollisions(collisionArray);
        

        }

        std::cout<<"The final  position is "<<pointer.center.x<<" "<<pointer.center.y<<std::endl;


        // call dispatcher to narrowphase
        
        
        
    } 
};
#endif