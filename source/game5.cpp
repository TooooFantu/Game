
#include "game5.h"
#include "texture.h"
#include "const.h"
#include "externtexture.h"
#include "ball.h"
#include "rect.h"
#include "timer.h"
#include "renderpoint.h"
#include "quitmenu.h"

#include <SDL.h>
#include <vector>


using namespace std;



void callGame5(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int posX = 150;
    int posY = 150;

    vector <SDL_Rect> wall;

    SDL_Rect ballBox = {posX, posY, 1400, 700};

    int cnt = 2;

    bool getRect = true;

    bool level1 = true;
    bool level2 = true;
    bool level3 = true;

    theme.stopMusic();

    TRect safeZone;
    safeZone.setPosition(posX, posY);
    safeZone.setRectSize(1400, 700);

    TRect warningSafeZone;
    int warnPosX = 0;
    int warnPosY = 0;
    int warnWidth = 0;
    int warnHeight = 0;

    TBall player1;
    player1.setPosition(500, 350);
    player1.shiftColliders();
    player1.setBallVel(6);

    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(1200, 650);
    player2.shiftColliders();
    player2.setBallVel(6);


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

    double second = 0;

    Unit8 alpha = 255;
    Unit8 betas = 185;
    Unit8 gamma = 0;

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

                    alpha = 255;
                    betas = 185;

                    player1areDead = false;
                    player2areDead = false;
                    pause = false;

                    cnt = 2;

                    getRect = true;

                    level1 = true;
                    level2 = true;
                    level3 = true;

                    safeZone.setPosition(posX, posY);
                    safeZone.setRectSize(1400, 700);

                    warningSafeZone.setPosition(0, 0);
                    warningSafeZone.setRectSize(0, 0);

                    player1.setPosition(500, 350);
                    player1.shiftColliders();
                    player1.setBallVel(6);

                    player2.setPosition(1200, 650);
                    player2.shiftColliders();
                    player2.setBallVel(6);

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
        game5.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game5.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        safeZone.render(game5.object[curMap], false, false);

        if (!player1areDead && !player2areDead && !pause && second > 8)
        {
            player1.moveBall(wall, player2.getColliders(), ballBox, stepTime);
            player2.moveBall(wall, player1.getColliders(), ballBox, stepTime);

            if (second > 30 && level1)
            {
                player1.setBallVel(5);
                player2.setBallVel(5);
                level1 = false;
            }

            if (second > 60 && level2)
            {
                player1.setBallVel(4);
                player2.setBallVel(4);
                level2 = false;
            }

            if (second > 90 && level3)
            {
                player1.setBallVel(3);
                player2.setBallVel(3);
                level3 = false;
            }


            if (second > cnt * 4)
            {
                if (getRect)
                {
                    warnPosX = (rand() % 1350) + 150;
                    warnWidth = min(1550 - warnPosX, (rand() % 1350) + 50);
                    warnPosY = (rand() % 650) + 150;
                    warnHeight = min(850 - warnPosY, (rand() % 650) + 50);
                    warningSafeZone.setPosition(warnPosX, warnPosY);
                    warningSafeZone.setRectSize(warnWidth, warnHeight);
                    getRect = false;
                }

                if (second < (cnt * 4 + 1))
                {
                    warningSafeZone.render(cnting[0], false, false);
                }
                else if (second < (cnt * 4 + 2))
                {
                    warningSafeZone.render(cnting[1], false, false);
                }
                else if (second < (cnt * 4 + 3))
                {
                    warningSafeZone.render(cnting[2], false, false);
                }
                else
                {
                    safeZone.setPosition(warnPosX, warnPosY);
                    safeZone.setRectSize(warnWidth, warnHeight);
                }
                if (second > (cnt + 1) * 4)
                {
                    safeZone.setPosition(posX, posY);
                    safeZone.setRectSize(1400, 700);
                    ++cnt;
                    getRect = true;
                }
            }
            player1areDead = !player1.areDeadRect(safeZone.getColliders());
            player2areDead = !player2.areDeadRect(safeZone.getColliders());
        }

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);


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
        else if (player1areDead)
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
        else if (player2areDead)
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
