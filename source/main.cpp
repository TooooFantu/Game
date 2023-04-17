
#include "const.h"
#include "texture.h"
#include "sound.h"
#include "externtexture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <queue>

//:------------------------------

#include "introgame.h"
#include "menu.h"
#include "picteam.h"
#include "picgame.h"
#include "troducecup.h"
#include "callgame.h"
#include "getpoint.h"
#include "endgame.h"


using namespace std;

//Window and renderer:----------------------------------------------------------------------------------------------------------

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

//Class Texture:----------------------------------------------------------------------------------------------------------------

TTexture::TTexture()
{
    mTexture = NULL;

    mWidth = 0;
    mHeight = 0;
}


TTexture::~TTexture()
{
    free();
}


bool TTexture::loadFromfile(string path)
{
    free();

    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        cout << "Fail to load Surface! ERROR: " << IMG_GetError();
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL)
        {
            cout << "Fail to create Texture! ERROR: " << SDL_GetError();
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;

    return mTexture != NULL;
}


bool TTexture::loadFromRenderedText(string currentText, SDL_Color color, TTF_Font *font)
{
    free();

    SDL_Surface *loadedSurface = TTF_RenderText_Solid(font, currentText.c_str(), color);

    if (loadedSurface == NULL)
    {
        cout << "Fail to load Surface! ERROR: " << SDL_GetError();
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (mTexture == NULL)
        {
            cout << "Fail to create Texture! ERROR: " << SDL_GetError();
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return mTexture != NULL;
}


void TTexture::free()
{
    if (mTexture == NULL)
    {
        mTexture = NULL;

        mWidth = 0;
        mHeight = 0;
    }
}


void TTexture::setColor(Unit8 red, Unit8 green, Unit8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}


void TTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}


void TTexture::setAlpha(Unit8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}


void TTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


int TTexture::getWidth()
{
    return mWidth;
}


int TTexture::getHeight()
{
    return mHeight;
}


//Extern Texture:----------------------------------------------------------------------------------------------------------------

    //:-----------------------------------------------------------------------------

        TTexture draw;

        TTexture pauseTexture;

        TTexture bestcolor[5];

        TTexture quitBackground;

    //Button:----------------------------------------------------------------------

        TTexture newGameButton[2];

        TTexture quitGameButton[2];

        TTexture mainMenuButton[2];

        TTexture continueButton[2];

    //Intro Game:------------------------------------------------------------------

        TTexture logoFantu;

        TTexture logoColorBattle;

        TTexture introBackground[4];

        TTexture transitionBlack;

    //Player:---------------------------------------------------------------------

        TTexture playerBall[4];

        TTexture player1Rect[4];

        TTexture player2Rect[4];

        TTexture playerTank[4];

        TTexture playerBullet[4];

    //Timing & tutorial:------------------------------------------------------------

        TTexture countDown[3];

        TTexture tutorialWASD;

        TTexture tutorialWS;

        TTexture tutorialAD;

        TTexture tutorialW;

    //PicTeam:--------------------------------------------------------------------

        TTexture background[4][4];

        TTexture picPinkButton[3];

        TTexture picRedButton[3];

        TTexture picGreenButton[3];

        TTexture picGreyButton[3];

        TTexture picTeamTexture;

        TTexture border;

        TTexture picingPlayerTexture[2];

    //Picgame:-----------------------------------------

        TTexture troduceGame1[2];

        TTexture troduceGame2[2];

        TTexture troduceGame3[2];

        TTexture troduceGame4[2];

        TTexture troduceGame5[2];

        TTexture troduceGame6[2];

        TTexture troduceGame7[2];

        TTexture troduceGame8[2];

        TTexture gameButtonTexture[2];

        TTexture picBorder[2];

        TTexture gameNumber[5];

        TTexture picGameTitle;


    //GetPoin:-----------------------------------------

        TTexture playzone;

        TTexture fantuPoint;

        TTexture door;

        TTexture loserWall;


    //Game1:-------------------------------------------

        TFileGame game1;

    //Game2:-------------------------------------------

        TFileGame game2;

    //Game3:-------------------------------------------

        TFileGame game3;

    //Game4:-------------------------------------------

        TFileGame game4;

    //Game5:-------------------------------------------

        TFileGame game5;

        TTexture cnting[3];

    //Game6:-------------------------------------------

        TFileGame game6;

        TTexture objecthighGame6[2];

    //Game7:--------------------------------------------

        TFileGame game7;

    //Game8:--------------------------------------------

        TFileGame game8;

        TTexture point[5];

    //EndGame:-------------------------------------------

        TTexture winBackground[4];

        TTexture camera;



//Font:----------------------------------------------------------------------------------------------------------------

TTF_Font *gFont = NULL;

//Sound:--------------------------------------------------------------------------------------------------------------

    TSoundEffect intro[3];

    TMusic theme;

    TSoundEffect click;

    TSoundEffect cntdown;

    TSoundEffect cameraShutter;


//Init function:----------------------------------------------------------------------------------------------------------------

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "Fail to init SDL! ERROR: " << SDL_GetError();
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            cout << "Fail to linear! ERROR: " << SDL_GetError();
            success = false;
        }

        gWindow = SDL_CreateWindow("COLOR BATLE v.1027", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL)
        {
            cout << "Fail to create Window! ERROR: " << SDL_GetError();
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (gRenderer == NULL)
            {
                cout << "Fail to create Renderer! ERROR: " << SDL_GetError();
                success = false;
            }
            else
            {
                int imgFlag = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlag) & imgFlag))
                {
                    cout << "Fail to init SDL_image! ERROR: " << IMG_GetError();
                    success = false;
                }


                if (TTF_Init() == -1)
                {
                    cout << "Fail to init SDL_ttf! ERROR: " << TTF_GetError();
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "Fail to int SDL_mixer! ERROR: " << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}


//loadMedia function:----------------------------------------------------------------------------------------------------------------

bool loadMedia()
{
    bool success = true;

    //Texture:--------------------------------------------------------------------------------------------

        //:--------------------------------------------------------------------------------

        if (!draw.loadFromfile("res\\gfx\\draw.png"))
        {
            cout << "Fail to load draw";
            success = false;
        }
        if (!pauseTexture.loadFromfile("res\\gfx\\pause.png"))
        {
            cout << "Fail to load pause";
            success = false;
        }
        if (!bestcolor[0].loadFromfile("res\\gfx\\bestcolor\\pink.png"))
        {
            cout << "Fail to load pink";
            success = false;
        }
        if (!bestcolor[1].loadFromfile("res\\gfx\\bestcolor\\red.png"))
        {
            cout << "Fail to load red";
            success = false;
        }
        if (!bestcolor[2].loadFromfile("res\\gfx\\bestcolor\\green.png"))
        {
            cout << "Fail to load green";
            success = false;
        }
        if (!bestcolor[3].loadFromfile("res\\gfx\\bestcolor\\grey.png"))
        {
            cout << "Fail to load grey";
            success = false;
        }
        if (!bestcolor[4].loadFromfile("res\\gfx\\bestcolor\\none.png"))
        {
            cout << "Fail to load none";
            success = false;
        }
        if (!quitBackground.loadFromfile("res\\gfx\\quitbackground.png"))
        {
            cout << "Fail to load quitbackground";
            success = false;
        }

        //Button:--------------------------------------------------------------------------

        if (!newGameButton[0].loadFromfile("res\\gfx\\Button\\newGameBlue.png"))
        {
            cout << "Fail to load newgameblue!";
            success = false;
        }

        if (!newGameButton[1].loadFromfile("res\\gfx\\Button\\newGameYellow.png"))
        {
            cout << "Fail to load newgameyellow!";
            success = false;
        }

        if (!quitGameButton[0].loadFromfile("res\\gfx\\Button\\quitBlue.png"))
        {
            cout << "Fail to load quitblue!";
            success = false;
        }

        if (!quitGameButton[1].loadFromfile("res\\gfx\\Button\\quitYellow.png"))
        {
            cout << "Fail to load quityellow!";
            success = false;
        }
        if (!mainMenuButton[0].loadFromfile("res\\gfx\\Button\\mainMenuBlue.png"))
        {
            cout << "Fail to load mainmenublue";
            success = false;
        }
        if (!mainMenuButton[1].loadFromfile("res\\gfx\\Button\\mainMenuYellow.png"))
        {
            cout << "Fail to load mainmenuyellow";
            success = false;
        }
        if (!continueButton[0].loadFromfile("res\\gfx\\Button\\continueBlue.png"))
        {
            cout << "Fail to load continueblue";
            success = false;
        }
        if (!continueButton[1].loadFromfile("res\\gfx\\Button\\continueYellow.png"))
        {
            cout << "Fail to load continueyellow";
            success = false;
        }

        //Intro Game:----------------------------------------------------------------------

        if (!logoFantu.loadFromfile("res\\gfx\\introGame\\logoft.png"))
        {
            cout << "Fail to load logoFantu!";
            success = false;
        }
        else
        {
            logoFantu.setBlendMode(SDL_BLENDMODE_BLEND);
        }

        if (!logoColorBattle.loadFromfile("res\\gfx\\introGame\\gameLogo.png"))
        {
            cout << "Fail to load gameLogo!";
            success = false;
        }
        else
        {
            logoColorBattle.setBlendMode(SDL_BLENDMODE_BLEND);
        }

        if (!introBackground[0].loadFromfile("res\\gfx\\introGame\\background\\back1.png"))
        {
            cout << "Fail to load back1!";
            success = false;
        }

        if (!introBackground[1].loadFromfile("res\\gfx\\introGame\\background\\back2.png"))
        {
            cout << "Fail to load back2!";
            success = false;
        }

        if (!introBackground[2].loadFromfile("res\\gfx\\introGame\\background\\back3.png"))
        {
            cout << "Fail to load back3!";
            success = false;
        }

        if (!introBackground[3].loadFromfile("res\\gfx\\introGame\\background\\back4.png"))
        {
            cout << "Fail to load back4!";
            success = false;
        }

        if (!transitionBlack.loadFromfile("res\\gfx\\blacktransition.png"))
        {
            cout << "Fail to load blacktransition!";
            success = false;
        }

        //Player:--------------------------------------------------------------------

        if (!playerBall[0].loadFromfile("res\\gfx\\player\\ballpink.png"))
        {
            cout << "Fail to load ballpink";
            success = false;
        }
        if (!playerBall[1].loadFromfile("res\\gfx\\player\\ballred.png"))
        {
            cout << "Fail to load ballred";
            success = false;
        }
        if (!playerBall[2].loadFromfile("res\\gfx\\player\\ballgreen.png"))
        {
            cout << "Fail to load ballgreen";
            success = false;
        }
        if (!playerBall[3].loadFromfile("res\\gfx\\player\\ballgrey.png"))
        {
            cout << "Fail to load ballgrey";
            success = false;
        }

        if (!player1Rect[0].loadFromfile("res\\gfx\\player\\p11.png"))
        {
            cout << "Fail to load p11";
            success = false;
        }
        if (!player1Rect[1].loadFromfile("res\\gfx\\player\\p12.png"))
        {
            cout << "Fail to load p12";
            success = false;
        }
        if (!player1Rect[2].loadFromfile("res\\gfx\\player\\p13.png"))
        {
            cout << "Fail to load p13";
            success = false;
        }
        if (!player1Rect[3].loadFromfile("res\\gfx\\player\\p14.png"))
        {
            cout << "Fail to load p14";
            success = false;
        }
        if (!player2Rect[0].loadFromfile("res\\gfx\\player\\p21.png"))
        {
            cout << "Fail to load p21";
            success = false;
        }
        if (!player2Rect[1].loadFromfile("res\\gfx\\player\\p22.png"))
        {
            cout << "Fail to load p22";
            success = false;
        }
        if (!player2Rect[2].loadFromfile("res\\gfx\\player\\p23.png"))
        {
            cout << "Fail to load p23";
            success = false;
        }
        if (!player2Rect[3].loadFromfile("res\\gfx\\player\\p24.png"))
        {
            cout << "Fail to load p24";
            success = false;
        }

        if (!playerTank[0].loadFromfile("res\\gfx\\player\\tank1.png"))
        {
            cout << "Fail to load tank1";
            success = false;
        }
        if (!playerTank[1].loadFromfile("res\\gfx\\player\\tank2.png"))
        {
            cout << "Fail to load tank2";
            success = false;
        }
        if (!playerTank[2].loadFromfile("res\\gfx\\player\\tank3.png"))
        {
            cout << "Fail to load tank3";
            success = false;
        }
        if (!playerTank[3].loadFromfile("res\\gfx\\player\\tank4.png"))
        {
            cout << "Fail to load tank4";
            success = false;
        }

        if (!playerBullet[0].loadFromfile("res\\gfx\\player\\bullet1.png"))
        {
            cout << "Fail to load bullet1";
            success = false;
        }
        if (!playerBullet[1].loadFromfile("res\\gfx\\player\\bullet2.png"))
        {
            cout << "Fail to load bullet2";
            success = false;
        }
        if (!playerBullet[2].loadFromfile("res\\gfx\\player\\bullet3.png"))
        {
            cout << "Fail to load bullet3";
            success = false;
        }
        if (!playerBullet[3].loadFromfile("res\\gfx\\player\\bullet4.png"))
        {
            cout << "Fail to load bullet4";
            success = false;
        }



        //PicTeam:-------------------------------------------------------------------

        if (!background[0][0].loadFromfile("res\\gfx\\ingameBackground\\b10.png"))
        {
            cout << "Fail to load 10";
            success = false;
        }
        if (!background[0][1].loadFromfile("res\\gfx\\ingameBackground\\b12.png"))
        {
            cout << "Fail to load 12";
            success = false;
        }
        if (!background[0][2].loadFromfile("res\\gfx\\ingameBackground\\b13.png"))
        {
            cout << "Fail to load 13";
            success = false;
        }
        if (!background[0][3].loadFromfile("res\\gfx\\ingameBackground\\b14.png"))
        {
            cout << "Fail to load 14";
            success = false;
        }
        if (!background[1][0].loadFromfile("res\\gfx\\ingameBackground\\b21.png"))
        {
            cout << "Fail to load 21";
            success = false;
        }
        if (!background[1][1].loadFromfile("res\\gfx\\ingameBackground\\b20.png"))
        {
            cout << "Fail to load 20";
            success = false;
        }
        if (!background[1][2].loadFromfile("res\\gfx\\ingameBackground\\b23.png"))
        {
            cout << "Fail to load 23";
            success = false;
        }
        if (!background[1][3].loadFromfile("res\\gfx\\ingameBackground\\b24.png"))
        {
            cout << "Fail to load 24";
            success = false;
        }
        if (!background[2][0].loadFromfile("res\\gfx\\ingameBackground\\b31.png"))
        {
            cout << "Fail to load 31";
            success = false;
        }
        if (!background[2][1].loadFromfile("res\\gfx\\ingameBackground\\b32.png"))
        {
            cout << "Fail to load 32";
            success = false;
        }
        if (!background[2][2].loadFromfile("res\\gfx\\ingameBackground\\b30.png"))
        {
            cout << "Fail to load 30";
            success = false;
        }
        if (!background[2][3].loadFromfile("res\\gfx\\ingameBackground\\b34.png"))
        {
            cout << "Fail to load 34";
            success = false;
        }
        if (!background[3][0].loadFromfile("res\\gfx\\ingameBackground\\b41.png"))
        {
            cout << "Fail to load 41";
            success = false;
        }
        if (!background[3][1].loadFromfile("res\\gfx\\ingameBackground\\b42.png"))
        {
            cout << "Fail to load 42";
            success = false;
        }
        if (!background[3][2].loadFromfile("res\\gfx\\ingameBackground\\b43.png"))
        {
            cout << "Fail to load 43";
            success = false;
        }
        if (!background[3][3].loadFromfile("res\\gfx\\ingameBackground\\b40.png"))
        {
            cout << "Fail to load 40";
            success = false;
        }

        if (!picPinkButton[0].loadFromfile("res\\gfx\\picTeam\\pinkteam.png"))
        {
            cout << "Fail to load pinkteam";
            success = false;
        }
        if (!picPinkButton[1].loadFromfile("res\\gfx\\picTeam\\pinkteamchosen.png"))
        {
            cout << "Fail to load pinkteamchosen";
            success = false;
        }
        if (!picPinkButton[2].loadFromfile("res\\gfx\\picTeam\\selectingbutton.png"))
        {
            cout << "Fail to load pinkselecting";
            success = false;
        }
        if (!picRedButton[0].loadFromfile("res\\gfx\\picTeam\\redteam.png"))
        {
            cout << "Fail to load redteam";
            success = false;
        }
        if (!picRedButton[1].loadFromfile("res\\gfx\\picTeam\\redteamchosen.png"))
        {
            cout << "Fail to load redteamchosen";
            success = false;
        }
        if (!picRedButton[2].loadFromfile("res\\gfx\\picTeam\\selectingbutton.png"))
        {
            cout << "Fail to load redselecting";
            success = false;
        }
        if (!picGreenButton[0].loadFromfile("res\\gfx\\picTeam\\greenteam.png"))
        {
            cout << "Fail to load greenteam";
            success = false;
        }
        if (!picGreenButton[1].loadFromfile("res\\gfx\\picTeam\\greenteamchosen.png"))
        {
            cout << "Fail to load greenteamchosen";
            success = false;
        }
        if (!picGreenButton[2].loadFromfile("res\\gfx\\picTeam\\selectingbutton.png"))
        {
            cout << "Fail to load greenselecting";
            success = false;
        }
        if (!picGreyButton[0].loadFromfile("res\\gfx\\picTeam\\greyteam.png"))
        {
            cout << "Fail to load greyteam";
            success = false;
        }
        if (!picGreyButton[1].loadFromfile("res\\gfx\\picTeam\\greyteamchosen.png"))
        {
            cout << "Fail to load greyteamchosen";
            success = false;
        }
        if (!picGreyButton[2].loadFromfile("res\\gfx\\picTeam\\selectingbutton.png"))
        {
            cout << "Fail to load greyselecting";
            success = false;
        }

        if (!picTeamTexture.loadFromfile("res\\gfx\\picTeam\\titleSelectTeam.png"))
        {
            cout << "Fail to load selectTeamTitle";
            success = false;
        }

        if (!border.loadFromfile("res\\gfx\\picTeam\\border.png"))
        {
            cout << "Fail to load border";
            success = false;
        }

        if (!picingPlayerTexture[0].loadFromfile("res\\gfx\\picTeam\\player1.png"))
        {
            cout << "Fail to load player1";
            success = false;
        }

        if (!picingPlayerTexture[1].loadFromfile("res\\gfx\\picTeam\\player2.png"))
        {
            cout << "Fail to load player2";
            success = false;
        }

        //Picgame:--------------------------------------------------------------------------

        if (!troduceGame1[0].loadFromfile("res\\gfx\\picgame\\game11.png"))
        {
            cout << "Fail to load game11";
            success = false;
        }
        if (!troduceGame1[1].loadFromfile("res\\gfx\\picgame\\game12.png"))
        {
            cout << "Fail to load game12";
            success = false;
        }
        if (!troduceGame2[0].loadFromfile("res\\gfx\\picgame\\game21.png"))
        {
            cout << "Fail to load game21";
            success = false;
        }
        if (!troduceGame2[1].loadFromfile("res\\gfx\\picgame\\game22.png"))
        {
            cout << "Fail to load game22";
            success = false;
        }
        if (!troduceGame3[0].loadFromfile("res\\gfx\\picgame\\game31.png"))
        {
            cout << "Fail to load game31";
            success = false;
        }
        if (!troduceGame3[1].loadFromfile("res\\gfx\\picgame\\game32.png"))
        {
            cout << "Fail to load game32";
            success = false;
        }
        if (!troduceGame4[0].loadFromfile("res\\gfx\\picgame\\game41.png"))
        {
            cout << "Fail to load game41";
            success = false;
        }
        if (!troduceGame4[1].loadFromfile("res\\gfx\\picgame\\game42.png"))
        {
            cout << "Fail to load game42";
            success = false;
        }
        if (!troduceGame5[0].loadFromfile("res\\gfx\\picgame\\game51.png"))
        {
            cout << "Fail to load game51";
            success = false;
        }
        if (!troduceGame5[1].loadFromfile("res\\gfx\\picgame\\game52.png"))
        {
            cout << "Fail to load game52";
            success = false;
        }
        if (!troduceGame6[0].loadFromfile("res\\gfx\\picgame\\game61.png"))
        {
            cout << "Fail to load game61";
            success = false;
        }
        if (!troduceGame6[1].loadFromfile("res\\gfx\\picgame\\game62.png"))
        {
            cout << "Fail to load game62";
            success = false;
        }
        if (!troduceGame7[0].loadFromfile("res\\gfx\\picgame\\game71.png"))
        {
            cout << "Fail to load game71";
            success = false;
        }
        if (!troduceGame7[1].loadFromfile("res\\gfx\\picgame\\game72.png"))
        {
            cout << "Fail to load game72";
            success = false;
        }
        if (!troduceGame8[0].loadFromfile("res\\gfx\\picgame\\game81.png"))
        {
            cout << "Fail to load game81";
            success = false;
        }
        if (!troduceGame8[1].loadFromfile("res\\gfx\\picgame\\game82.png"))
        {
            cout << "Fail to load game82";
            success = false;
        }

        if (!gameButtonTexture[0].loadFromfile("res\\gfx\\picgame\\game1.png"))
        {
            cout << "Fail to load game1";
            success = false;
        }
        if (!gameButtonTexture[1].loadFromfile("res\\gfx\\picgame\\game2.png"))
        {
            cout << "Fail to load game2";
            success = false;
        }
        if (!picGameTitle.loadFromfile("res\\gfx\\picgame\\title.png"))
        {
            cout << "Fail to load title";
            success = false;
        }

        if (!gameNumber[0].loadFromfile("res\\gfx\\picgame\\number1.png"))
        {
            cout << "Fail to load number1";
            success = false;
        }
        if (!gameNumber[1].loadFromfile("res\\gfx\\picgame\\number2.png"))
        {
            cout << "Fail to load number2";
            success = false;
        }
        if (!gameNumber[2].loadFromfile("res\\gfx\\picgame\\number3.png"))
        {
            cout << "Fail to load number3";
            success = false;
        }
        if (!gameNumber[3].loadFromfile("res\\gfx\\picgame\\number4.png"))
        {
            cout << "Fail to load number4";
            success = false;
        }
        if (!gameNumber[4].loadFromfile("res\\gfx\\picgame\\number5.png"))
        {
            cout << "Fail to load number5";
            success = false;
        }

        if (!picBorder[0].loadFromfile("res\\gfx\\picgame\\border1.png"))
        {
            cout << "Fail to load border1";
            success = false;
        }
        if (!picBorder[1].loadFromfile("res\\gfx\\picgame\\border2.png"))
        {
            cout << "Fail to load border2";
            success = false;
        }

        //Timing & tutorial:----------------------------------------------------------------

        if (!countDown[0].loadFromfile("res\\gfx\\tutorial\\cnt3.png"))
        {
            cout << "Fail to load cnt3";
            success = false;
        }
        if (!countDown[1].loadFromfile("res\\gfx\\tutorial\\cnt2.png"))
        {
            cout << "Fail to load cnt2";
            success = false;
        }
        if (!countDown[2].loadFromfile("res\\gfx\\tutorial\\cnt1.png"))
        {
            cout << "Fail to load cnt1";
            success = false;
        }
        if (!tutorialWASD.loadFromfile("res\\gfx\\tutorial\\tutorial1.png"))
        {
            cout << "Fail to load tutorial1";
            success = false;
        }
        if (!tutorialWS.loadFromfile("res\\gfx\\tutorial\\tutorial2.png"))
        {
            cout << "Fail to load tutorial2";
            success = false;
        }
        if (!tutorialAD.loadFromfile("res\\gfx\\tutorial\\tutorial3.png"))
        {
            cout << "Fail to load tutorial3";
            success = false;
        }
        if (!tutorialW.loadFromfile("res\\gfx\\tutorial\\tutorial4.png"))
        {
            cout << "Fail to load tutorial4";
            success = false;
        }

        //GetPoint:-------------------------------------------------------------------------

        if (!playzone.loadFromfile("res\\gfx\\getpoint\\playzone.png"))
        {
            cout << "Fail to load playzone";
            success = false;
        }
        if (!fantuPoint.loadFromfile("res\\gfx\\getpoint\\point.png"))
        {
            cout << "Fail to load point";
            success = false;
        }
        if (!door.loadFromfile("res\\gfx\\getpoint\\door.png"))
        {
            cout << "Fail to load door";
            success = false;
        }
        if (!loserWall.loadFromfile("res\\gfx\\getpoint\\wall.png"))
        {
            cout << "Fail to load wall";
            success = false;
        }


        //Game1:----------------------------------------------------------------------------

        if (!game1.playzone[0].loadFromfile("res\\gfx\\game1\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game1.playzone[1].loadFromfile("res\\gfx\\game1\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game1.logo.loadFromfile("res\\gfx\\game1\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game1.object[0].loadFromfile("res\\gfx\\game1\\object1.png"))
        {
            cout << "Fail to load object1";
            success = false;
        }
        if (!game1.object[1].loadFromfile("res\\gfx\\game1\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }
        if (!game1.wall[0].loadFromfile("res\\gfx\\game1\\wall1.png"))
        {
            cout << "Fail to load wall1";
            success = false;
        }
        if (!game1.wall[1].loadFromfile("res\\gfx\\game1\\wall2.png"))
        {
            cout << "Fail to load wall2";
            success = false;
        }

        //Game2:-----------------------------------------------------------------------------

        if (!game2.object[0].loadFromfile("res\\gfx\\game2\\object1.png"))
        {
            cout << " Fail to load object1";
            success = false;
        }
        if (!game2.object[1].loadFromfile("res\\gfx\\game2\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }
        if (!game2.playzone[0].loadFromfile("res\\gfx\\game2\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game2.playzone[1].loadFromfile("res\\gfx\\game2\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game2.logo.loadFromfile("res\\gfx\\game2\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }


        //Game3:----------------------------------------------------------------------------

        if (!game3.playzone[0].loadFromfile("res\\gfx\\game3\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game3.playzone[1].loadFromfile("res\\gfx\\game3\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game3.logo.loadFromfile("res\\gfx\\game3\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game3.wall[0].loadFromfile("res\\gfx\\game3\\wall1.png"))
        {
            cout << "Fail to load wall1";
            success = false;
        }
        if (!game3.wall[1].loadFromfile("res\\gfx\\game3\\wall2.png"))
        {
            cout << "Fail to load wall2";
            success = false;
        }

        //Game4:---------------------------------------------------------------------------

        if (!game4.playzone[0].loadFromfile("res\\gfx\\game4\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game4.playzone[1].loadFromfile("res\\gfx\\game4\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game4.object[0].loadFromfile("res\\gfx\\game4\\object1.png"))
        {
            cout << "Fail to load object1";
            success = false;
        }
        if (!game4.object[1].loadFromfile("res\\gfx\\game4\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }
        if (!game4.logo.loadFromfile("res\\gfx\\game4\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game4.treasure[0].loadFromfile("res\\gfx\\game4\\treasure1.png"))
        {
            cout << "Fail to load treasure1";
            success = false;
        }
        if (!game4.treasure[1].loadFromfile("res\\gfx\\game4\\treasure2.png"))
        {
            cout << "Fail to load treasure2";
            success = false;
        }

        //Game5:---------------------------------------------------------------------------

        if (!game5.playzone[0].loadFromfile("res\\gfx\\game5\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game5.playzone[1].loadFromfile("res\\gfx\\game5\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game5.logo.loadFromfile("res\\gfx\\game5\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game5.object[0].loadFromfile("res\\gfx\\game5\\object1.png"))
        {
            cout << "Fail to load object1";
            success = false;
        }
        if (!game5.object[1].loadFromfile("res\\gfx\\game5\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }

        if (!cnting[0].loadFromfile("res\\gfx\\game5\\green.png"))
        {
            cout << "Fail to load green";
            success = false;
        }
        if (!cnting[1].loadFromfile("res\\gfx\\game5\\yellow.png"))
        {
            cout << "Fail to load yellow";
            success = false;
        }
        if (!cnting[2].loadFromfile("res\\gfx\\game5\\red.png"))
        {
            cout << "Fail to load red";
            success = false;
        }

        //Game6:--------------------------------------------------------------------------

        if (!game6.playzone[0].loadFromfile("res\\gfx\\game6\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game6.playzone[1].loadFromfile("res\\gfx\\game6\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game6.logo.loadFromfile("res\\gfx\\game6\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game6.treasure[0].loadFromfile("res\\gfx\\game6\\treasure1.png"))
        {
            cout << "Fail to load treasure1";
            success = false;
        }
        if (!game6.treasure[1].loadFromfile("res\\gfx\\game6\\treasure2.png"))
        {
            cout << "Fail to load treasure2";
            success = false;
        }
        if (!game6.object[0].loadFromfile("res\\gfx\\game6\\low1.png"))
        {
            cout << "Fail to load low1";
            success = false;
        }
        if (!game6.object[1].loadFromfile("res\\gfx\\game6\\low2.png"))
        {
            cout << "Fail to load low2";
            success = false;
        }
        if (!game6.wall[0].loadFromfile("res\\gfx\\game6\\mid1.png"))
        {
            cout << "Fail to load mid1";
            success = false;
        }
        if (!game6.wall[1].loadFromfile("res\\gfx\\game6\\mid2.png"))
        {
            cout << "Fail to load mid2";
            success = false;
        }

        if (!objecthighGame6[0].loadFromfile("res\\gfx\\game6\\high1.png"))
        {
            cout << "Fail to load high1";
            success = false;
        }
        if (!objecthighGame6[1].loadFromfile("res\\gfx\\game6\\high2.png"))
        {
            cout << "Fail to load high2";
            success = false;
        }

        //Game7:----------------------------------------------------------------------------

        if (!game7.logo.loadFromfile("res\\gfx\\game7\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game7.playzone[0].loadFromfile("res\\gfx\\game7\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game7.playzone[1].loadFromfile("res\\gfx\\game7\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game7.object[0].loadFromfile("res\\gfx\\game7\\object1.png"))
        {
            cout << "Fail to load object1";
            success = false;
        }
        if (!game7.object[1].loadFromfile("res\\gfx\\game7\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }

        //Game8:----------------------------------------------------------------------------

        if (!game8.logo.loadFromfile("res\\gfx\\game8\\logo.png"))
        {
            cout << "Fail to load logo";
            success = false;
        }
        if (!game8.object[0].loadFromfile("res\\gfx\\game8\\object1.png"))
        {
            cout << "Fail to load object1";
            success = false;
        }
        if (!game8.object[1].loadFromfile("res\\gfx\\game8\\object2.png"))
        {
            cout << "Fail to load object2";
            success = false;
        }
        if (!game8.playzone[0].loadFromfile("res\\gfx\\game8\\playzone1.png"))
        {
            cout << "Fail to load playzone1";
            success = false;
        }
        if (!game8.playzone[1].loadFromfile("res\\gfx\\game8\\playzone2.png"))
        {
            cout << "Fail to load playzone2";
            success = false;
        }
        if (!game8.treasure[0].loadFromfile("res\\gfx\\game8\\treasure1.png"))
        {
            cout << "Fail to load treasure1";
            success = false;
        }
        if (!game8.treasure[1].loadFromfile("res\\gfx\\game8\\treasure2.png"))
        {
            cout << "Fail to load treasure2";
            success = false;
        }
        if (!game8.wall[0].loadFromfile("res\\gfx\\game8\\wall1.png"))
        {
            cout << "Fail to load wall1";
            success = false;
        }
        if (!game8.wall[1].loadFromfile("res\\gfx\\game8\\wall2.png"))
        {
            cout << "Fail to load wal2";
            success = false;
        }

        if (!point[0].loadFromfile("res\\gfx\\game8\\point1.png"))
        {
            cout << "Fail to load point1";
            success = false;
        }
        if (!point[1].loadFromfile("res\\gfx\\game8\\point2.png"))
        {
            cout << "Fail to load point2";
            success = false;
        }
        if (!point[2].loadFromfile("res\\gfx\\game8\\point3.png"))
        {
            cout << "Fail to load point3";
            success = false;
        }
        if (!point[3].loadFromfile("res\\gfx\\game8\\point4.png"))
        {
            cout << "Fail to load point4";
            success = false;
        }
        if (!point[4].loadFromfile("res\\gfx\\game8\\point5.png"))
        {
            cout << "Fail to load point5";
            success = false;
        }

        //EndGame:------------------------------------------------------------------------------

        if (!camera.loadFromfile("res\\gfx\\winbackground\\camera.png"))
        {
            cout << "Fail to load camera";
            success = false;
        }
        if (!winBackground[0].loadFromfile("res\\gfx\\winbackground\\pink.png"))
        {
            cout << "Fail to load pink";
            success = false;
        }
        if (!winBackground[1].loadFromfile("res\\gfx\\winbackground\\red.png"))
        {
            cout << "Fail to load red";
            success = false;
        }
        if (!winBackground[2].loadFromfile("res\\gfx\\winbackground\\green.png"))
        {
            cout << "Fail to load green";
            success = false;
        }
        if (!winBackground[3].loadFromfile("res\\gfx\\winbackground\\grey.png"))
        {
            cout << "Fail to load grey";
            success = false;
        }


    //Sound:--------------------------------------------------------------------------------------------

        //Intro:---------------------------------------------------------------

        if (!intro[0].loadFormfile("res\\sfx\\intro\\intro1.wav"))
        {
            cout << "Fail to load intro1!";
            success = false;
        }

        if (!intro[1].loadFormfile("res\\sfx\\intro\\intro2.wav"))
        {
            cout << "Fail to load intro2!";
            success = false;
        }

        if (!intro[2].loadFormfile("res\\sfx\\intro\\intro3.wav"))
        {
            cout << "Fail to load intro3";
            success = false;
        }

        if (!theme.loadFromfile("res\\sfx\\funk.wav"))
        {
            cout << "Fail to load theme";
            success = false;
        }

        if (!click.loadFormfile("res\\sfx\\click.wav"))
        {
            cout << "Fail to load click";
            success = false;
        }
        if (!cntdown.loadFormfile("res\\sfx\\countdown.wav"))
        {
            cout << "Fail to load countdownsound";
            success = false;
        }

        if (!cameraShutter.loadFormfile("res\\sfx\\camera.wav"))
        {
            cout << "Fail to load camera";
            success = false;
        }

        //Game1:----------------------------------------------------------





    return success;
}


//close function:----------------------------------------------------------------------------------------------------------------

void close()
{

    //Texture:--------------------------------------------------------------------------------------------

        //:-----------------------------------

            draw.free();

            pauseTexture.free();

            for (int i = 0; i < 5; i++)
            {
                bestcolor[i].free();
            }

            quitBackground.free();

        //Button:----------------------------

            for (int i = 0; i < 2; i++)
            {
                newGameButton[i].free();
                quitGameButton[i].free();
            }


        //Intro Game:------------------------

            logoFantu.free();
            logoColorBattle.free();
            transitionBlack.free();

            for (int i = 0; i < 4; i++)
            {
                introBackground[i].free();
            }

        //PLayer:-----------------------------

            for (int i = 0; i < 4; i++)
            {
                playerBall[i].free();
                player1Rect[i].free();
                player2Rect[i].free();
                playerTank[i].free();
                playerBullet[i].free();
            }

        //Picteam:----------------------------

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    background[i][i].free();
                }
            }

            for (int i = 0; i < 3; i++)
            {
                picPinkButton[i].free();
                picRedButton[i].free();
                picGreenButton[i].free();
                picGreyButton[i].free();
            }

            picTeamTexture.free();

            border.free();

            for (int i = 0; i < 2; i++)
            {
                picingPlayerTexture[i].free();
                objecthighGame6[i].free();
            }

        //Picgame:-----------------------------

                for (int i = 0; i < 2; i++)
                {
                    troduceGame1[i].free();
                    troduceGame2[i].free();
                    troduceGame3[i].free();
                    troduceGame4[i].free();
                    troduceGame5[i].free();
                    troduceGame6[i].free();
                    troduceGame7[i].free();
                    troduceGame8[i].free();
                    gameButtonTexture[i].free();
                    picBorder[i].free();
                }

                picGameTitle.free();

                for (int i = 0; i < 5; i++)
                {
                    gameNumber[i].free();
                }


        //Timing & tutorial:-----------------------

            tutorialWASD.free();
            tutorialWS.free();
            tutorialAD.free();
            tutorialW.free();

            for (int i = 0; i < 3; i++)
            {
                countDown[i].free();
                cnting[i].free();
            }

            for (int i = 0; i < 5; i++)
            {
                point[i].free();
            }

        //GetPoint:-------------------------------

            playzone.free();
            fantuPoint.free();
            door.free();
            loserWall.free();

        //Game:-----------------------------------

            game1.free();
            game2.free();
            game3.free();
            game4.free();
            game5.free();
            game6.free();
            game7.free();
            game8.free();

        //EndGame:--------------------------------

            for (int i = 0; i < 4; i++)
            {
                winBackground[i].free();
            }

            camera.free();



    //Sound:------------------------------------------------------------------------------------------------

        //Intro:-----------------------------

            for (int i = 0; i < 3; i++)
            {
                intro[i].free();
            }

            theme.free();

        //Game1:-----------------------------

            camera.free();

            click.free();

            cntdown.free();



    //:--------------------------------------------------------------------------------------------

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

//main function:----------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    if (init())
    {
        if (loadMedia())
        {
            bool quit = false;

            bool skipIntro = false;

            while (!quit)
            {
                int p1 = 0;
                int p2 = 0;

                queue <int> game;

                int player1Point = 0;
                int player2Point = 0;

                bool player1Win = true;

                bool backToMenu = false;

                //:-------------------------------------------------------------

                if (!skipIntro)
                {
                    introgame(gRenderer, quit);
                }

                 skipIntro = true;

                if (quit || backToMenu)
                {
                    continue;
                }

                menuscreen(gRenderer, quit);
                if (quit)
                {
                    continue;
                }

                picteam(gRenderer, quit, backToMenu, p1, p2);
                if (quit || backToMenu)
                {
                    continue;
                }

                picgame(gRenderer, quit, backToMenu, p1, p2, game);
                if (quit || backToMenu)
                {
                    continue;
                }

                troduceCup(gRenderer, quit, backToMenu, p1, p2);
                if (quit || backToMenu)
                {
                    continue;
                }
                //Game[1]:--------------------------------------------------------
                callGame(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, game, player1Win);
                if (quit || backToMenu)
                {
                    continue;
                }
                getPoint(gRenderer, quit, backToMenu, p1, p2, player1Win, player1Point, player2Point);
                if (quit || backToMenu)
                {
                    continue;
                }
                //Game[2]:-------------------------------------------------------
                callGame(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, game, player1Win);
                if (quit || backToMenu)
                {
                    continue;
                }
                getPoint(gRenderer, quit, backToMenu, p1, p2, player1Win, player1Point, player2Point);
                if (quit || backToMenu)
                {
                    continue;
                }
                //Game[3]:-------------------------------------------------------
                callGame(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, game, player1Win);
                if (quit || backToMenu)
                {
                    continue;
                }
                getPoint(gRenderer, quit, backToMenu, p1, p2, player1Win, player1Point, player2Point);
                if (quit || backToMenu)
                {
                    continue;
                }
                //Game[4]:-------------------------------------------------------

                if (player1Point < 3 && player2Point < 3)
                {
                    callGame(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, game, player1Win);
                    if (quit || backToMenu)
                    {
                        continue;
                    }
                    getPoint(gRenderer, quit, backToMenu, p1, p2, player1Win, player1Point, player2Point);
                    if (quit || backToMenu)
                    {
                        continue;
                    }
                }

                //Game[5]:-------------------------------------------------------

                if (player1Point < 3 && player2Point < 3)
                {
                    callGame(gRenderer, quit, backToMenu, p1, p2, player1Point, player2Point, game, player1Win);
                    if (quit || backToMenu)
                    {
                        continue;
                    }
                    getPoint(gRenderer, quit, backToMenu, p1, p2, player1Win, player1Point, player2Point);
                    if (quit || backToMenu)
                    {
                        continue;
                    }
                    quit = true;
                }

                endgame(gRenderer, quit, p1, p2, player1Win);

                //:-------------------------------------------------------------


            }
        }

    }
    close();
    return 0;
}


