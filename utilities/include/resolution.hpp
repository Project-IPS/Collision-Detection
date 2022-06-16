#include"shapes.hpp"
#include"vec2.hpp"
#include <vector>
#include<cmath>
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

void findline(float &A, float &B, float &C, vec2& pt1, vec2& pt2)
{
    A = pt2.y - pt1.y;
    B = pt1.x - pt2.x;
    C = pt1.y*(pt2.x - pt1.x) - pt2.x*(pt2.y - pt1.y);

}
void resolveCollision(vec2& currPos, vec2& prevPos, Rectangle& rect, Circle& c)
{
    vec2 displacement = vec2(currPos.x - prevPos.x, currPos.y - prevPos.y);
    std::vector<vec2> correctionDisplacements;
    for ( int i = 3; i >= 0; i--)
    {
        int k = i;
        int j = (i+1)%4;
        float A, B, C;
        findline(A, B, C, rect.points[k], rect.points[j] );
        if(checksegmentIntersection(c, rect.points[k], rect.points[j]) || !(checkSide(A, B, C, currPos, prevPos)))
        {
            
            float allowedDistance = perpendicularDistance(A, B, C, prevPos) - c.radius;
            float disDisplacementVector = std::abs(std::sqrt((currPos.x - prevPos.x)*(currPos.x - prevPos.x) + (currPos.y - prevPos.y)*currPos.y - prevPos.y));
            vec2 displacementVector = vec2((currPos.x - prevPos.x)/disDisplacementVector, (currPos.y - prevPos.y)/disDisplacementVector); //unit vector
            float disNormalVector = std::abs(std::sqrt((rect.points[k].x - rect.points[k - 1].x)*(rect.points[k].x - rect.points[k - 1].x) + (rect.points[k].y - rect.points[k-1].y)*rect.points[k].y - rect.points[k-1].y));
            vec2 normalVector = vec2((rect.points[k].x - rect.points[k-1].x)/disNormalVector, (rect.points[k].y - rect.points[k-1].y)/disNormalVector);
            float discurrVector = std::abs(std::sqrt((rect.points[j].x - rect.points[k].x)*(rect.points[j].x - rect.points[k].x) + (rect.points[j].y - rect.points[k].y)*rect.points[j].y - rect.points[k].y));
             vec2 currVector = vec2((rect.points[j].x - rect.points[k].x)/discurrVector, (rect.points[j].y - rect.points[k].y)/discurrVector);
            float cosAngle = displacementVector.x*currVector.x + displacementVector.y*currVector.y;
            float sinAngle = std::abs(std::sqrt(1 - cosAngle*cosAngle));
            float travelledDistance = disDisplacementVector*sinAngle;
            float rollBack = travelledDistance - allowedDistance; // length of the vector which will be used to displace the particle back in correct position
            vec2 correction =  vec2(normalVector.x*rollBack, normalVector.y*rollBack);
            correctionDisplacements.push_back(correction);
        }
    }
    for(int i =0; i<correctionDisplacements.size(); i++)
    {
        currPos = vec2(currPos.x + correctionDisplacements[i].x, currPos.y + correctionDisplacements[i].y );
    }
    

}
