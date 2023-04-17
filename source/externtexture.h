#pragma once

#include "texture.h"
#include "sound.h"
#include "structure.h"



//Texture:----------------------------------------------------------------------------------------------

    //:--------------------------------------
        extern TTexture draw;

        extern TTexture pauseTexture;

        extern TTexture bestcolor[5];

        extern TTexture quitBackground;


    //Button:--------------------------------

        extern TTexture newGameButton[2];

        extern TTexture quitGameButton[2];

        extern TTexture mainMenuButton[2];

        extern TTexture continueButton[2];


    //Intro:---------------------------------
        extern TTexture logoFantu;

        extern TTexture logoColorBattle;

        extern TTexture introBackground[4];

        extern TTexture transitionBlack;


    //Player:--------------------------------
        extern TTexture playerBall[4];

        extern TTexture player1Rect[4];

        extern TTexture player2Rect[4];

        extern TTexture playerTank[4];

        extern TTexture playerBullet[4];

    //Timing & tutorial:---------------------

        extern TTexture countDown[3];

        extern TTexture tutorialWASD;

        extern TTexture tutorialWS;

        extern TTexture tutorialAD;

        extern TTexture tutorialW;

    //Picteam:-------------------------------
        extern TTexture background[4][4];

        extern TTexture picPinkButton[3];

        extern TTexture picRedButton[3];

        extern TTexture picGreenButton[3];

        extern TTexture picGreyButton[3];

        extern TTexture picTeamTexture;

        extern TTexture border;

        extern TTexture picingPlayerTexture[2];

    //Picgame:---------------------------------
        extern TTexture troduceGame1[2];

        extern TTexture troduceGame2[2];

        extern TTexture troduceGame3[2];

        extern TTexture troduceGame4[2];

        extern TTexture troduceGame5[2];

        extern TTexture troduceGame6[2];

        extern TTexture troduceGame7[2];

        extern TTexture troduceGame8[2];

        extern TTexture gameButtonTexture[2];

        extern TTexture picBorder[2];

        extern TTexture gameNumber[5];

        extern TTexture picGameTitle;

    //GetPoint:--------------------------------

        extern TTexture playzone;

        extern TTexture fantuPoint;

        extern TTexture door;

        extern TTexture loserWall;



    //Game1:-----------------------------------
        extern TFileGame game1;

    //Game2:-----------------------------------
        extern TFileGame game2;

    //Game3:----------------------------------
        extern TFileGame game3;

    //Game4:-----------------------------------
        extern TFileGame game4;

    //Game5:-----------------------------------
        extern TFileGame game5;

        extern TTexture cnting[3];

    //Game6:-----------------------------------
        extern TFileGame game6;

        extern TTexture objecthighGame6[2];
    //Game7:-----------------------------------
        extern TFileGame game7;

    //Game8:------------------------------------
        extern TFileGame game8;

        extern TTexture point[5];

    //EndGame:
        extern TTexture winBackground[4];

        extern TTexture camera;

//Sound:----------------------------------------------------------------------------------------------

extern TSoundEffect intro[3];

extern TMusic theme;

extern TSoundEffect click;

extern TSoundEffect cntdown;

extern TSoundEffect cameraShutter;
