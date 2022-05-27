#ifndef BVHNODE_H
#define BVHNODE_H

#include"aabb.hpp"
#include"vec2.hpp"
#include"shapes.hpp"
#include<vector>
#include<memory>

class BVHnode
{
    public:
    Rectangle body;
    std::shared_ptr<BVHnode> left;
    std::shared_ptr<BVHnode> right;
    AABB enclosedAABB;
    BVHnode() = default;
    BVHnode(Rectangle body): body(body) {}
};
#endif