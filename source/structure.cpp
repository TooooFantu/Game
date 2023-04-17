#include "structure.h"

#include "texture.h"

#include <SDL.h>
#include <math.h>



//Struct vector:----------------------------------------------------------------------------------------------------------------

LVector::LVector()
{
    x = 0;
    y = 0;
}


double LVector::getLength()
{
    return sqrt(x * x + y * y);
}


//Struct point:----------------------------------------------------------------------------------------------------------------

void LPoint::setPoint(int a, int b)
{
    x = a;
    y = b;
}


void LPoint::getClosestPoint(LPoint& a, SDL_Rect& b)
{
    int cX, cY;

    if (a.x < b.x)
        {
            cX = b.x;
        }
        else if (a.x > b.x + b.w)
        {
            cX = b.x + b.w;
        }
        else
        {
            cX = a.x;
        }

        if (a.y < b.y)
        {
            cY = b.y;
        }
        else if (a.y > b.y + b.h)
        {
            cY = b.y + b.h;
        }
        else
        {
            cY = a.y;
        }
    setPoint(cX, cY);
}

//Struct FileGame:--------------------------------------------------

void TFileGame::free()
{
    logo.free();
    for (int i = 0; i < 2; i++)
    {
        playzone[i].free();
        object[i].free();
        wall[i].free();
        treasure[i].free();
    }
}
