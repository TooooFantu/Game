
#include "endgame.h"
#include "mouseButton.h"
#include "const.h"
#include "timer.h"
#include "externtexture.h"

#include <SDL.h>



void endgame(SDL_Renderer* gRenderer, bool& quit, int p1, int p2, bool player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.playMusic();

    TTimer timer;
    timer.Start();

    double second = 0;

    Unit8 alpha = 254;

    Unit8 betas = 0;

    TMouseButton mainMenu;
    mainMenu.setButtonPosition((SCREEN_WIDTH - 600) / 2, 600);
    mainMenu.setButtonSize(600, 100);

    bool mainMenuOver = false;
    bool mainMenuClick = false;

    TMouseButton quitGame;
    quitGame.setButtonPosition((SCREEN_WIDTH - 600) / 2, 800);
    quitGame.setButtonSize(600, 100);

    bool quitGameOver = false;
    bool quitGameClick = false;

    bool camShutter = true;


    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            mainMenuOver = mainMenu.mouseInButton(&e);
            mainMenuClick = mainMenu.mouseClickInButton(&e);

            quitGameOver = quitGame.mouseInButton(&e);
            quitGameClick = quitGame.mouseClickInButton(&e);
        }

        //:-------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:-------------------------------------------------------------

        second = timer.GetTicks() / (1000.f);

        if (player1Win)
        {
            winBackground[p1].render(0, 0);
            bestcolor[p1].render((SCREEN_WIDTH - bestcolor[4].getWidth()) / 2, 150);
        }
        else
        {
            winBackground[p2].render(0, 0);
            bestcolor[p2].render((SCREEN_WIDTH - bestcolor[4].getWidth()) / 2, 150);
        }

        if (second < 5)
        {
            transitionBlack.setAlpha(alpha);
            transitionBlack.render(0, 0);
        }


        if (alpha != 0)
        {
            alpha -=2;
        }

        if (second > 5)
        {
            transitionBlack.setAlpha(100);
            transitionBlack.render(0, 0);
            camera.render(0, 0);
        }

        if (second > 5 && camShutter)
        {
            cameraShutter.playSoundEffect();
            camShutter = false;
        }

        if (second > 7)
        {
            if (betas != 254)
            {
                betas += 2;
            }
            if (mainMenuOver)
            {
                mainMenuButton[1].setAlpha(betas);
                mainMenu.render(mainMenuButton[1]);
            }
            else
            {
                mainMenuButton[0].setAlpha(betas);
                mainMenu.render(mainMenuButton[0]);
            }

            if (quitGameOver)
            {
                quitGameButton[1].setAlpha(betas);
                quitGame.render(quitGameButton[1]);
            }
            else
            {
                quitGameButton[0].setAlpha(betas);
                quitGame.render(quitGameButton[0]);
            }

            if (mainMenuClick)
            {
                mainMenuButton[0].setAlpha(255);
                mainMenuButton[1].setAlpha(255);
                quitGameButton[0].setAlpha(255);
                quitGameButton[1].setAlpha(255);
                outLoop = true;
                quit = false;
            }

            if (quitGameClick)
            {
                mainMenuButton[0].setAlpha(255);
                mainMenuButton[1].setAlpha(255);
                quitGameButton[0].setAlpha(255);
                quitGameButton[1].setAlpha(255);
                outLoop = true;
                quit = true;
            }

        }

    SDL_RenderPresent(gRenderer);
    }
}
