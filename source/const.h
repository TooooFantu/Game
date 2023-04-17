#pragma once
#include <SDL.h>


//Typedef:----------------------------------------------------------------------------------------------------------------

typedef unsigned char Unit8;
typedef unsigned int Unit32;


//Color:----------------------------------------------------------------------------------------------------------------

const SDL_Color gWhite = {0xFF, 0xFF, 0xFF};
const SDL_Color gBlack = {0, 0, 0};
const SDL_Color gRed = {0xFF, 0, 0};
const SDL_Color gPink = {0xFF, 153, 153};
const SDL_Color gYellow = {0xFF, 0xFF, 0};
const SDL_Color gGreen = {0, 0xFF, 0xFF};
const SDL_Color gBlue = {0, 0xFF, 0xFF};
const SDL_Color gGray = {192, 192, 192};
const SDL_Color gPurple = {0xFF, 0, 0xFF};
const SDL_Color gBrown = {153, 76, 0};
const SDL_Color gSea = {0, 0, 0xFF};

//Screen size:----------------------------------------------------------------------------------------------------------------

const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 950;

//RenderPos:------------------------------------------------------------------------------------------------------------------

const int playZoneRenderPosX = 130;
const int playZoneRenderPosY = 130;

