#pragma once

#include "texture.h"

#include <SDL.h>



class TMouseButton
{
    public:

        TMouseButton();

        void setButtonPosition(int x, int y);

        void setButtonSize(int w, int h);

        bool mouseInButton(SDL_Event* e);

        bool mouseClickInButton(SDL_Event* e);

        void render(TTexture button);

    private:

        int buttonPosX;
        int buttonPosY;

        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
};
