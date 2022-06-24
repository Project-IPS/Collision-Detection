#ifndef BROADPHASE_H
#define BROADPHASE_H

#include"bvhnode.hpp"
#include"bvh.hpp"
#include "shapes.hpp"
#include"iostream"
#include"aabb.hpp"
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
void hello()
{
    std::cout<<" inside hello"<<std::endl;
}


void getPotentialContacts(std::shared_ptr<BVHnode>node,  std::vector<PotentialContact>& collisionArray, Circle& c)
{
    if(node == nullptr) return;
   
     AABB P1 =node->enclosedAABB;
    AABB P2 = c.BoundingVolume;
    
    if (!(P1.overlapsWith(P2))) return;
    

    if(isLeaf(node)) 
    {
        PotentialContact collision(c, node->body);
        collisionArray.push_back(collision);
    }
    getPotentialContacts(node->left, collisionArray, c);
    getPotentialContacts(node->right, collisionArray, c);
   
    return;


}
#endif