
#include "picteam.h"
#include "texture.h"
#include "const.h"
#include "mouseButton.h"
#include "externtexture.h"
#include "quitmenu.h"

#include <SDL.h>



void picteam(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int& p1, int& p2)
{
    SDL_Event e;
    bool outLoop = false;

    TMouseButton redTeam;
    redTeam.setButtonPosition(1200, 300);
    redTeam.setButtonSize(400, 250);
    bool mouseInRed = false;
    bool mouseClickRed = false;
    bool chosenRed = false;

    TMouseButton pinkTeam;
    pinkTeam.setButtonPosition(100, 300);
    pinkTeam.setButtonSize(400, 250);
    bool mouseInPink = false;
    bool mouseClickPink = false;
    bool chosenPink = false;

    TMouseButton greenTeam;
    greenTeam.setButtonPosition(100, 650);
    greenTeam.setButtonSize(400, 250);
    bool mouseInGreen = false;
    bool mouseClickGreen = false;
    bool chosenGreen = false;

    TMouseButton greyTeam;
    greyTeam.setButtonPosition(1200, 650);
    greyTeam.setButtonSize(400, 250);
    bool mouseInGrey = false;
    bool mouseClickGrey = false;
    bool chosenGrey = false;

    int player1 = -1;

    bool player1chosen = false;

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quitmenu(gRenderer, quit, backToMenu);
                if (quit || backToMenu)
                {
                    outLoop = true;
                    theme.stopMusic();
                }
            }
            mouseInPink = pinkTeam.mouseInButton(&e);
            mouseInRed = redTeam.mouseInButton(&e);
            mouseInGreen = greenTeam.mouseInButton(&e);
            mouseInGrey = greyTeam.mouseInButton(&e);

            mouseClickPink = pinkTeam.mouseClickInButton(&e);
            mouseClickRed = redTeam.mouseClickInButton(&e);
            mouseClickGreen = greenTeam.mouseClickInButton(&e);
            mouseClickGrey = greyTeam.mouseClickInButton(&e);
        }

        //:-------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:-------------------------------------------------------------

        if (player1 < 0)
        {
            border.render(0, 0);
        }

        if (!player1chosen)
        {
            if (player1 >= 0)
            {
                background[player1][player1].render(0, 0);
            }
            pinkTeam.render(picPinkButton[0]);
            redTeam.render(picRedButton[0]);
            greenTeam.render(picGreenButton[0]);
            greyTeam.render(picGreyButton[0]);

            if (mouseInPink)
            {
                pinkTeam.render(picPinkButton[2]);
                player1 = 0;
            }
            else if (mouseInRed)
            {
                redTeam.render(picRedButton[2]);
                player1 = 1;
            }
            else if (mouseInGreen)
            {
                greenTeam.render(picGreenButton[2]);
                player1 = 2;
            }
            else if (mouseInGrey)
            {
                greyTeam.render(picGreyButton[2]);
                player1 = 3;
            }
            else
            {
                player1 = -1;
            }
        }
        else
        {
            background[p1][p2].render(0, 0);

            if(chosenPink)
            {
                pinkTeam.render(picPinkButton[1]);
            }
            else
            {
                pinkTeam.render(picPinkButton[0]);
            }
            if (chosenRed)
            {
                redTeam.render(picRedButton[1]);
            }
            else
            {
                redTeam.render(picRedButton[0]);
            }
            if (chosenGreen)
            {
                greenTeam.render(picGreenButton[1]);
            }
            else
            {
                greenTeam.render(picGreenButton[0]);
            }
            if (chosenGrey)
            {
                greyTeam.render(picGreyButton[1]);
            }
            else
            {
                greyTeam.render(picGreyButton[0]);
            }

            if (mouseInPink && !chosenPink)
            {
                pinkTeam.render(picPinkButton[2]);
                p2 = 0;
            }
            else if (mouseInRed && !chosenRed)
            {
                redTeam.render(picRedButton[2]);
                p2 = 1;
            }
            else if (mouseInGreen && !chosenGreen)
            {
                greenTeam.render(picGreenButton[2]);
                p2 = 2;
            }
            else if (mouseInGrey && !chosenGrey)
            {
                greyTeam.render(picGreyButton[2]);
                p2 = 3;
            }
            else
            {
                p2 = p1;
            }

        }
        //Check p1 chosen:-------------------------------
        if (!player1chosen)
        {
            if (mouseClickGreen)
            {
                chosenGreen = true;
                player1chosen = true;
            }
            else if (mouseClickGrey)
            {
                chosenGrey = true;
                player1chosen = true;
            }
            else if (mouseClickPink)
            {
                chosenPink = true;
                player1chosen = true;
            }
            else if (mouseClickRed)
            {
                chosenRed = true;
                player1chosen = true;
            }

            if (player1chosen)
            {
                p1 = player1;
            }
        }

        if (player1chosen)
        {
            if (mouseClickGreen && !chosenGreen)
            {
                outLoop = true;
            }
            else if (mouseClickGrey && !chosenGrey)
            {
                outLoop = true;
            }
            else if (mouseClickPink && !chosenPink)
            {
                outLoop = true;
            }
            else if (mouseClickRed && !chosenRed)
            {
                outLoop = true;
            }
        }

        if (mouseClickGreen || mouseClickGrey || mouseClickPink || mouseClickRed)
        {
            click.playSoundEffect();
        }

        if (!player1chosen)
        {
            picingPlayerTexture[0].render((SCREEN_WIDTH - picingPlayerTexture[0].getWidth()) / 2, (SCREEN_HEIGHT - picingPlayerTexture[0].getHeight()) / 2);
        }
        else
        {
            picingPlayerTexture[1].render((SCREEN_WIDTH - picingPlayerTexture[1].getWidth()) / 2, (SCREEN_HEIGHT - picingPlayerTexture[1].getHeight()) / 2);
        }

        picTeamTexture.render(500, 50);


    SDL_RenderPresent(gRenderer);
    }
}
