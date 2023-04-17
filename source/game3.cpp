
#include "game3.h"
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



void callGame3(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    int changBallLine = 850;

    int posX = 150;
    int posY = 150;

    int rectVelocity = 5;
    int ballVeclocity = 8;

    SDL_Rect ballZone = {posX - 20, posX, 1440, 700};

    SDL_Rect p1DeadZone = {posX, posY, 78, 700};
    SDL_Rect p2DeadZone = {posX + 1320, posY, 78, 700};

    TRect player1;
    player1.setPosition(posX - 25, posY + 300);
    player1.setRectVelocity(0, 0);
    player1.setRectSize(110, 100);

    bool upDown1 = false;

    TRect player2;
    player2.setPosition(posX + 1290 + 25, posY + 300);
    player2.setRectVelocity(0, 0);
    player2.setRectSize(110, 100);

    bool upDown2 = false;

    SDL_Rect wall1 = {800, 250, 100, 100};
    SDL_Rect wall2 = {800, 650, 100, 100};

    vector <SDL_Rect> wall;

    wall.push_back(wall1);
    wall.push_back(wall2);



    TBall object1;
    object1.setPosition(850, 500);
    object1.shiftColliders();
    LVector v1;
    v1.x = (rand() % 4) + 1;
    v1.y = (rand() % 3) + 2;

    TBall object2;
    object2.setPosition(850, 500);
    object2.shiftColliders();
    LVector v2;
    v2.x = 1;
    v2.y = 1;

    bool player1areDead = false;
    bool player2areDead = false;

    bool pause = false;

    bool playCountDown = true;

    bool levelUp1 = true;

    bool levelUp2 = true;

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

                player1.setRectVelocity(0, 0);
                player2.setRectVelocity(0, 0);

                upDown1 = false;
                upDown2 = false;
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

                    upDown1 = false;
                    upDown2 = false;

                    levelUp1 = true;
                    levelUp2 = true;

                    ballVeclocity = 8;

                    rectVelocity = 5;

                    v1.x = (rand() % 4) + 1;
                    v1.y = (rand() % 3) + 2;

                    player1.setPosition(posX - 25, posY + 300);
                    player1.setRectVelocity(0, 0);

                    player2.setPosition(posX + 1290 + 25, posY + 300);
                    player2.setRectVelocity(0, 0);

                    object1.setPosition(850, 500);
                    object1.shiftColliders();

                    object2.setPosition(850, 500);
                    object2.shiftColliders();
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
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                if (e.key.keysym.sym == SDLK_UP)
                {
                    player2.setRectVelocity(0, -rectVelocity);
                    upDown2 = true;
                }

                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    player2.setRectVelocity(0, rectVelocity);
                    upDown2 = false;
                }

                if (e.key.keysym.sym == SDLK_w)
                {
                    player1.setRectVelocity(0, -rectVelocity);
                    upDown1 = true;
                }

                if (e.key.keysym.sym == SDLK_s)
                {
                    player1.setRectVelocity(0, rectVelocity);
                    upDown1 = false;
                }
            }
            else if (e.type == SDL_KEYUP && e.key.repeat == 0)
            {
                if (e.key.keysym.sym == SDLK_UP && upDown2)
                {
                    player2.setRectVelocity(0, 0);
                }

                if (e.key.keysym.sym == SDLK_DOWN && !upDown2)
                {
                    player2.setRectVelocity(0, 0);
                }

                if (e.key.keysym.sym == SDLK_w && upDown1)
                {
                    player1.setRectVelocity(0, 0);
                }

                if (e.key.keysym.sym == SDLK_s && !upDown1)
                {
                    player1.setRectVelocity(0, 0);
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
        game3.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game3.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);


        player1.render(player1Rect[p1], false, false);
        player2.render(player2Rect[p2], false, false);

        if (object1.getPositionX() < changBallLine)
        {
            object1.render(playerBall[p1]);
        }
        else
        {
            object1.render(playerBall[p2]);
        }

        if (second > 90)
        {
            if (object2.getPositionX() > changBallLine)
            {
                object2.render(playerBall[p1]);
            }
            else
            {
                object2.render(playerBall[p2]);
            }
        }

        game3.wall[curMap].render(wall1.x, wall1.y);
        game3.wall[curMap].render(wall2.x, wall2.y);

        if (!player1areDead && !player2areDead && !pause)
        {
            if (second > 8)
            {
                player1.moveRect(ballZone, player2.getColliders(), wall, stepTime);
                player2.moveRect(ballZone, player1.getColliders(), wall, stepTime);

                wall.push_back(player1.getColliders());
                wall.push_back(player2.getColliders());


                object1.moveObject(v1, ballVeclocity, wall, ballZone, stepTime);

                if (second > 95)
                {
                    object2.moveObject(v2, 5, wall, ballZone, stepTime);
                }

                wall.pop_back();
                wall.pop_back();
                player1areDead = checkCollision(object1.getColliders(), p1DeadZone);
                if (!player1areDead)
                {
                    player1areDead = checkCollision(object2.getColliders(), p1DeadZone);
                }
                player2areDead = checkCollision(object1.getColliders(), p2DeadZone);
                if (!player2areDead)
                {
                    player2areDead = checkCollision(object2.getColliders(), p2DeadZone);
                }

            }

            if (second > 30 && levelUp1)
            {
                ballVeclocity += 2;
                rectVelocity += 2;
                levelUp1 = false;
            }

            if (second > 60 && levelUp2)
            {
                ballVeclocity++;
                rectVelocity ++;
                levelUp2 = false;
            }
        }



        if (second < 5)
        {
            if (alpha != 0)
            {
                alpha -= 3;
            }
            tutorialWS.setAlpha(betas);
            tutorialWS.render(0, 0);
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
