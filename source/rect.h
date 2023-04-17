#pragma once

#include "texture.h"

#include <SDL.h>
#include <vector>


using namespace std;



class TRect
{
    public:

        TRect();

        void setPosition(int x, int y);

        void setRectSize(int w, int h);

        void setRectVelocity(int vX, int vY);

        bool inZone(SDL_Rect& zone);

        bool inRect(SDL_Rect zone);

        int getMidX();

        int getMidY();

        int getHeight();

        void moveRect(SDL_Rect box, SDL_Rect& other, vector <SDL_Rect> wall, float timeStep);

        void moveObject(SDL_Rect box, float timeStep);

        bool moveObjectDown(int velocity, int boxYline, float timeStep);

        void render(TTexture rect, bool moveRender, bool down, double angle = 0.0);

        SDL_Rect& getColliders();

        void shiftColliders();

    private:

        float rectPosX;
        float rectPosY;

        float rectVelocityX;
        float rectVelocityY;

        SDL_Rect mColliders;
};
