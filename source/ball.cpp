
#include "ball.h"
#include "texture.h"
#include "structure.h"
#include "compute.h"

#include <SDL.h>


using namespace std;



TBall::TBall()
{
    ballPosX = 0;
    ballPosY = 0;

    BALL_WIDHT = 30;
    BALL_HEIGHT = 30;

    BALL_VEL = 5;

    ballVelX = 0;
    ballVelY = 0;

    velocity.x = 0;
    velocity.y = 0;
}


void TBall::setBallSize(int w, int h)
{
    BALL_WIDHT = w;
    BALL_HEIGHT = h;
}


void TBall::handleEventPlayer2(SDL_Event& e, bool& stopUp, bool& stopDown, bool& stopLeft, bool& stopRight)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                ballVelY -= BALL_VEL;
                stopUp = true;
                break;
            case SDLK_DOWN:
                ballVelY += BALL_VEL;
                stopDown = true;
                break;
            case SDLK_LEFT:
                ballVelX -= BALL_VEL;
                stopLeft = true;
                break;
            case SDLK_RIGHT:
                ballVelX += BALL_VEL;
                stopRight = true;
                break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                if (stopUp)
                {
                    ballVelY += BALL_VEL;
                }
                break;
            case SDLK_DOWN:
                if (stopDown)
                {
                    ballVelY -= BALL_VEL;
                }
                break;
            case SDLK_LEFT:
                if (stopLeft)
                {
                    ballVelX += BALL_VEL;
                }
                break;
            case SDLK_RIGHT:
                if (stopRight)
                {
                    ballVelX -= BALL_VEL;
                }
                break;
        }
    }
}


void TBall::handleEventPlayer1(SDL_Event& e, bool& stopUp, bool& stopDown, bool& stopLeft, bool& stopRight)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
                ballVelY -= BALL_VEL;
                stopUp = true;
                break;
            case SDLK_s:
                ballVelY += BALL_VEL;
                stopDown = true;
                break;
            case SDLK_a:
                ballVelX -= BALL_VEL;
                stopLeft = true;
                break;
            case SDLK_d:
                ballVelX += BALL_VEL;
                stopRight = true;
                break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
                if (stopUp)
                {
                    ballVelY += BALL_VEL;
                }
                break;
            case SDLK_s:
                if (stopDown)
                {
                    ballVelY -= BALL_VEL;
                }
                break;
            case SDLK_a:
                if (stopLeft)
                {
                    ballVelX += BALL_VEL;
                }
                break;
            case SDLK_d:
                if (stopRight)
                {
                    ballVelX -= BALL_VEL;
                }
                break;
        }
    }
}


void TBall::setPosition(int x, int y)
{
    ballPosX = x;
    ballPosY = y;
    shiftColliders();
}


int TBall::getPositionX()
{
    return ballPosX;
}


int TBall::getPositionY()
{
    return ballPosY;
}


int TBall::getVelX()
{
    return ballVelX;
}


int TBall::getVelY()
{
    return ballVelY;
}

void TBall::setBallVelocity(int vX, int vY)
{
    ballVelX = vX;
    ballVelY = vY;
}


void TBall::setBallVel(int v)
{
    BALL_VEL = v;
}

bool TBall::insideBox(SDL_Rect& box)
{
    if (ballPosX - mColliders.r < box.x || ballPosX + mColliders.r > box.x + box.w)
    {
        return false;
    }

    if (ballPosY - mColliders.r < box.y || ballPosY + mColliders.r > box.y + box.h)
    {
        return false;
    }

    return true;
}


bool TBall::areDeadCircle(LCircle& circle)
{
    return checkCollision(mColliders, circle);
}


bool TBall::areDeadRect(SDL_Rect& rect)
{
    return checkCollision(mColliders, rect);
}


void TBall::moveBall(vector <SDL_Rect>& wall, LCircle& circle,  SDL_Rect box, float timeStep)
{
    ballPosX += ballVelX * 60 * timeStep;
    shiftColliders();

    if (ballPosX - mColliders.r < box.x || ballPosX + mColliders.r > box.x + box.w || checkCollision(mColliders, wall) || checkCollision(mColliders, circle))
    {
        ballPosX -= ballVelX * 60 * timeStep;
        shiftColliders();
    }

    ballPosY += ballVelY * 60 * timeStep;
    shiftColliders();

    if (ballPosY - mColliders.r < box.y || ballPosY + mColliders.r > box.y + box.h || checkCollision(mColliders, wall) || checkCollision(mColliders, circle))
    {
        ballPosY -= ballVelY * 60 * timeStep;
        shiftColliders();
    }
}


void TBall::moveObject(LVector& vel, int veloci, vector <SDL_Rect>& wall, SDL_Rect box, float timeStep)
{
    int veloc = veloci / vel.getLength();
    ballVelX = vel.x * veloc;
    ballVelY = vel.y * veloc;

    LPoint flashBack;
    flashBack.setPoint(ballPosX, ballPosY);

    ballPosX += ballVelX * 60 * timeStep;
    ballPosY += ballVelY * 60 * timeStep;
    shiftColliders();

    bool changevX = changeVelX(mColliders, wall, flashBack);
    bool changevY = changeVelY(mColliders, wall, flashBack);

    if (ballPosX - mColliders.r < box.x || (ballPosX + mColliders.r) > box.x + box.w || changevX)
    {
        vel.x = - vel.x;
        ballPosX -= ballVelX * 60 * timeStep;
        shiftColliders();
    }

    if (ballPosY - mColliders.r < box.y || (ballPosY + mColliders.r) > box.y + box.h || changevY)
    {
        vel.y = - vel.y;
        ballPosY -= ballVelY * 60 * timeStep;
        shiftColliders();
    }

}


void TBall::moveBullet(float timeStep)
{
    ballPosX += ballVelX * 60 * timeStep;
    ballPosY += ballVelY * 60 * timeStep;
    shiftColliders();
}


void TBall::moveParabol(int vX, int& vY, float timeStep)
{

    ballPosX += vX * 60 * timeStep;
    ballPosY += vY * 0.1 * 60 * timeStep;

    vY += 5 * 0.2;

    shiftColliders();
}


void TBall::render(TTexture ball)
{
    ball.render(ballPosX - mColliders.r, ballPosY - mColliders.r);
}


void TBall::shiftColliders()
{
    mColliders.x = ballPosX;
    mColliders.y = ballPosY;
    mColliders.r = BALL_WIDHT / 2;
}


LCircle& TBall::getColliders()
{
    return mColliders;
}
