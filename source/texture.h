#pragma once

#include "const.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


using namespace std;



class TTexture
{
    public:

        TTexture();

        ~TTexture();

        bool loadFromfile(string path);

        bool loadFromRenderedText(string currentText, SDL_Color color, TTF_Font *font);

        void free();

        void setColor(Unit8 red, Unit8 green, Unit8 blue);

        void setBlendMode( SDL_BlendMode blending );

        void setAlpha( Unit8 alpha );

        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

    private:

        SDL_Texture *mTexture;

        int mWidth;
        int mHeight;
};
