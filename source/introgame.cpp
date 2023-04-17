
#include "introgame.h"
#include "texture.h"
#include "const.h"
#include "externtexture.h"
#include "timer.h"

#include <SDL.h>

void introgame(SDL_Renderer* gRenderer, bool& quit)
{
    SDL_Event e;
    bool outLoop = false;

    TTimer timer;
    timer.Start();
    double second = 0;
    Unit8 alpha = 0;
    Unit8 betas = 0;

    bool soundLoop1 = true;
    bool soundLoop21 = true;
    bool soundLoop22 = true;
    bool soundLoop23 = true;
    bool soundLoop24 = true;

    bool soundLoop3 = true;

    bool changeAlpha = false;
    bool changeFrame[3];

    bool renderFantu = true;

    for (int i = 0; i < 3; i++)
    {
        changeFrame[i] = false;;
    }

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                outLoop = true;
                quit = true;
            }
        }
        second = timer.GetTicks() / (1000.f);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        //:----------------------------------------------

            logoFantu.setAlpha(alpha);
            if (renderFantu)
            {
                logoFantu.render((SCREEN_WIDTH - logoFantu.getWidth()) / 2, (SCREEN_HEIGHT - logoFantu.getHeight()) / 2);
            }

            if (alpha != 255 && !changeAlpha)
            {
                alpha += 3;
            }

            if (alpha!= 0 && changeAlpha)
            {
                alpha -= 3;
            }

            if (alpha == 255)
            {
                changeAlpha = true;
            }

            if (alpha == 0)
            {
                alpha = 0;
                renderFantu = false;
            }

            if (second > 4 && !changeFrame[0])
            {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
                SDL_RenderClear(gRenderer);

                introBackground[0].render(0, 0);
            }

            if (second > 4.5 && !changeFrame[1])
            {
                changeFrame[0] = true;

                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
                SDL_RenderClear(gRenderer);

                introBackground[1].render(0, 0);

            }

            if (second > 5 && !changeFrame[2])
            {
                changeFrame[1] = true;

                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
                SDL_RenderClear(gRenderer);

                introBackground[2].render(0, 0);
            }

            if (second > 5.5)
            {
                changeFrame[2] = true;

                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
                SDL_RenderClear(gRenderer);

                introBackground[3].render(0, 0);
            }

            if (second > 6)
            {
                logoColorBattle.render((SCREEN_WIDTH - logoColorBattle.getWidth()) / 2, (SCREEN_HEIGHT - logoColorBattle.getHeight()) / 2);
            }

            if (second > 7)
            {
                transitionBlack.setAlpha(betas);
                transitionBlack.render(0, 0);

                if (betas != 255)
                {
                    betas += 3;
                }
            }

            //Sound:-----------------------------------

            if (soundLoop1)
            {
                intro[0].playSoundEffect();
                soundLoop1 = false;
            }

            if (second > 5.2 && soundLoop24)
            {
                soundLoop23 = true;
                soundLoop24 = false;
            }


            if (second > 4.7 && soundLoop23)
            {
                soundLoop22 = true;
                soundLoop23 = false;
            }

            if (second > 4.2 && soundLoop22)
            {
                soundLoop21 = true;
                soundLoop22 = false;
            }

            if (second > 3.7 && soundLoop21)
            {
                intro[1].playSoundEffect();
                soundLoop21 = false;
            }

            if (second > 6 && soundLoop3)
            {
                intro[2].playSoundEffect();
                soundLoop3 = false;
            }

            if (second > 10)
            {
                outLoop = true;
            }


        SDL_RenderPresent(gRenderer);
    }
}
