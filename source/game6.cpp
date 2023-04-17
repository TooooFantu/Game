
#include "game6.h"
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



void callGame6(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int posX = 150;
    int posY = 150;

    vector <SDL_Rect> wall;

    SDL_Rect ballBox = {posX, posY, 1400, 700};

    SDL_Rect treasure = {800, 450, 100, 100};

    TBall player1;
    player1.setPosition(posX + 20, posY + 70);
    player1.shiftColliders();

    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(posX + ballBox.w - 20, posY + ballBox.h - 70);
    player2.shiftColliders();

    bool p2Up = false;
    bool p2Down = false;
    bool p2Left = false;
    bool p2Right = false;

    SDL_Rect mWall[10];
    mWall[0] = {posX, posY, 1400, 35};
    mWall[1] = {posX + 1365, posY, 35, 700 - 105};
    mWall[2] = {posX, posY + 665, 1400, 35};
    mWall[3] = {posX, posY + 105, 35, 595};
    mWall[4] = {posX, posY + 105, 1295, 70};
    mWall[5] = {posX + (1400 - 175), posY + 105, 70, 350};
    mWall[6] = {posX + 245, posY + 385, (1400 - 350), 70};
    mWall[7] = {posX + 105, posY + 525, 1295, 70};
    mWall[8] = {posX + 105, posY + 245, 70, 350};
    mWall[9] = {posX + 105, posY + 245, (1400 - 350), 70};

    for (int i = 0; i < 10; i++)
    {
        wall.push_back(mWall[i]);
    }

    TRect barrier[6];
    barrier[0].setPosition(posX + 45, posY);
    barrier[0].setRectSize(50, 150);

    barrier[1].setPosition(posX + 185, posY);
    barrier[1].setRectSize(50, 250);

    barrier[5].setPosition(posX + 325, posY);
    barrier[5].setRectSize(50, 300);

    barrier[4].setPosition(posX + 1400 - 375, posY + ballBox.h - 300);
    barrier[4].setRectSize(50, 300);

    barrier[2].setPosition(posX + 1400 - 235, posY + ballBox.h - 250);
    barrier[2].setRectSize(50, 250);

    barrier[3].setPosition(posX + 1400 - 95, posY + ballBox.h - 150);
    barrier[3].setRectSize(50, 150);

    for (int i = 0; i < 4; i++)
    {
        barrier[i].setRectVelocity(0, (rand() % 2) + 4);
    }
    barrier[4].setRectVelocity(0, 3);
    barrier[5].setRectVelocity(0, 3);



    bool player1areDead = false;
    bool player2areDead = false;

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

                    alpha = 255;
                    betas = 185;

                    retry = true;
                    second = 0;
                    timer.Start();

                    player1areDead = false;
                    player2areDead = false;

                    player1areWin = false;
                    player2areWin = false;

                    pause = false;

                    player1.setPosition(posX + 20, posY + 70);
                    player1.shiftColliders();

                    player2.setPosition(posX + ballBox.w - 20, posY + ballBox.h - 70);
                    player2.shiftColliders();


                    barrier[0].setPosition(posX + 45, posY);
                    barrier[0].setRectSize(50, 150);

                    barrier[1].setPosition(posX + 185, posY);
                    barrier[1].setRectSize(50, 250);

                    barrier[5].setPosition(posX + 325, posY);
                    barrier[5].setRectSize(50, 300);

                    barrier[4].setPosition(posX + 1400 - 375, posY + ballBox.h - 300);
                    barrier[4].setRectSize(50, 300);

                    barrier[2].setPosition(posX + 1400 - 235, posY + ballBox.h - 250);
                    barrier[2].setRectSize(50, 250);

                    barrier[3].setPosition(posX + 1400 - 95, posY + ballBox.h - 150);
                    barrier[3].setRectSize(50, 150);

                    for (int i = 0; i < 4; i++)
                    {
                        barrier[i].setRectVelocity(0, (rand() % 2) + 4);
                    }
                    barrier[4].setRectVelocity(0, 3);
                    barrier[5].setRectVelocity(0, 3);

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
        game6.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game6.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);

        game6.treasure[curMap].render(treasure.x, treasure.y);

        barrier[0].render(game6.object[curMap], false, false);
        barrier[1].render(game6.wall[curMap], false, false);
        barrier[5].render(objecthighGame6[curMap], false, false);
        barrier[4].render(objecthighGame6[curMap], false, false);
        barrier[2].render(game6.wall[curMap], false, false);
        barrier[3].render(game6.object[curMap], false, false);


        if (!player1areWin && !player2areWin && !pause && second > 8)
        {
            player1.moveBall(wall, player2.getColliders(), ballBox, stepTime);
            player2.moveBall(wall, player1.getColliders(), ballBox, stepTime);

            for (int i = 0; i < 6; i++)
            {
                barrier[i].moveObject(ballBox, stepTime);
                if (!player1areDead)
                {
                    player1areDead = player1.areDeadRect(barrier[i].getColliders());
                }
                if (!player2areDead)
                {
                   player2areDead = player2.areDeadRect(barrier[i].getColliders());
                }

            }

            if (player1areDead)
            {
                player1.setPosition(posX + 20, posY + 70);
                player1.shiftColliders();
                player1areDead = false;
            }
            if (player2areDead)
            {
                player2.setPosition(posX + ballBox.w - 20, posY + ballBox.h - 70);
                player2.shiftColliders();
                player2areDead = false;
            }

            player1areWin = player1.areDeadRect(treasure);
            player2areWin = player2.areDeadRect(treasure);
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

