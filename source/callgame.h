#pragma once

#include <SDL.h>
#include <queue>


using namespace std;



void callGame(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, int player1Point, int player2Point, queue <int>& game, bool& player1Win);
