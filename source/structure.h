#pragma once

#include "texture.h"

#include <SDL.h>



struct LCircle
{
    int x, y;
    int r;
};


struct LVector
{
    int x, y;

    LVector();

    double getLength();
};


struct LPoint
{
    int x, y;

    void setPoint(int a, int b);

    void getClosestPoint(LPoint& a, SDL_Rect& b);
};


struct TFileGame
{
    TTexture playzone[2];

    TTexture object[2];

    TTexture wall[2];

    TTexture treasure[2];

    TTexture logo;

    void free();
};
