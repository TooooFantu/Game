
#include "rect.h"
#include "texture.h"
#include "compute.h"

#include <SDL.h>


using namespace std;




TRect::TRect()
{
    rectPosX = 0;
    rectPosY = 0;

    rectVelocityX = 0;
    rectVelocityY = 0;

    mColliders.w = 0;
    mColliders.h = 0;
}


void TRect::setPosition(int x, int y)
{
    rectPosX = x;
    rectPosY = y;
    shiftColliders();
}


void TRect::setRectSize(int w, int h)
{
    mColliders.w = w;
    mColliders.h = h;
}


void TRect::setRectVelocity(int vX, int vY)
{
    rectVelocityX = vX;
    rectVelocityY = vY;
}


bool TRect::inZone(SDL_Rect& zone)
{
    if (mColliders.x + mColliders.w < zone.x || mColliders.x > zone.x + zone.w || mColliders.y + mColliders.h < zone.y || mColliders.y > zone.y + zone.h)
    {
        return false;
    }

    return true;
}


bool TRect::inRect(SDL_Rect zone)
{
    if (rectPosY > zone.y)
    {
        return true;
    }
    return false;
}


int TRect::getMidX()
{
    return mColliders.x + (mColliders.w / 2);
}


int TRect::getMidY()
{
    return mColliders.y + (mColliders.h / 2);
}


int TRect::getHeight()
{
    return mColliders.h;
}


void TRect::moveRect(SDL_Rect box, SDL_Rect& other, vector <SDL_Rect> wall, float timeStep)
{
    rectPosX += rectVelocityX * 60 * timeStep;
    shiftColliders();

    if (rectPosX < box.x || rectPosX + mColliders.w > box.x + box.w || inZone(other) || checkCollision(mColliders, wall))
    {
        rectPosX -= rectVelocityX * 60 * timeStep;
        shiftColliders();
    }

    rectPosY += rectVelocityY * 60 * timeStep;
    shiftColliders();

    if (rectPosY < box.y || rectPosY + mColliders.h > box.y + box.h || inZone(other) || checkCollision(mColliders, wall))
    {
        rectPosY -= rectVelocityY * 60 * timeStep;
        shiftColliders();
    }
}


void  TRect::moveObject(SDL_Rect box, float timeStep)
{
    rectPosX += rectVelocityX * 60 * timeStep;
    shiftColliders();

    if (rectPosX < box.x || rectPosX + mColliders.w > box.x + box.w)
    {
        rectPosX -= rectVelocityX * 60 * timeStep;
        rectVelocityX = - rectVelocityX;
        shiftColliders();
    }

    rectPosY += rectVelocityY * 60 * timeStep;
    shiftColliders();

    if (rectPosY < box.y || rectPosY + mColliders.h > box.y + box.h)
    {
        rectPosY -= rectVelocityY * 60 * timeStep;
        rectVelocityY = -rectVelocityY;
        shiftColliders();
    }
}


bool TRect::moveObjectDown(int velocity, int boxYline, float timeStep)
{
    rectPosY += velocity * 60 * timeStep;
    shiftColliders();

    if (rectPosY + mColliders.h > boxYline)
    {
        mColliders.h -= velocity * 60 * timeStep;
    }
    if (mColliders.h <= 0)
    {
        return false;
    }
    return true;
}


void TRect::render(TTexture rect, bool moveRender, bool down, double angle)
{
    SDL_Rect renderClip = {0, 0, mColliders.w, mColliders.h};
    SDL_Rect* mRenderClip = NULL;

    if (moveRender)
    {
        mRenderClip = &mColliders;

        if (down)
        {
            mRenderClip->y = 0;
        }
    }
    else
    {
        mRenderClip = &renderClip;
    }

    rect.render(rectPosX, rectPosY, mRenderClip, angle);

    mRenderClip = NULL;
}


void TRect::shiftColliders()
{
    mColliders.x = rectPosX;
    mColliders.y = rectPosY;
}


SDL_Rect& TRect::getColliders()
{
    return mColliders;
}
