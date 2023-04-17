
#include "mouseButton.h"
#include "texture.h"



TMouseButton::TMouseButton()
{
    buttonPosX = 0;
    buttonPosX = 0;

    BUTTON_WIDTH = 0;
    BUTTON_HEIGHT = 0;
}


void TMouseButton::setButtonPosition(int x, int y)
{
    buttonPosX = x;
    buttonPosY = y;
}


void TMouseButton::setButtonSize(int w, int h)
{
    BUTTON_WIDTH = w;
    BUTTON_HEIGHT = h;
}


bool TMouseButton::mouseInButton(SDL_Event* e)
{
    int mousePosX;
    int mousePosY;

    SDL_GetMouseState(&mousePosX, &mousePosY);

    bool inside = true;

        if (mousePosX < buttonPosX)
        {
            inside = false;
        }

        else if (mousePosX > buttonPosX + BUTTON_WIDTH)
        {
            inside = false;
        }

        else if (mousePosY < buttonPosY)
        {
            inside = false;
        }

        else if (mousePosY > buttonPosY + BUTTON_HEIGHT)
        {
            inside = false;
        }
    return inside;
}


bool  TMouseButton::mouseClickInButton(SDL_Event* e)
{
    if (mouseInButton(e) && e->type == SDL_MOUSEBUTTONDOWN)
    {
        return true;
    }

    return false;
}


void TMouseButton::render(TTexture button)
{
    button.render(buttonPosX, buttonPosY);
}
