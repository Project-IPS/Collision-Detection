#ifndef PRINT_H
#define PRINT_H
#include"shapes.hpp"
#include"broadphase.hpp"
#include "bvhnode.hpp"


void printAABB(AABB& aabb)
{
    std::cout<<" AABB"<<std::endl;
    std::cout<<"Max is ("<<aabb.max.x<<","<<aabb.max.y<<")"<<std::endl;
    std::cout<<"Min is ("<<aabb.min.x<<","<<aabb.min.y<<")"<<std::endl<<std::endl;
}

void printshape(Rectangle& shape, int index)
{
    std::cout<<" Shape "<<index<<std::endl;
    for(int j =0; j<shape.points.size();j++)
    {
        std::cout<<"Point"<<j<<"is("<<shape.points[j].x<<","<<shape.points[j].y<<")"<<std::endl;
    }
    std::cout<<"Center is("<<shape.center.x<<","<<shape.center.y<<")"<<std::endl;
    printAABB(shape.BoundingVolume);
    std::cout<<std::endl;
}

void printCircle(Circle& c,int index)
{
    std::cout<<"Circle "<<index<<std::endl;
    std::cout<<"Center "<<c.center.x<< " "<<c.center.y<<std::endl;
    std::cout<<"Radius "<<c.radius<<std::endl;
}

void printshapes(std::vector<Rectangle>& shapes)
{
    std::cout<<"Shapes: "<<std::endl;
    for(int i=0;i<shapes.size();i++)
    {
         printshape(shapes[i], i+1);
    }
    std::cout<<std::endl;
}


   
void printnodes(std::shared_ptr<BVHnode> node, int index)
{
    std::cout<<"Node "<<index<<std::endl;
    std::cout<<"Body contained:"<<std::endl;

    if(isLeaf(node))
    {
    printshape(node->body, 1);
    }

    printAABB(node->enclosedAABB);
    std::cout<<std::endl;
}

void printcollisions(std::vector<PotentialContact>& collisionArray)
{
    std::cout<<"Number of Collisions: "<<collisionArray.size()<<std::endl;
    for (int i=0;i<collisionArray.size();i++)
    {
        std::cout<<"Collision between the following shapes:"<<std::endl;
        PotentialContact p = collisionArray[i];
        printshape(p.body2, 2);
        printCircle(p.body1, 1);
        std::cout<<std::endl;
    }
}

void printtree(std::shared_ptr<BVHnode> node, int index)
{
    if(isLeaf(node))
    {
        printnodes(node, index);
        return;
    }

    else
    {
        printnodes(node, index);
        printtree(node->left, index+1);
        printtree(node->right, index+1);
    }
}
void printbuildtree(std::shared_ptr<BVHnode> node)
{
    std::cout<<"The build tree is traversed in the following order:"<<std::endl;
    printtree(node, 1);
    std::cout<<std::endl;
}
#endif

