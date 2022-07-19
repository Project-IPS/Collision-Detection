#include"shapes.hpp"
#include"vec2.hpp"
#include <vector>
#include<cmath>
#include"iostream"
void findline(float &A, float &B, float &C, vec2& pt1, vec2& pt2)
{
    A = pt1.y - pt2.y;
    B = pt2.x - pt1.x;
    C = pt1.x*(pt2.y - pt1.y) - pt1.y*(pt2.x - pt1.x);

}
bool checkSide(float A, float B, float C, vec2 pt1, vec2 pt2 )
{
    bool a = A*pt1.x +B*pt1.y + C >0;
    bool b = A*pt2.x +B*pt2.y + C >0;
    return a == b;
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
bool checksegmentIntersection(Circle c, vec2& pt1, vec2& pt2)
{
    if(ptInsideCircle(c, pt1) || ptInsideCircle(c, pt2)) return true;
    float m, n, p;
    findline(m, n, p, pt1, pt2);
    float distance = perpendicularDistance(m, n, p, c.center);
    return distance < c.radius;
    
}


void resolveCollision(vec2& currPos, vec2& prevPos, Rectangle& rect, Circle& c)
{
    std::cout<<"Inside resolution"<<std::endl;
   
    std::vector<vec2> correctionDisplacements;
   // int flag = false;
    for ( int i = 3; i >= 0; i--)
    {
        //if(flag == true) break;
        int k = i;
        int j = (i+1)%4;
        float A, B, C;
        findline(A, B, C, rect.points[k], rect.points[j] );
        std::cout<<A<<" "<<B<<" "<<C<<std::endl;
        if(checksegmentIntersection(c, rect.points[k], rect.points[j]) || !(checkSide(A, B, C, currPos, prevPos)))
        {
            //flag = true;
            
            float allowedDistance = perpendicularDistance(A, B, C, prevPos) - c.radius;
            // if(abs(allowedDistance) <= 1e-2 )
            // {
            //     vec2 correction = vec2(prevPos.x - currPos.x, prevPos.y - currPos.y);
            //     correctionDisplacements.push_back(correction);
            //     continue;
            // }
            std::cout<<" allow "<<i<<perpendicularDistance(A, B, C, prevPos)<<std::endl;
            int al =  k-1;
            if(al == -1) al = 3;
            float disDisplacementVector = std::abs(std::sqrt((currPos.x - prevPos.x)*(currPos.x - prevPos.x) + (currPos.y - prevPos.y)*(currPos.y - prevPos.y)));
            vec2 displacementVector = vec2((currPos.x - prevPos.x)/disDisplacementVector, (currPos.y - prevPos.y)/disDisplacementVector); //unit vector
            float disNormalVector = std::abs(std::sqrt((rect.points[k].x - rect.points[al].x)*(rect.points[k].x - rect.points[al].x) + (rect.points[k].y - rect.points[al].y)*(rect.points[k].y - rect.points[al].y)));
            vec2 normalVector = vec2((rect.points[k].x - rect.points[al].x)/disNormalVector, (rect.points[k].y - rect.points[al].y)/disNormalVector);
            float discurrVector = std::abs(std::sqrt((rect.points[j].x - rect.points[k].x)*(rect.points[j].x - rect.points[k].x) + (rect.points[j].y - rect.points[k].y)*(rect.points[j].y - rect.points[k].y)));
             vec2 currVector = vec2((rect.points[j].x - rect.points[k].x)/discurrVector, (rect.points[j].y - rect.points[k].y)/discurrVector);
            float cosAngle = displacementVector.x*currVector.x + displacementVector.y*currVector.y;
            float sinAngle = std::abs(std::sqrt(1 - cosAngle*cosAngle));
            float travelledDistance = disDisplacementVector*sinAngle;
            float rollBack = (travelledDistance - allowedDistance); // length of the vector which will be used to displace the particle back in correct position
            vec2 correction =  vec2(normalVector.x*rollBack, normalVector.y*rollBack);
            std::cout<<" dis"<<i<<disDisplacementVector<<std::endl;
            std::cout<<" nor vec "<<i<<normalVector.x<<" "<<normalVector.y<<std::endl;
            std::cout<<" correction "<<i<<correction.x<<" "<<correction.y<<std::endl;
            correctionDisplacements.push_back(correction);
        }
    }
    for(int i =0; i<correctionDisplacements.size(); i++)
    {
        
        currPos = vec2(currPos.x + correctionDisplacements[i].x, currPos.y + correctionDisplacements[i].y );
    }
    

}
