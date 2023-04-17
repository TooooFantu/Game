
#include "game1.h"
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


void callGame1(SDL_Renderer *gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    SDL_Rect ballZone = {480, 320, 740, 360};
    SDL_Rect objectZone = {150, 150, 1400, 700};

    TBall object[6];

    object[0].setPosition(objectZone.x + 20, objectZone.y + 20);
    object[1].setPosition(objectZone.x + 20, objectZone.y + objectZone.h - 30);
    object[2].setPosition(objectZone.x + objectZone.w - 20, objectZone.y + 20);
    object[3].setPosition(objectZone.x + objectZone.w - 20, objectZone.y + objectZone.h - 20);
    object[4].setPosition(objectZone.x + (objectZone.w / 2) - 15, objectZone.y + 20);
    object[5].setPosition(objectZone.x + (objectZone.w / 2) - 15, objectZone.y + objectZone.h - 20);

    for (int i = 0; i < 6; i++)
    {
        object[i].shiftColliders();
    }

    TBall player1;
    player1.setPosition(500, 350);
    player1.shiftColliders();

    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(1200, 650);
    player2.shiftColliders();


    bool p2Up = false;
    bool p2Down = false;
    bool p2Left = false;
    bool p2Right = false;

    bool player1areDead = false;
    bool player2areDead = false;

    bool pause = false;

    bool playCountDown = true;

    //Object vector:---------------------
    LVector v[6];

    v[0].x = (rand() % 4) + 1; v[0].y = (rand() % 4) + 1;
    v[1].x = (rand() % 4) + 1; v[1].y = (rand() % 4) + 1;
    v[2].x = (rand() % 4) + 1; v[2].y = (rand() % 4) + 1;
    v[3].x = (rand() % 4) + 1; v[3].y = (rand() % 4) + 1;
    v[4].x = (rand() % 4) + 1; v[4].y = (rand() % 4) + 1;
    v[5].x = (rand() % 4) + 1; v[5].y = (rand() % 4) + 1;
    //:-----------------------------------

    int velocity = 8;

    bool level1 = true;
    bool level2 = true;
    bool level3 = true;

    //Wall:-------------------------------
    SDL_Rect wall1 = {300, 200, 100, 100};
    SDL_Rect wall2 = {1300, 200, 100, 100};
    SDL_Rect wall3 = {300, 700, 100, 100};
    SDL_Rect wall4 = {1300, 700, 100, 100};

    vector <SDL_Rect> wall;

    wall.push_back(wall1);
    wall.push_back(wall2);
    wall.push_back(wall3);
    wall.push_back(wall4);

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
                            level1 = true;
                            level2 = true;
                            level3 = true;

                            playCountDown = true;

                            retry = true;
                            second = 0;
                            timer.Start();

                            velocity = 8;

                            player1areDead = false;
                            player2areDead = false;
                            pause = false;

                            player1.setPosition(500, 350);
                            player1.shiftColliders();
                            player2.setPosition(1200, 650);
                            player2.shiftColliders();

                            v[0].x = (rand() % 4) + 1; v[0].y = (rand() % 4) + 1;
                            v[1].x = (rand() % 4) + 1; v[1].y = (rand() % 4) + 1;
                            v[2].x = (rand() % 4) + 1; v[2].y = (rand() % 4) + 1;
                            v[3].x = (rand() % 4) + 1; v[3].y = (rand() % 4) + 1;
                            v[4].x = (rand() % 4) + 1; v[4].y = (rand() % 4) + 1;
                            v[5].x = (rand() % 4) + 1; v[5].y = (rand() % 4) + 1;

                            object[0].setPosition(objectZone.x + 20, objectZone.y + 20);
                            object[1].setPosition(objectZone.x + 20, objectZone.y + objectZone.h - 30);
                            object[2].setPosition(objectZone.x + objectZone.w - 20, objectZone.y + 20);
                            object[3].setPosition(objectZone.x + objectZone.w - 20, objectZone.y + objectZone.h - 20);
                            object[4].setPosition(objectZone.x + (objectZone.w / 2) - 15, objectZone.y + 20);
                            object[5].setPosition(objectZone.x + (objectZone.w / 2) - 15, objectZone.y + objectZone.h - 20);

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
        game1.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game1.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);
        game1.wall[curMap].render(wall1.x, wall1.y);
        game1.wall[curMap].render(wall2.x, wall2.y);
        game1.wall[curMap].render(wall3.x, wall3.y);
        game1.wall[curMap].render(wall4.x, wall4.y);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);

        for (int i = 0; i < 6; i++)
        {
            object[i].render(game1.object[curMap]);
        }


        if (second > 8)
        {
            if (!player1areDead && !player2areDead && !pause)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        object[i].moveObject(v[i], velocity, wall, objectZone, stepTime);
                        if (!player1areDead)
                        {
                            player1areDead = player1.areDeadCircle(object[i].getColliders());
                        }
                        if (!player2areDead)
                        {
                            player2areDead = player2.areDeadCircle(object[i].getColliders());
                        }
                    }
                    player1.moveBall(wall, player2.getColliders(), ballZone, stepTime);
                    player2.moveBall(wall, player1.getColliders(), ballZone, stepTime);
                }
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

        if (second > 60 && level1)
        {
            velocity += 2;
            level1 = false;
        }

        if (second > 120 && level2)
        {
            velocity += 2;
            level2 = false;
        }

        if (second > 180 && level3)
        {
            velocity += 2;
            level3 = false;
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

