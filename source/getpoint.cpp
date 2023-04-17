
#include "getpoint.h"
#include "externtexture.h"
#include "texture.h"
#include "ball.h"
#include "const.h"
#include "rect.h"
#include "renderpoint.h"
#include "quitmenu.h"
#include "timer.h"

#include <SDL.h>
#include <vector>


using namespace std;



void getPoint(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, bool player1Win, int& player1Point, int& player2Point)
{
    SDL_Event e;
    bool outLoop = false;

    Unit8 alpha = 254;
    Unit8 betas = 0;

    bool p1done = false;
    bool p1GetTreasure = false;

    bool p2done = false;
    bool p2GetTreasure = false;

    SDL_Rect ballBox = {40, 10, 1620, 930};

    SDL_Rect point1 = {0, 0, 10, 10};

    if (player1Point == 0)
    {
        point1 = {550, 20, 100, 100};
    }
    else if (player1Point == 1)
    {
        point1 = {400, 20, 100, 100};
    }
    else if (player1Point == 2)
    {
        point1 = {250, 20, 100, 100};
    }

    SDL_Rect point2;

    if (player2Point == 0)
    {
        point2 = {1050, 20, 100, 100};
    }
    else if (player2Point == 1)
    {
        point2 = {1200, 20, 100, 100};
    }
    else if (player2Point == 2)
    {
        point2 = {1350, 20, 100, 100};
    }

    TRect door1;
    door1.setPosition(130, 450);
    door1.setRectSize(20, 100);


    TRect door2;
    door2.setPosition(1550, 450);
    door2.setRectSize(20, 100);

    vector <SDL_Rect> wall;

    SDL_Rect wallll[8];
    wallll[0] = {130, 130, 1440, 20};
    wallll[1] = {130, 130, 20, 320};
    wallll[2] = {130, 850, 1440, 20};
    wallll[3] = {1550, 130, 20, 320};
    wallll[4] = {700, 0, 300, 150};
    wallll[5] = {0, 850, 1700, 100};
    wallll[6] = {130, 550, 20, 320};
    wallll[7] = {1550, 550, 20, 320};

    for (int i = 0; i < 8; i++)
    {
        wall.push_back(wallll[i]);
    }

    SDL_Rect loser;

    if (player1Win)
    {
        loser = {1200, 150, 50, 700};
    }
    else
    {
        loser = {450, 150, 50, 700};
    }

    wall.push_back(loser);

    TTimer timerStep;
    float stepTime = 0;



    TRect treasure;
    treasure.setPosition(800, 500);
    treasure.setRectSize(100, 100);
    treasure.shiftColliders();


    TBall player1;
    player1.setPosition(175, 575);
    player1.shiftColliders();

    bool p1Up = false;
    bool p1Down = false;
    bool p1Left = false;
    bool p1Right = false;

    TBall player2;
    player2.setPosition(1525, 575);
    player2.shiftColliders();


    bool p2Up = false;
    bool p2Down = false;
    bool p2Left = false;
    bool p2Right = false;

    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                timerStep.Pause();
                quitmenu(gRenderer, quit, backToMenu);
                timerStep.unPause();
                if (quit || backToMenu)
                {
                    outLoop = true;
                    theme.stopMusic();
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

        background[p1][p2].render(0, 0);
        renderPoint(player1Point, player2Point);

        playzone.render(playZoneRenderPosX, playZoneRenderPosY);

        loserWall.render(loser.x, loser.y);

        door1.render(door, false, false);
        door2.render(door, false, false);

        wall.push_back(door1.getColliders());
        wall.push_back(door2.getColliders());

        player1.render(playerBall[p1]);
        player2.render(playerBall[p2]);


        if (alpha == 0)
        {
            player1.moveBall(wall, player2.getColliders(), ballBox, stepTime);
            player2.moveBall(wall, player1.getColliders(), ballBox, stepTime);
        }

        wall.pop_back();
        wall.pop_back();

        if (!p1done && !p2done)
        {
            treasure.render(fantuPoint, false, false);
        }

        if (p1done)
        {
            fantuPoint.render(point1.x, point1.y);
            betas += 2;
            transitionBlack.setAlpha(betas);
            transitionBlack.render(0, 0);
        }
        if (p2done)
        {
            fantuPoint.render(point2.x, point2.y);
            betas += 2;
            transitionBlack.setAlpha(betas);
            transitionBlack.render(0, 0);
        }

        if (p1GetTreasure)
        {
            treasure.setPosition(player1.getPositionX() - 75, player1.getPositionY() - 25);

            if (door1.getHeight() > 0)
            {
                door1.setRectSize(20 ,door1.getHeight() - 1);
            }

            if (player1.areDeadRect(point1))
            {
                p1done = true;
            }
        }

        if (p2GetTreasure)
        {
            treasure.setPosition(player2.getPositionX() - 25, player2.getPositionY() - 25);

            if (door2.getHeight() > 0)
            {
                door2.setRectSize(20, door2.getHeight() - 1);
            }

            if (player2.areDeadRect(point2))
            {
                p2done = true;
            }
        }

        if (player1.areDeadRect(treasure.getColliders()))
        {
            p1GetTreasure = true;
        }

        if (player2.areDeadRect(treasure.getColliders()))
        {
            p2GetTreasure = true;
        }


        if (alpha != 0)
        {
            transitionBlack.setAlpha(alpha);
            transitionBlack.render(0, 0);
            alpha -= 2;
        }


        if (betas == 254)
        {
            if (player1Win)
            {
                player1Point++;
            }
            else
            {
                player2Point++;
            }
            outLoop = true;
        }


        timerStep.Start();


    SDL_RenderPresent(gRenderer);
    }
}
