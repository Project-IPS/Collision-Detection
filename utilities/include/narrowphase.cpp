#ifndef NARROWPHASE_HPP
#define NARROWPHASE_HPP
#include<vector>
#include<cmath>
#include"shapes.hpp"
#include"vec2.hpp"
#include"broadphase.hpp"


struct Collisiondata
{
    public:
    std::vector<PotentialContact> dataArray;
    Collisiondata() = default;

};


class Checkcollisions
{
    public:
    Checkcollisions() = default;

    bool circle_rectangle(Circle& c, Rectangle& r)
    {
        
        // check for collision and update collisionInfo array
        return pointInRectangle( c.center, r) ||
        checksegmentIntersection(c, r.points[0], r.points[1]) ||
        checksegmentIntersection(c, r.points[1], r.points[2]) ||
        checksegmentIntersection(c, r.points[2], r.points[3]) ||
        checksegmentIntersection(c, r.points[3], r.points[0]);
    }

    bool pointInRectangle(vec2 centerofcircle, Rectangle rect)
    {
        // code to detect whether a point is inside the rectangle or not.Assuming counterclockwise function
        bool test = true;
        for( int i = 0; i< 4; i++)
        {
            float x1 = rect.points[i].x;
            float x2 = rect.points[(i+1)%4].x;
            float y1 = rect.points[i].y;
            float y2 = rect.points[(i+1)%4].y;
            float A = -( y2 - y1);
            float B = x2 - x1;
            float C = -(A*x1 + B*y1);
            float D = A*centerofcircle.x + B*centerofcircle.y + C;
            test = test && (D>=0);
        }
        return test;
    }

    bool ptInsideCircle(Circle& c, vec2& pt)
    {
    if(std::abs(std::sqrt((c.center.x - pt.x)*(c.center.x - pt.x) + (c.center.y - pt.y)*(c.center.y - pt.y) )) < c.radius) return true;
    else return false;
    }

    float perpendicularDistance(float A, float B, float C, vec2 point)
    {
        float distance = std::abs(A*point.x +B*point.y + C)/(std::abs(std::sqrt(A*A +B*B)));
        return distance;
    }
    void findline(float &A, float &B, float &C, vec2& pt1, vec2& pt2)
    {
    A = pt2.y - pt1.y;
    B = pt1.x - pt2.x;
    C = pt1.y*(pt2.x - pt1.x) - pt2.x*(pt2.y - pt1.y);

    }
    
    bool checksegmentIntersection(Circle c, vec2& pt1, vec2& pt2)
    {
    if(ptInsideCircle(c, pt1) || ptInsideCircle(c, pt2)) return true;
    float m, n, p;
    findline(m, n, p, pt1, pt2);
    float distance = perpendicularDistance(m, n, p, c.center);
    return distance <= c.radius;
    }

    
};

class Dispatcher
{
    public:
    Dispatcher() = default;
    Collisiondata collisionInfo; 
    std::vector<PotentialContact> getcollisionInfo();

    void dispatch(std::vector<PotentialContact> receieved)
    {
     
        for(int i =0; i<receieved.size(); i++){
        Circle c = receieved[i].body1;
        Rectangle r = receieved[i].body2;
        Checkcollisions checker;
        bool flag = checker.circle_rectangle(c, r);
        if(flag == true)
        {
            std::cout<<"Collision detected!"<<std::endl;
            collisionInfo.dataArray.push_back(PotentialContact(c, r));
        }
        }
        
        
    }   
};
std::vector<PotentialContact> Dispatcher::getcollisionInfo()
{
    return collisionInfo.dataArray;
}

#endif