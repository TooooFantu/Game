
#include "compute.h"
#include "structure.h"
#include "const.h"

#include <SDL.h>
#include <math.h>


using namespace std;



bool checkCollision(LCircle& a, LCircle& b)
{
    int totalRadiusSquared = a.r + a.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    return distanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared;
}


bool checkCollision(LCircle& a, vector <SDL_Rect>& b)
{
    for (int i = 0; i < b.size(); i++)
    {
        LPoint point;
        point.setPoint(a.x, a.y);
        LPoint closestPoint;
        closestPoint.getClosestPoint(point, b[i]);

        if (distanceSquared(a.x, a.y, closestPoint.x, closestPoint.y) < a.r * a.r)
        {
            return true;
        }
    }
    return false;
}


bool checkCollision(LCircle& a, SDL_Rect& b)
{
    LPoint point;
    point.setPoint(a.x, a.y);
    LPoint closestPoint;
    closestPoint.getClosestPoint(point, b);

    if (distanceSquared(a.x, a.y, closestPoint.x, closestPoint.y) < a.r * a.r)
    {
        return true;
    }
    return false;
}


bool checkCollision(SDL_Rect& a, vector <SDL_Rect>& b)
{
    for (int i = 0; i < b.size(); i++)
    {
        if (  ((a.x <= b[i].x + b[i].w && a.x + a.w >= b[i].x) || (b[i].x <= a.x + a.w && b[i].x + b[i].w >= a.x )) && ((a.y <= b[i].y + b[i].h && a.y + a.h > b[i].y) || (b[i].y <= a.y + a.h && b[i].y + b[i].h >= a.y) ))
        {
            return true;
        }
    }
    return false;
}


bool changeVelX(LCircle& a, vector <SDL_Rect>& b, LPoint flashBack)
{
    for (int i = 0; i < b.size(); i++)
    {
        LPoint point;
        point.setPoint(a.x, a.y);
        LPoint closestPoint;
        closestPoint.getClosestPoint(point , b[i]);

        int distanceX = abs(a.x - closestPoint.x);
        int distanceY = abs(a.y - closestPoint.y);

        if (distanceSquared(a.x, a.y, closestPoint.x, closestPoint.y) < a.r * a.r)
        {
            if (distanceX > distanceY && distanceY == 0)
            {
                return true;
            }
            else
            {
                closestPoint.getClosestPoint(flashBack, b[i]);

                distanceX = abs(flashBack.x - closestPoint.x);
                distanceY = abs(flashBack.y - closestPoint.y);

                if (distanceX >= distanceY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


bool changeVelY(LCircle& a, vector <SDL_Rect>& b, LPoint flashBack)
{
    for (int i = 0; i < b.size(); i++)
    {
        LPoint point;
        point.setPoint(a.x, a.y);
        LPoint closestPoint;
        closestPoint.getClosestPoint(point , b[i]);

        int distanceX = abs(a.x - closestPoint.x);
        int distanceY = abs(a.y - closestPoint.y);

        if (distanceSquared(a.x, a.y, closestPoint.x, closestPoint.y) < a.r * a.r)
        {
            if (distanceX < distanceY && distanceX == 0)
            {
                return true;
            }
            else
            {
                closestPoint.getClosestPoint(flashBack, b[i]);

                distanceX = abs(flashBack.x - closestPoint.x);
                distanceY = abs(flashBack.y - closestPoint.y);

                if (distanceX < distanceY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


double distanceSquared(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    return deltaX*deltaX + deltaY*deltaY;
}


void getVel(int& velX, int& velY, Unit32 a, int velocity)
{
    double x = (double) a*3.14159/180;

    double vX = sin(x)*velocity;
    double vY = cos(x)*velocity;

    velX = round(vX);
    velY = - round(vY);
}
