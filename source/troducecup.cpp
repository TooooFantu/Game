
#include "troducecup.h"
#include "texture.h"
#include "externtexture.h"
#include "const.h"
#include "timer.h"
#include "quitmenu.h"

#include <SDL.h>



void troduceCup(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2)
{
    SDL_Event e;
    bool outLoop = false;

    TTimer timer;
    timer.Start();

    Unit8 alpha = 254;

    double second = 0;

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                timer.Pause();
                quitmenu(gRenderer, quit, backToMenu);
                timer.unPause();
                if (quit || backToMenu)
                {
                    outLoop = true;
                    theme.stopMusic();
                }
            }

        }

        //:------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:------------------------------------------------------------

        second = timer.GetTicks() / (1000.f);

        background[p1][p2].render(0, 0);

        bestcolor[4].render((SCREEN_WIDTH - bestcolor[4].getWidth()) / 2, 150);

        transitionBlack.setAlpha(alpha);
        transitionBlack.render(0, 0);

        if (second < 3 && alpha != 0)
        {
            alpha -= 2;
        }

        if (alpha != 254 && second > 5)
        {
            alpha += 2;
        }

        if (alpha == 254)
        {
            outLoop = true;
        }



    SDL_RenderPresent(gRenderer);
    }
}
