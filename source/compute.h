#pragma once

#include "structure.h"
#include "const.h"

#include <SDL.h>
#include <vector>


using namespace std;



bool checkCollision(LCircle& a, LCircle& b);


bool checkCollision(LCircle& a, vector <SDL_Rect>& b);


bool checkCollision(LCircle& a, SDL_Rect& b);


bool checkCollision(SDL_Rect& a, vector <SDL_Rect>& b);


bool changeVelX(LCircle& a, vector <SDL_Rect>& b, LPoint flashBack);


bool changeVelY(LCircle& a, vector <SDL_Rect>& b, LPoint flashBack);


double distanceSquared(int x1, int y1, int x2, int y2);


void getVel(int& velX, int& velY, Unit32 a, int velocity);
