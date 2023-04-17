#pragma once

#include "texture.h"
#include "structure.h"

#include <SDL.h>
#include <vector>


using namespace std;



class TBall
{
    public:

        TBall();

        void setBallSize(int w, int h);

        void setPosition(int x, int y);

        int getPositionX();

        int getPositionY();

        int getVelX();

        int getVelY();

        void setBallVelocity(int vX, int xY);

        void setBallVel(int v);

        bool insideBox(SDL_Rect& box);

        bool areDeadCircle(LCircle& circle);

        bool areDeadRect(SDL_Rect& rect);

        void handleEventPlayer1(SDL_Event& e, bool& stopUp, bool& stopDown, bool& stopLeft, bool& stopRight);

        void handleEventPlayer2(SDL_Event& e, bool& stopUp, bool& stopDown, bool& stopLeft, bool& stopRight);

        void moveBall(vector <SDL_Rect>& wall, LCircle& circle, SDL_Rect box, float timeStep);

        void moveObject(LVector& vel, int velocity, vector <SDL_Rect>& wall, SDL_Rect box, float timeStep);

        void moveBullet(float timeStep);

        void moveParabol(int vX, int& vY, float timeStep);

        void render(TTexture ball);

        LCircle& getColliders();

        void shiftColliders();

    private:

        int BALL_VEL;

        int BALL_WIDHT;
        int BALL_HEIGHT;

        float ballPosX;
        float ballPosY;

        float ballVelX;
        float ballVelY;

        LCircle mColliders;

        LVector velocity;

};



