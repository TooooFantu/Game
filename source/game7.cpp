
#include "game7.h"
#include "texture.h"
#include "const.h"
#include "externtexture.h"
#include "ball.h"
#include "rect.h"
#include "timer.h"
#include "compute.h"
#include "renderpoint.h"
#include "quitmenu.h"

#include <SDL.h>
#include <vector>


using namespace std;



void callGame7(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int posX = 150;
    int posY = 150;

    int velocity = 2;

    SDL_Rect tankBox = {posX, posY, 1400, 700};

    vector <SDL_Rect> wall;


    SDL_Rect wallll[5];
    wallll[0] = {posX + 200, posY + 100, 100, 100};
    wallll[1] = {posX + 500, posY + 300, 100, 100};
    wallll[2] = {posX, posY + 600, 100, 100};
    wallll[3] = {posX + 1200, 200, 100, 100};
    wallll[4] = {posX + 1000, posY + 450, 100, 100};


    for (int i = 0; i < 5; i++)
    {
        wall.push_back(wallll[i]);
    }

    //Player1:-----------------------------------------

    TRect player1;
    player1.setPosition(posX + 30, posY + 30);
    player1.setRectSize(50, 50);
    player1.setRectVelocity(0, 0);
    player1.shiftColliders();

    TBall bullet1;
    bullet1.setPosition(player1.getMidX(), player1.getMidY());
    bullet1.setBallSize(10, 10);
    bullet1.shiftColliders();

    bool p1spin = true;

    bool p1start = false;

    bool p1shooting = false;

    bool p1GetNewVelocity = true;

    bool p1Looping = false;

    int vP1X = 0, vP1Y = 0;

    double p1Alpha = 0;

    //Player2:----------------------------------------

    TRect player2;
    player2.setPosition(posX + 1320, posY + 620);
    player2.setRectSize(50, 50);
    player2.setRectVelocity(0, 0);
    player2.shiftColliders();

    TBall bullet2;
    bullet2.setPosition(player2.getMidX(), player2.getMidY());
    bullet2.setBallSize(10, 10);
    bullet2.shiftColliders();

    bool p2spin = true;

    bool p2start = false;

    bool p2shooting = false;

    bool p2GetNewVelocity = true;

    bool p2Looping = false;

    int vP2X = 0, vP2Y = 0;

    double p2Alpha = 0;

    //:-----------------------------------------------


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

                p1start = false;
                p2start = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN && (player1areDead && player2areDead))
                {
                    playCountDown = true;

                    alpha = 255;
                    betas = 185;

                    retry = true;
                    second = 0;
                    timer.Start();

                    player1areDead = false;
                    player2areDead = false;

                    pause = false;


                    player1.setPosition(posX + 30, posY + 30);
                    player1.setRectVelocity(0, 0);
                    player1.shiftColliders();


                    bullet1.setPosition(player1.getMidX(), player1.getMidY());
                    bullet1.shiftColliders();


                    p1spin = true;

                    p1start = false;

                    p1shooting = false;

                    p1GetNewVelocity = true;

                    p1Looping = false;

                    vP1X = 0; vP1Y = 0;

                    p1Alpha = 0;


                    player2.setPosition(posX + 1320, posY + 620);
                    player2.setRectVelocity(0, 0);
                    player2.shiftColliders();

                    bullet2.setPosition(player2.getMidX(), player2.getMidY());
                    bullet2.shiftColliders();

                    p2spin = true;

                    p2start = false;

                    p2shooting = false;

                    p2GetNewVelocity = true;

                    p2Looping = false;

                    vP2X = 0; vP2Y = 0;

                    p2Alpha = 0;


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

                if (e.key.keysym.sym == SDLK_w && second > 8)
                {
                    p1start = true;
                    p1shooting = true;
                    p1Looping = true;

                    getVel(vP1X, vP1Y, p1Alpha, velocity);

                    p1spin = false;
                }

                if (e.key.keysym.sym == SDLK_UP && second > 8)
                {
                    p2start = true;
                    p2shooting = true;
                    p2Looping = true;

                    getVel(vP2X, vP2Y, p2Alpha, velocity);

                    p2spin = false;
                }




            }
            else if (e.type == SDL_KEYUP)
            {

                if (e.key.keysym.sym == SDLK_w && second > 8)
                {
                    p1GetNewVelocity = false;
                    p1Looping = false;
                    p1start = false;
                    vP1X = 0;
                    vP1Y = 0;
                    p1spin = true;
                }

                if (e.key.keysym.sym == SDLK_UP && second > 8)
                {
                    p2GetNewVelocity = false;
                    p2Looping = false;
                    p2start = false;
                    vP2X = 0;
                    vP2Y = 0;
                    p2spin = true;
                }

            }


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
        game7.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game7.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        for (int i = 0; i < 5; i++)
        {
            game7.object[curMap].render(wallll[i].x, wallll[i].y);
        }


        player1.render(playerTank[p1], false, false, p1Alpha);
        player2.render(playerTank[p2], false, false, p2Alpha);




        player1.setRectVelocity(vP1X, vP1Y);
        player2.setRectVelocity(vP2X, vP2Y);


        if (!player1areDead && !player2areDead && !pause && second > 8)
        {
            //Set velocity:--------------------------
            if (p1start && p1GetNewVelocity)
            {
                bullet1.setBallVelocity(vP1X * 4, vP1Y * 4);
                p1GetNewVelocity = false;
                p1start = false;
            }

            player1.moveRect(tankBox, player2.getColliders(), wall, stepTime);

            if (p2start && p2GetNewVelocity)
            {
                bullet2.setBallVelocity(vP2X * 4, vP2Y * 4);
                p2GetNewVelocity = false;
                p2start = false;
            }

            player2.moveRect(tankBox, player1.getColliders(), wall, stepTime);

            if (!bullet1.insideBox(tankBox) || checkCollision(bullet1.getColliders(), wall) || (bullet1.getVelX() == 0 && bullet1.getVelY() == 0))
            {
                p1GetNewVelocity = true;
            }

            if (!bullet2.insideBox(tankBox) || checkCollision(bullet2.getColliders(), wall) || (bullet2.getVelX() == 0 && bullet2.getVelY() == 0))
            {
                p2GetNewVelocity = true;
            }

            //Render:------------------------------------

            if (p1shooting && bullet1.insideBox(tankBox) && !checkCollision(bullet1.getColliders(), wall))
            {
                bullet1.moveBullet(stepTime);
                bullet1.render(playerBullet[p1]);
            }
            else
            {
                if (!p1Looping)
                {
                    p1shooting = false;
                    bullet1.setBallVelocity(0, 0);
                }

                bullet1.setPosition(player1.getMidX(), player1.getMidY());
                bullet1.shiftColliders();
            }

            if (p2shooting && bullet2.insideBox(tankBox) && !checkCollision(bullet2.getColliders(), wall))
            {
                bullet2.moveBullet(stepTime);
                bullet2.render(playerBullet[p2]);
            }
            else
            {
                if (!p2Looping)
                {
                    p2shooting = false;
                    bullet2.setBallVelocity(0, 0);
                }

                bullet2.setPosition(player2.getMidX(), player2.getMidY());
                bullet2.shiftColliders();
            }

            //:---------------------------------------------------

            player1areDead = bullet2.areDeadRect(player1.getColliders());
            player2areDead = bullet1.areDeadRect(player2.getColliders());

            //Spin:-----------------------------------------------

            if (p1spin)
            {
                p1Alpha += 2 * stepTime * 60;
            }
            if (p1Alpha == 360)
            {
                p1Alpha = 0;
            }

            if (p2spin)
            {
                p2Alpha += 2 * stepTime * 60;
            }

            if (p2Alpha == 360)
            {
                p2Alpha = 0;
            }

        }




        if (second < 5)
        {
            if (alpha != 0)
            {
                alpha -= 3;
            }
            tutorialW.setAlpha(betas);
            tutorialW.render(0, 0);
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
                player1Win = true;;
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
