#ifndef BROADPHASE_H
#define BROADPHASE_H

#include"bvhnode.hpp"
#include"bvh.hpp"
#include "shapes.hpp"

struct PotentialContact
{
    public:
    Rectangle body1;
    Rectangle body2;
    PotentialContact(Rectangle& body1, Rectangle& body2): body1(body1), body2(body2){}
};

bool isLeaf(std::shared_ptr<BVHnode> node)
{
    return (node->left == nullptr && node->right == nullptr);
}

void getPotentialContactsWith(std::shared_ptr<BVHnode>node1, std::shared_ptr<BVHnode>node2, std::vector<PotentialContact>& collisionArray )
{
    if (!(node1->enclosedAABB.overlapsWith(node2->enclosedAABB))) return;

    else if (isLeaf(node1) &&isLeaf(node2))
    {
        PotentialContact collission(node1->body, node2->body);
        collisionArray.push_back(collission);
    }

    else if (isLeaf(node1) && !isLeaf(node2))
    {
        getPotentialContactsWith(node2, node1, collisionArray);
    }

    else if (!isLeaf(node1) && isLeaf(node2))
    {
        getPotentialContactsWith(node1->left, node2, collisionArray);
        getPotentialContactsWith(node1->right, node2, collisionArray);
    }

    else 
    {
        getPotentialContactsWith(node1->left, node2->left, collisionArray);
        getPotentialContactsWith(node1->left, node2->right, collisionArray);
        getPotentialContactsWith(node1->right, node2->left, collisionArray);
        getPotentialContactsWith(node1->right, node2->right, collisionArray);

    }
}

void getPotentialContacts(std::shared_ptr<BVHnode>node, std::vector<PotentialContact>& collisionArray)
{
    if(isLeaf(node)) return;
    getPotentialContacts(node->left, collisionArray);
    getPotentialContacts(node->right, collisionArray);
    getPotentialContactsWith(node->left,node->right, collisionArray);
}
#endif