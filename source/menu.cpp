
#include "menu.h"
#include "texture.h"
#include "const.h"
#include "externtexture.h"
#include "mouseButton.h"

#include <SDL.h>



void menuscreen(SDL_Renderer* gRenderer, bool& quit)
{
    SDL_Event event;

    Unit8 alpha = 255;

    bool outLoop = false;

    bool mouseInNewGame = false;
    bool mouseClickNewGame = false;

    bool mouseInQuitGame = false;
    bool mouseClickQuitGame = false;

    theme.playMusic();

    TMouseButton newGame;

    newGame.setButtonPosition((SCREEN_WIDTH - 600) / 2, 600);
    newGame.setButtonSize(600, 100);

    TMouseButton quitGame;

    quitGame.setButtonPosition((SCREEN_WIDTH - 600) / 2, 800);
    quitGame.setButtonSize(600, 100);

    while (!outLoop)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                outLoop = true;
            }
            mouseInNewGame = newGame.mouseInButton(&event);
            mouseInQuitGame = quitGame.mouseInButton(&event);

            mouseClickNewGame = newGame.mouseClickInButton(&event);
            mouseClickQuitGame = quitGame.mouseClickInButton(&event);
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        introBackground[3].render(0, 0);
        logoColorBattle.render((SCREEN_WIDTH - logoColorBattle.getWidth()) / 2, 100);

        if (mouseInNewGame)
        {
            newGame.render(newGameButton[1]);
        }
        else
        {
            newGame.render(newGameButton[0]);
        }

        if (mouseInQuitGame)
        {
            quitGame.render(quitGameButton[1]);
        }
        else
        {
            quitGame.render(quitGameButton[0]);
        }

        transitionBlack.setAlpha(alpha);
        transitionBlack.render(0, 0);

        if (alpha != 0)
        {
            alpha -= 3;
        }

        if (mouseClickNewGame)
        {
            click.playSoundEffect();
            return;
        }

        if (mouseClickQuitGame)
        {
            theme.stopMusic();
            click.playSoundEffect();
            outLoop = true;
            quit = true;
        }
        SDL_RenderPresent(gRenderer);
    }
}
