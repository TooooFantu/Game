
#include "game8.h"
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



void callGame8(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int posX = 150;
    int posY = 150;


    TRect treasure;
    treasure.setPosition(posX + 675, posY + (rand() % 650));
    treasure.setRectSize(50, 50);
    treasure.shiftColliders();

    //Player1:---------------------------------

    TBall player1;
    player1.setPosition(posX + 85, posY + 515);
    player1.shiftColliders();

    TRect p1PowerQue;
    p1PowerQue.setPosition(posX + 20, posY + 395);
    p1PowerQue.setRectSize(24, 84);

    bool p1RenderPowerQue = false;

    bool p1PowerCharge = false;
    bool p1Fire = false;

    int p1Power = 0;

    int p1Point = 0;

    //Player2:-------------------------------

    TBall player2;
    player2.setPosition(posX + 1315, posY + 515);
    player2.shiftColliders();

    TRect p2PowerQue;
    p2PowerQue.setPosition(posX + 1356, posY + 395);
    p2PowerQue.setRectSize(24, 84);

    bool p2RenderPowerQue = false;

    bool p2PowerCharge = false;
    bool p2Fire = false;

    int p2Power = 0;

    int p2Point = 0;




    bool player1areWin = false;
    bool player2areWin = false;

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
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_w)
                {
                    p1PowerCharge = true;
                    p1RenderPowerQue = true;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    p2PowerCharge = true;
                    p2RenderPowerQue = true;
                }
                else if (e.key.keysym.sym == SDLK_p && !(player1areWin || player2areWin) && second > 8)
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
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_w)
                {
                    p1PowerCharge = false;
                    p1RenderPowerQue = false;
                    p1Fire = true;
                }

                if (e.key.keysym.sym == SDLK_UP)
                {
                    p2PowerCharge = false;
                    p2RenderPowerQue = false;
                    p2Fire = true;
                }


            }

        }

        //:------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:------------------------------------------------------------

        stepTime = timerStep.GetTicks() / (1000.f);

        second = timer.GetTicks() / (1000.f);

        background[p1][p2].render(0, 0);
        game8.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game8.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        treasure.render(game8.treasure[curMap], false, false);


        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);



        if (!player1areWin && !player2areWin && ! pause && second > 8)
        {
            //ChargePower:-------------------------------------------------

            if (p1PowerCharge && p1Power > - 90 && !p1Fire)
            {
                p1Power --;
            }

            if (p2PowerCharge && p2Power > - 90 && !p2Fire)
            {
                p2Power --;
            }

            //Fire:--------------------------------------------------------

            if (p1Fire)
            {
                player1.moveParabol(6, p1Power, stepTime);
            }

            if (p2Fire)
            {
                player2.moveParabol(-6, p2Power, stepTime);
            }


            //Check:-------------------------------------------------------

                //Collision:-------------------------------------------
                    if (player1.areDeadRect(treasure.getColliders()))
                    {
                        p1Point++;

                        p1Fire = false;
                        p1Power = 0;
                        player1.setPosition(posX + 85, posY + 515);
                        player1.shiftColliders();
                        p1PowerQue.setRectSize(24, 84);

                        treasure.setPosition(posX + 675, posY + (rand() % 650));
                        treasure.shiftColliders();

                    }

                    if (player2.areDeadRect(treasure.getColliders()))
                    {
                        p2Point++;

                        p2Fire = false;
                        p2Power = 0;
                        player2.setPosition(posX + 1315, posY + 515);
                        player2.shiftColliders();
                        p2PowerQue.setRectSize(24, 84);

                        treasure.setPosition(posX + 675, posY + (rand() % 650));
                        treasure.shiftColliders();

                    }


                //OutPlayZone:------------------------------------------------

                    bool reset = player1.areDeadCircle(player2.getColliders());

                    if (player1.getPositionY() > posY + 685 || reset)
                    {
                        p1Fire = false;
                        p1Power = 0;
                        player1.setPosition(posX + 85, posY + 515);
                        player1.shiftColliders();
                        p1PowerQue.setRectSize(24, 84);
                    }

                    if (player2.getPositionY() > posY + 685 || reset)
                    {
                        p2Fire = false;
                        p2Power = 0;
                        player2.setPosition(posX + 1315, posY + 515);
                        player2.shiftColliders();
                        p2PowerQue.setRectSize(24, 84);
                    }


            //RenderPowerQue:----------------------------------------------------

            if (p1RenderPowerQue && !p1Fire)
            {
                if (p1PowerQue.getHeight() > 0)
                {
                    p1PowerQue.setRectSize(24, p1PowerQue.getHeight() - 1);
                }

                game8.wall[0].render(posX + 12, posY + 387);
                p1PowerQue.render(game8.wall[1], false, false);
            }
            else
            {
                p1PowerQue.setRectSize(24, 84);
            }

            if (p2RenderPowerQue && !p2Fire)
            {
                if (p2PowerQue.getHeight() > 0)
                {
                    p2PowerQue.setRectSize(24,p2PowerQue.getHeight() - 1);
                }

                game8.wall[0].render(posX + 1348, posY + 387);
                p2PowerQue.render(game8.wall[1], false, false);
            }
            else
            {
                p2PowerQue.setRectSize(24, 84);
            }

            //UpdatePoint:---------------------------------

            if (p1Point == 5)
            {
                player1areWin = true;
            }
            else
            {
                point[p1Point].render(posX, posY);
            }

            if (p2Point == 5)
            {
                player2areWin = true;
            }
            else
            {
                point[p2Point].render(posX + 1200, posY);
            }


        }



        game8.object[curMap].render(posX, posY + 500);
        game8.object[curMap].render(posX + 1300, posY + 500, NULL, 0.0, NULL, SDL_FLIP_HORIZONTAL);



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




        if (player1areWin && player2areWin)
        {
            transitionBlack.setAlpha(185);
            transitionBlack.render(0, 0);
            draw.render((SCREEN_WIDTH - draw.getWidth()) / 2, (SCREEN_HEIGHT - draw.getHeight()) / 2);
        }
        else if (player1areWin)
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
        else if (player2areWin)
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
