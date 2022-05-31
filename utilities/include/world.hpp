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

class World
{
    public:
    std::vector<Rectangle> shapes;
    std::vector<PotentialContact> collisionArray;

    void addShapes(Rectangle& obj)
    {
        shapes.push_back(obj);
    }

    void Compute()
    { 
        BVH bvh =  BVH(shapes);
        bvh.buildTree(bvh.root, 0, shapes.size() - 1);
        getPotentialContacts(bvh.root, collisionArray);
        // call dispatcher to narrowphase
        printshapes(shapes);
        printbuildtree(bvh.root);
        printcollisions(collisionArray);
    } 
};
#endif