
#include "game4.h"
#include "texture.h"
#include "externtexture.h"
#include "ball.h"
#include "rect.h"
#include "const.h"
#include "timer.h"
#include "compute.h"
#include "renderpoint.h"
#include "quitmenu.h"

#include <SDL.h>
#include <vector>


using namespace std;



void callGame4(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int posX = 150;
    int posY = 150;

    vector <SDL_Rect> wall;

    int treasureX = (rand() % 1300) + 200;
    int treasureY = (rand() % 400) + 400;

    SDL_Rect treasure = {treasureX, treasureY, 20, 20};

    SDL_Rect ballBox = {posX + 20, posY + 20, 1400 - 40, 700 - 40};


    TBall player1;
    player1.setPosition(posX + 35, posY + 35);
    player1.shiftColliders();
    player1.setBallVel(3);

    TRect p1Zone;
    p1Zone.setPosition(player1.getPositionX() - 35, player1.getPositionY() - 35);
    p1Zone.setRectSize(70, 70);

    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(SCREEN_WIDTH - posX - 35, posY + 35);
    player2.shiftColliders();
    player2.setBallVel(3);

    TRect p2Zone;
    p2Zone.setPosition(player2.getPositionX() - 35, player2.getPositionY() - 35);
    p2Zone.setRectSize(70, 70);

    bool p2Up = false;
    bool p2Down = false;
    bool p2Left = false;
    bool p2Right = false;



    bool player1areDead = false;
    bool player2areDead = false;

    bool pause = false;

    bool playCountDown = true;

    TTimer timer;
    timer.Start();

    TTimer timerStep;
    float stepTime = 0;

    Unit8 alpha = 255;
    Unit8 betas = 185;
    Unit8 gamma = 0;

    double second = 0;

    bool retry = false;

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT && second > 8)
            {
                timer.Pause();
                timerStep.Pause();
                pause = true;

                quitmenu(gRenderer, quit, backToMenu);

                timer.unPause();
                timerStep.unPause();
                pause = false;

                if (quit || backToMenu)
                {
                    outLoop = true;
                    theme.stopMusic();
                }

                player1.setBallVelocity(0, 0);
                player2.setBallVelocity(0, 0);

                p1Up = false;
                p1Down = false;
                p1Left = false;
                p1Right = false;


                p2Up = false;
                p2Down = false;
                p2Left = false;
                p2Right = false;

            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN && (player1areDead && player2areDead))
                {
                    playCountDown = true;

                    retry = true;
                    second = 0;
                    timer.Start();

                    player1areDead = false;
                    player2areDead = false;
                    pause = false;

                    player1.setPosition(posX + 35, posY + 35);
                    player1.shiftColliders();

                    p1Zone.setPosition(player1.getPositionX() - 35, player1.getPositionY() - 35);

                    player2.setPosition(SCREEN_WIDTH - posX - 35, posY + 35);
                    player2.shiftColliders();

                    p2Zone.setPosition(player2.getPositionX() - 35, player2.getPositionY() - 35);

                    treasureX = (rand() % 1300) + 200;
                    treasureY = (rand() % 400) + 400;

                    treasure = {treasureX, treasureY, 20, 20};

                    player1.setBallVelocity(0, 0);
                    player2.setBallVelocity(0, 0);

                    p1Up = false;
                    p1Down = false;
                    p1Left = false;
                    p1Right = false;


                    p2Up = false;
                    p2Down = false;
                    p2Left = false;
                    p2Right = false;


                }
                else if (e.key.keysym.sym == SDLK_p && !(player1areDead || player2areDead) && second > 8)
                {
                    if (timer.isPaused())
                    {
                        timer.unPause();
                    }
                    else
                    {
                        timer.Pause();
                    }
                    if (pause)
                    {
                        pause = false;
                    }
                    else
                    {
                        pause = true;
                    }
                }
            }
            player1.handleEventPlayer1(e, p1Up, p1Down, p1Left, p1Right);
            player2.handleEventPlayer2(e, p2Up, p2Down, p2Left, p2Right);
        }

        //:------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:------------------------------------------------------------

        stepTime = timerStep.GetTicks() / (1000.f);

        if (!retry)
        {
            second = timer.GetTicks() / (1000.f);
        }
        else
        {
            second = 5 + (timer.GetTicks() / (1000.f));
        }

        background[p1][p2].render(0, 0);
        game4.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game4.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        p1Zone.render(game4.object[curMap], false, false);
        p2Zone.render(game4.object[curMap], false, false);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);

        if (p1Zone.inZone(treasure) || p2Zone.inZone(treasure))
        {
            game4.treasure[curMap].render(treasure.x, treasure.y);
        }




        if (!player1areDead && !player2areDead && !pause && second > 8)
        {
            player1.moveBall(wall, player2.getColliders(), ballBox, stepTime);
            player2.moveBall(wall, player1.getColliders(), ballBox, stepTime);

            p1Zone.setPosition(player1.getPositionX() - 35, player1.getPositionY() - 35);
            p1Zone.shiftColliders();

            p2Zone.setPosition(player2.getPositionX() - 35, player2.getPositionY() - 35);
            p2Zone.shiftColliders();

            player1areDead = player1.areDeadRect(treasure);
            player2areDead = player2.areDeadRect(treasure);
        }







        if (second < 5)
        {
            if (alpha != 0)
            {
                alpha -= 3;
            }
            tutorialWASD.setAlpha(betas);
            tutorialWASD.render(0, 0);
            transitionBlack.setAlpha(alpha);
            transitionBlack.render(0, 0);
            if (betas != 0 && second > 4)
            {
                betas -= 3;
            }
        }

        if (second > 5 && second <= 8)
        {
            alpha = 185;
            transitionBlack.setAlpha(alpha);
            transitionBlack.render(0, 0);
        }

        if (second > 5 && second <= 6)
        {
            countDown[0].render((SCREEN_WIDTH - countDown[0].getWidth()) / 2, (SCREEN_HEIGHT - countDown[0].getHeight()) / 2);
        }
        if (second > 6 && second <= 7)
        {
            countDown[1].render((SCREEN_WIDTH - countDown[0].getWidth()) / 2, (SCREEN_HEIGHT - countDown[0].getHeight()) / 2);
        }
        if (second > 7 && second <= 8)
        {
            countDown[2].render((SCREEN_WIDTH - countDown[0].getWidth()) / 2, (SCREEN_HEIGHT - countDown[0].getHeight()) / 2);
        }







        if (player1areDead && player2areDead)
        {
            transitionBlack.setAlpha(185);
            transitionBlack.render(0, 0);
            draw.render((SCREEN_WIDTH - draw.getWidth()) / 2, (SCREEN_HEIGHT - draw.getHeight()) / 2);
        }
        else if (player2areDead)
        {
            transitionBlack.setAlpha(gamma);
            transitionBlack.render(0, 0);
            gamma++;
            if (gamma == 255)
            {
                player1Win = false;
                outLoop = true;
            }
        }
        else if (player1areDead)
        {
            transitionBlack.setAlpha(gamma);
            transitionBlack.render(0, 0);
            gamma++;
            if (gamma == 255)
            {
                player1Win = true;
                outLoop = true;
            }
        }


        timerStep.Start();

        //Sound:-------------------------------------------------------------

        if (second > 5 && playCountDown)
        {
            cntdown.playSoundEffect();
            playCountDown = false;
        }
        if (second > 8)
        {
            theme.playMusic();
        }




    SDL_RenderPresent(gRenderer);
    }
}
