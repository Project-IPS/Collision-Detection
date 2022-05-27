#ifndef BVH_H
#define BVH_H

#include<algorithm>
#include"bvhnode.hpp"
#include"shapes.hpp"
#include<vector>
#include<iostream>
#include"print.hpp"

class BVH
{
    public:
    std::vector<Rectangle> shapes;
    std::shared_ptr<BVHnode> root = std::make_shared<BVHnode>();

    enum Axis 
    {
		X,
		Y,
		Z,
	};

    BVH() = default;
    BVH(std::vector<Rectangle>& shapes): shapes(shapes) {}

    void buildTree(std::shared_ptr<BVHnode> node, int start, int end)
    {
        if(start == end)
        {
            node->enclosedAABB = shapes[start].BoundingVolume;
            node->body = shapes[start];    
        }
        else
        {
            node->enclosedAABB = calculateenclosedAABB(start, end);
            
            Axis axis = getMedianCuttingAxis(node);
            sort(axis, start, end);
            
            auto leftNode = std::make_shared<BVHnode>();
            auto rightNode = std::make_shared<BVHnode>();
            node->left = leftNode;
            node->right = rightNode;

            buildTree(leftNode, start, start +(end - start)/2);
            buildTree(rightNode, start + 1 + (end - start)/2, end);
        }


    }

    void sort( Axis& axis, int start, int end)
    {
        if(axis == X)
        {
            std::sort(std::next(shapes.begin(), start), std::next(shapes.begin(), end + 1), [](const Rectangle& lhs, const Rectangle& rhs){
            return lhs.center.x < rhs.center.x;}); 
        }
        else
        {
            std::sort(std::next(shapes.begin(), start), std::next(shapes.begin(), end + 1), [](const Rectangle& lhs, const Rectangle& rhs){
            return lhs.center.y < rhs.center.y;});    
        }    
    }

    Axis getMedianCuttingAxis( std::shared_ptr<BVHnode> node)
    {
        float x_width = node->enclosedAABB.max.x - node->enclosedAABB.min.x;
        float y_width = node->enclosedAABB.max.y - node->enclosedAABB.min.y;

        if(x_width > y_width) return X;
        else return Y;
    }

    AABB calculateenclosedAABB( int start, int end)
    {
        float minx, miny, maxx, maxy;
        minx = shapes[start].BoundingVolume.min.x;
        miny = shapes[start].BoundingVolume.min.y;
        maxx = shapes[start].BoundingVolume.max.x;
        maxy = shapes[start].BoundingVolume.max.y;

        for(int i=start + 1; i< end; i++)
        {
            float temp_minx, temp_miny, temp_maxx, temp_maxy;

            temp_minx = shapes[i].BoundingVolume.min.x;
            temp_miny = shapes[i].BoundingVolume.min.y;
            temp_maxx = shapes[i].BoundingVolume.max.x;
            temp_maxy = shapes[i].BoundingVolume.max.y;

            if(minx > temp_minx) minx = temp_minx;
            if(miny > temp_miny) miny = temp_miny;
            if(maxx < temp_maxx) maxx = temp_maxx;
            if(maxy < temp_maxy) maxy = temp_maxy;
        }

        vec2 max = vec2(maxx, maxy);
        vec2 min = vec2(minx, miny);
        AABB enclosedAABB = AABB(min, max);
        return enclosedAABB;
    }  
};
#endif