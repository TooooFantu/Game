
#include "quitmenu.h"
#include "mouseButton.h"
#include "externtexture.h"

#include <SDL.h>



void quitmenu(SDL_Renderer *gRenderer, bool& quit, bool& backToMenu)
{
    SDL_Event e;
    bool outLoop = false;

    TMouseButton TContinue;
    TContinue.setButtonPosition((SCREEN_WIDTH - 600) / 2, 200);
    TContinue.setButtonSize(600, 100);

    bool continueOver = false;
    bool continueClick = false;

    TMouseButton mainMenu;
    mainMenu.setButtonPosition((SCREEN_WIDTH - 600) / 2, 450);
    mainMenu.setButtonSize(600, 100);

    bool mainMenuOver = false;
    bool mainMenuClick = false;


    TMouseButton quitGame;
    quitGame.setButtonPosition((SCREEN_WIDTH - 600) / 2, 700);
    quitGame.setButtonSize(600, 100);

    bool quitGameOver = false;
    bool quitGameClick = false;

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            continueOver = TContinue.mouseInButton(&e);
            continueClick = TContinue.mouseClickInButton(&e);

            mainMenuOver = mainMenu.mouseInButton(&e);
            mainMenuClick = mainMenu.mouseClickInButton(&e);

            quitGameOver = quitGame.mouseInButton(&e);
            quitGameClick = quitGame.mouseClickInButton(&e);
        }

        //:-------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:-------------------------------------------------------------

        quitBackground.render(0, 0);

        if (continueOver)
        {
            TContinue.render(continueButton[1]);
        }
        else
        {
            TContinue.render(continueButton[0]);
        }

        if (mainMenuOver)
        {
            mainMenu.render(mainMenuButton[1]);
        }
        else
        {
            mainMenu.render(mainMenuButton[0]);
        }

        if (quitGameOver)
        {
            quitGame.render(quitGameButton[1]);
        }
        else
        {
            quitGame.render(quitGameButton[0]);
        }

        if (continueClick)
        {
            return;
        }

        if (mainMenuClick)
        {
            outLoop = true;
            backToMenu = true;
        }

        if (quitGameClick)
        {
            outLoop = true;
            quit = true;
        }

    SDL_RenderPresent(gRenderer);
    }
}

