
#include "callgame.h"
#include "game1.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "game5.h"
#include "game6.h"
#include "game7.h"
#include "game8.h"


#include <SDL.h>
#include <queue>


using namespace std;



void callGame(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, queue <int>& game, bool& player1Win)
{
    int curMap = game.front();
    game.pop();
    int curGame = game.front();
    game.pop();

    switch (curGame)
    {
        case 1:
            callGame1(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 2:
            callGame2(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 3:
            callGame3(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 4:
            callGame4(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 5:
            callGame5(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 6:
            callGame6(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 7:
            callGame7(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;

        case 8:
            callGame8(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, curMap, player1Win);
            break;
    }

}
