#ifndef BROADPHASE_H
#define BROADPHASE_H

#include"bvhnode.hpp"
#include"bvh.hpp"
#include "shapes.hpp"

struct PotentialContact
{
    public:
    Circle body1;
    Rectangle body2;
    PotentialContact(Circle& body1, Rectangle& body2): body1(body1), body2(body2){}
};

bool isLeaf(std::shared_ptr<BVHnode> node)
{
    return (node->left == nullptr && node->right == nullptr);
}


void getPotentialContacts(std::shared_ptr<BVHnode>node,  std::vector<PotentialContact>& collisionArray, Circle c)
{
    if (!(node->enclosedAABB.overlapsWith(c.BoundingVolume))) return;

    if(isLeaf(node)) 
    {
        PotentialContact collision(c, node->body);
        collisionArray.push_back(collision);
    }
    getPotentialContacts(node->left, collisionArray, c);
    getPotentialContacts(node->right, collisionArray, c);

}
#endif