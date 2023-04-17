#pragma once

#include <SDL.h>
#include <queue>


using namespace std;



void picgame(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, queue <int>& game);

