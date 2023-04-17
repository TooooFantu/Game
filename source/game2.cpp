
#include "game2.h"
#include "texture.h"
#include "externtexture.h"
#include "ball.h"
#include "rect.h"
#include "const.h"
#include "timer.h"
#include "renderpoint.h"
#include "quitmenu.h"

#include <SDL.h>
#include <vector>


using namespace std;



void callGame2(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, int curMap, bool& player1Win)
{
    SDL_Event e;
    bool outLoop = false;

    theme.stopMusic();

    bool levelUp = true;

    int BoxYline = 850;

    int posX = 150;

    SDL_Rect p1Box = {150, 820, 820, 30};
    SDL_Rect p2Box = {730, 820, 820, 30};

    SDL_Rect playZone = {150, 140, 1400, 850};

    vector <SDL_Rect> wall;


    int objectVelocity = 4;

    TRect object1[2];
    object1[0].setPosition(posX, 0);
    object1[0].setRectSize(500, 70);
    object1[1].setPosition(posX + 800, 0);
    object1[1].setRectSize(500, 70);

    bool moveOb1 = false;

    TRect object2[2];
    object2[0].setPosition(posX + 100, 0);
    object2[0].setRectSize(600, 70);
    object2[1].setPosition(posX + 900, 0);
    object2[1].setRectSize(400, 70);

    bool moveOb2 = false;

    TRect object3[5];
    object3[0].setPosition(posX, 0);
    object3[0].setRectSize(200, 70);
    object3[1].setPosition(posX + 300, 0);
    object3[1].setRectSize(200, 70);
    object3[2].setPosition(posX + 600, 0);
    object3[2].setRectSize(200, 70);
    object3[3].setPosition(posX + 900, 0);
    object3[3].setRectSize(200, 70);
    object3[4].setPosition(posX + 1200, 0);
    object3[4].setRectSize(200, 70);

    bool moveOb3 = false;

    TRect object4;
    object4.setPosition(posX + 50, 0);
    object4.setRectSize(1300, 70);

    bool moveOb4 = false;

    TRect object5[2];
    object5[0].setPosition(posX, 0);
    object5[0].setRectSize(600, 70);
    object5[1].setPosition(posX + 800, 0);
    object5[1].setRectSize(600, 70);

    bool moveOb5 = false;

    TRect object6[3];
    object6[0].setPosition(posX, 0);
    object6[0].setRectSize(1400, 70);
    object6[1].setPosition(posX, 70);
    object6[1].setRectSize(650, 70);
    object6[2].setPosition(posX + 750, 70);
    object6[2].setRectSize(650, 70);


    TBall player1;
    player1.setPosition(p1Box.x + 15, p1Box.y + p1Box.h - 15);
    player1.shiftColliders();


    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(p2Box.x + p2Box.w - 15, p2Box.y + p2Box.h - 15);
    player2.shiftColliders();


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

    int time = 3;

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
                    levelUp = true;

                    retry = true;
                    second = 0;
                    time = 3;
                    timer.Start();

                    player1areDead = false;
                    player2areDead = false;
                    pause = false;

                    player1.setPosition(p1Box.x + 15, p1Box.y + p1Box.h - 15);
                    player1.shiftColliders();

                    player2.setPosition(p2Box.x + p2Box.w - 15, p2Box.y + p2Box.h - 15);
                    player2.shiftColliders();

                    object1[0].setPosition(posX, 0);
                    object1[0].setRectSize(500, 70);
                    object1[1].setPosition(posX + 800, 0);
                    object1[1].setRectSize(500, 70);

                    object2[0].setPosition(posX + 100, 0);
                    object2[0].setRectSize(600, 70);
                    object2[1].setPosition(posX + 900, 0);
                    object2[1].setRectSize(400, 70);

                    object3[0].setPosition(posX, 0);
                    object3[0].setRectSize(200, 70);
                    object3[1].setPosition(posX + 300, 0);
                    object3[1].setRectSize(200, 70);
                    object3[2].setPosition(posX + 600, 0);
                    object3[2].setRectSize(200, 70);
                    object3[3].setPosition(posX + 900, 0);
                    object3[3].setRectSize(200, 70);
                    object3[4].setPosition(posX + 1200, 0);
                    object3[4].setRectSize(200, 70);

                    object4.setPosition(posX + 50, 0);
                    object4.setRectSize(1300, 70);

                    object5[0].setPosition(posX, 0);
                    object5[0].setRectSize(600, 70);
                    object5[1].setPosition(posX + 800, 0);
                    object5[1].setRectSize(600, 70);

                    object6[0].setPosition(posX, 0);
                    object6[0].setRectSize(1400, 70);
                    object6[1].setPosition(posX, 70);
                    object6[1].setRectSize(650, 70);
                    object6[2].setPosition(posX + 750, 70);
                    object6[2].setRectSize(650, 70);

                    moveOb1 = false;
                    moveOb2 = false;
                    moveOb3 = false;
                    moveOb4 = false;
                    moveOb5 = false;

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
        game2.playzone[curMap].render(playZoneRenderPosX, playZoneRenderPosY);
        game2.logo.render((SCREEN_WIDTH - game1.logo.getWidth()) / 2, 15);

        renderPoint(player1Point, player2Point);

        pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, 880);

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);

        for (int i = 0; i < 2; i++)
        {
            if (object1[i].inRect(playZone))
            {
                object1[i].render(game2.object[curMap], true, true);
            }
            if (object2[i].inRect(playZone))
            {
                object2[i].render(game2.object[curMap], true, true);
            }
            if (object5[i].inRect(playZone))
            {
                object5[i].render(game2.object[curMap], true, true);
            }
        }

        if (object4.inRect(playZone))
        {
            object4.render(game2.object[curMap], true, true);
        }

        for (int i = 0; i < 5; i++)
        {
            if (object3[i].inRect(playZone))
            {
                object3[i].render(game2.object[curMap], true, true);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (object6[i].inRect(playZone))
            {
                object6[i].render(game2.object[curMap], true, true);
            }
        }







        if (!player1areDead && !player2areDead && !pause)
        {
            if (second > 8)
            {
                player1.moveBall(wall, player2.getColliders(), p1Box, stepTime);
                player2.moveBall(wall, player1.getColliders(), p2Box, stepTime);
            }

            if (moveOb1)
            {
                bool stop = true;
                for (int i = 0; i < 2; i++)
                {
                    if (!object1[i].moveObjectDown(objectVelocity, BoxYline, stepTime) && stop)
                    {
                        object1[0].setPosition(posX, 0);
                        object1[0].setRectSize(500, 70);
                        object1[1].setPosition(posX + 800, 0);
                        object1[1].setRectSize(500, 70);
                        moveOb1 = false;
                        stop = false;
                    }
                    if (!player1areDead)
                    {
                        player1areDead = player1.areDeadRect(object1[i].getColliders());
                    }
                    if (!player2areDead)
                    {
                        player2areDead = player2.areDeadRect(object1[i].getColliders());
                    }
                }
            }

            if (moveOb2)
            {
                bool stop = true;
                for (int i = 0; i < 2; i++)
                {
                    if (!object2[i].moveObjectDown(objectVelocity, BoxYline, stepTime) && stop)
                    {
                        object2[0].setPosition(posX + 100, 0);
                        object2[0].setRectSize(600, 70);
                        object2[1].setPosition(posX + 900, 0);
                        object2[1].setRectSize(400, 70);
                        moveOb2 = false;
                        stop = false;
                    }
                    if (!player1areDead)
                    {
                        player1areDead = player1.areDeadRect(object2[i].getColliders());
                    }
                    if (!player2areDead)
                    {
                        player2areDead = player2.areDeadRect(object2[i].getColliders());
                    }
                }
            }


            if (moveOb3)
            {
                bool stop = true;
                for (int i = 0; i < 5; i++)
                {
                    if (!object3[i].moveObjectDown(objectVelocity, BoxYline, stepTime) && stop)
                    {
                        object3[0].setPosition(posX, 0);
                        object3[0].setRectSize(200, 70);
                        object3[1].setPosition(posX + 300, 0);
                        object3[1].setRectSize(200, 70);
                        object3[2].setPosition(posX + 600, 0);
                        object3[2].setRectSize(200, 70);
                        object3[3].setPosition(posX + 900, 0);
                        object3[3].setRectSize(200, 70);
                        object3[4].setPosition(posX + 1200, 0);
                        object3[4].setRectSize(200, 70);
                        moveOb3 = false;
                        stop = false;
                    }
                    if (!player1areDead)
                    {
                        player1areDead = player1.areDeadRect(object3[i].getColliders());
                    }
                    if (!player2areDead)
                    {
                        player2areDead = player2.areDeadRect(object3[i].getColliders());
                    }
                }
            }

            if (moveOb4)
            {
                if (!object4.moveObjectDown(objectVelocity, BoxYline, stepTime))
                {
                    object4.setPosition(posX + 50, 0);
                    object4.setRectSize(1300, 70);
                    moveOb4 = false;
                }

                if (!player1areDead)
                {
                    player1areDead = player1.areDeadRect(object4.getColliders());
                }
                if (!player2areDead)
                {
                    player2areDead = player2.areDeadRect(object4.getColliders());
                }
            }

            if (moveOb5)
            {
                bool stop = true;
                for (int i = 0; i < 2; i++)
                {
                    if (!object5[i].moveObjectDown(objectVelocity, BoxYline, stepTime) && stop)
                    {
                        object5[0].setPosition(posX, 0);
                        object5[0].setRectSize(600, 70);
                        object5[1].setPosition(posX + 800, 0);
                        object5[1].setRectSize(600, 70);
                        moveOb5 = false;
                        stop = false;
                    }
                    if (!player1areDead)
                    {
                        player1areDead = player1.areDeadRect(object5[i].getColliders());
                    }
                    if (!player2areDead)
                    {
                        player2areDead = player2.areDeadRect(object5[i].getColliders());
                    }
                }
            }


            if (second > 8 && second < 180 && second > (3 * time))
            {
                int callObject = (rand() % 5) + 1;
                switch (callObject)
                {
                    case 1:
                        moveOb1 = true;
                        ++time;
                        break;
                    case 2:
                        moveOb2 = true;
                        ++time;
                        break;
                    case 3:
                        moveOb3 = true;
                        ++time;
                        break;
                    case 4:
                        moveOb4 = true;
                        ++time;
                        break;
                    case 5:
                        moveOb5 = true;
                        ++time;
                        break;
                }
            }

            if (second > 120 && levelUp)
            {
                objectVelocity ++;
                levelUp = false;
            }



            if (second > 180)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (object6[i].moveObjectDown(objectVelocity, BoxYline, stepTime))
                    {
                        if (!player1areDead)
                        {
                            player1areDead = player1.areDeadRect(object6[i].getColliders());
                        }
                        if (!player2areDead)
                        {
                            player2areDead = player2.areDeadRect(object6[i].getColliders());
                        }
                    }
                }
            }


        }





        if (second < 5)
        {
            if (alpha != 0)
            {
                alpha -= 3;
            }
            tutorialAD.setAlpha(betas);
            tutorialAD.render(0, 0);
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
