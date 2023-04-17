
#include "picgame.h"
#include "texture.h"
#include "const.h"
#include "mouseButton.h"
#include "externtexture.h"
#include "quitmenu.h"

#include <SDL.h>
#include <queue>


using namespace std;



void picgame(SDL_Renderer* gRenderer, bool& quit, bool& backToMenu, int p1, int p2, queue <int>& game)
{
    SDL_Event e;
    bool outLoop = false;

    bool picGame = true;

    Unit8 alpha = 0;


    TMouseButton game1Button;
    game1Button.setButtonPosition(100, 300);
    game1Button.setButtonSize(300, 150);

    bool game1Chosen = false;

    bool game1Over = false;

        TMouseButton game11Button;
        game11Button.setButtonPosition(100, 300);
        game11Button.setButtonSize(150, 150);

        bool game11Over = false;
        bool game11Click = false;

        TMouseButton game12Button;
        game12Button.setButtonPosition(250, 300);
        game12Button.setButtonSize(150, 150);

        bool game12Click = false;

    TMouseButton game2Button;
    game2Button.setButtonPosition(500, 300);
    game2Button.setButtonSize(300, 150);

    bool game2Chosen = false;

    bool game2Over = false;

        TMouseButton game21Button;
        game21Button.setButtonPosition(500, 300);
        game21Button.setButtonSize(150, 150);

        bool game21Over = false;
        bool game21Click = false;

        TMouseButton game22Button;
        game22Button.setButtonPosition(650, 300);
        game22Button.setButtonSize(150, 150);

        bool game22Click = false;

    TMouseButton game3Button;
    game3Button.setButtonPosition(900, 300);
    game3Button.setButtonSize(300, 150);

    bool game3Chosen = false;

    bool game3Over = false;

        TMouseButton game31Button;
        game31Button.setButtonPosition(900, 300);
        game31Button.setButtonSize(150, 150);

        bool game31Over = false;
        bool game31Click = false;

        TMouseButton game32Button;
        game32Button.setButtonPosition(1050, 300);
        game32Button.setButtonSize(150, 150);

        bool game32Click = false;

    TMouseButton game4Button;
    game4Button.setButtonPosition(1300, 300);
    game4Button.setButtonSize(300, 150);

    bool game4Chosen = false;

    bool game4Over = false;

        TMouseButton game41Button;
        game41Button.setButtonPosition(1300, 300);
        game41Button.setButtonSize(150, 150);

        bool game41Over = false;
        bool game41Click = false;

        TMouseButton game42Button;
        game42Button.setButtonPosition(1450, 300);
        game42Button.setButtonSize(150, 150);

        bool game42Click = false;

    TMouseButton game5Button;
    game5Button.setButtonPosition(100, 750);
    game5Button.setButtonSize(300, 150);

    bool game5Chosen = false;

    bool game5Over = false;

        TMouseButton game51Button;
        game51Button.setButtonPosition(100, 750);
        game51Button.setButtonSize(150, 150);

        bool game51Over = false;
        bool game51Click = false;

        TMouseButton game52Button;
        game52Button.setButtonPosition(250, 750);
        game52Button.setButtonSize(150, 150);

        bool game52Click = false;

    TMouseButton game6Button;
    game6Button.setButtonPosition(500, 750);
    game6Button.setButtonSize(300, 150);

    bool game6Chosen = false;

    bool game6Over = false;

        TMouseButton game61Button;
        game61Button.setButtonPosition(500, 750);
        game61Button.setButtonSize(150, 150);

        bool game61Over = false;
        bool game61Click = false;

        TMouseButton game62Button;
        game62Button.setButtonPosition(650, 750);
        game62Button.setButtonSize(150, 150);

        bool game62Click = false;

    TMouseButton game7Button;
    game7Button.setButtonPosition(900, 750);
    game7Button.setButtonSize(300, 150);

    bool game7Chosen = false;

    bool game7Over = false;

        TMouseButton game71Button;
        game71Button.setButtonPosition(900, 750);
        game71Button.setButtonSize(150, 150);

        bool game71Over = false;
        bool game71Click = false;

        TMouseButton game72Button;
        game72Button.setButtonPosition(1050, 750);
        game72Button.setButtonSize(150, 150);

        bool game72Click = false;

    TMouseButton game8Button;
    game8Button.setButtonPosition(1300, 750);
    game8Button.setButtonSize(300, 150);

    bool game8Chosen = false;

    bool game8Over = false;

        TMouseButton game81Button;
        game81Button.setButtonPosition(1300, 750);
        game81Button.setButtonSize(150, 150);

        bool game81Over = false;
        bool game81Click = false;

        TMouseButton game82Button;
        game82Button.setButtonPosition(1450, 750);
        game82Button.setButtonSize(150, 150);

        bool game82Click = false;


    while (!outLoop)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quitmenu(gRenderer, quit, backToMenu);
                if (quit || backToMenu)
                {
                    outLoop = true;
                    theme.stopMusic();
                }
            }

            game1Over = game1Button.mouseInButton(&e);
            game11Over = game11Button.mouseInButton(&e);
            game11Click = game11Button.mouseClickInButton(&e);
            game12Click = game12Button.mouseClickInButton(&e);

            game2Over = game2Button.mouseInButton(&e);
            game21Over = game21Button.mouseInButton(&e);
            game21Click = game21Button.mouseClickInButton(&e);
            game22Click = game22Button.mouseClickInButton(&e);

            game3Over = game3Button.mouseInButton(&e);
            game31Over = game31Button.mouseInButton(&e);
            game31Click = game31Button.mouseClickInButton(&e);
            game32Click = game32Button.mouseClickInButton(&e);

            game4Over = game4Button.mouseInButton(&e);
            game41Over = game41Button.mouseInButton(&e);
            game41Click = game41Button.mouseClickInButton(&e);
            game42Click = game42Button.mouseClickInButton(&e);

            game5Over = game5Button.mouseInButton(&e);
            game51Over = game51Button.mouseInButton(&e);
            game51Click = game51Button.mouseClickInButton(&e);
            game52Click = game52Button.mouseClickInButton(&e);

            game6Over = game6Button.mouseInButton(&e);
            game61Over = game61Button.mouseInButton(&e);
            game61Click = game61Button.mouseClickInButton(&e);
            game62Click = game62Button.mouseClickInButton(&e);

            game7Over = game7Button.mouseInButton(&e);
            game71Over = game71Button.mouseInButton(&e);
            game71Click = game71Button.mouseClickInButton(&e);
            game72Click = game72Button.mouseClickInButton(&e);

            game8Over = game8Button.mouseInButton(&e);
            game81Over = game81Button.mouseInButton(&e);
            game81Click = game81Button.mouseClickInButton(&e);
            game82Click = game82Button.mouseClickInButton(&e);
        }

        //:-------------------------------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        //:-------------------------------------------------------------

        background[p1][p2].render(0, 0);

        picGameTitle.render(500, 50);


        if (game.size() == 10)
        {
            picGame = false;
        }


        if (picGame)
        {
            gameNumber[game.size() / 2].render(600, 500);
        }



        if (!game1Chosen)
        {
            game1Button.render(gameButtonTexture[0]);

            if (game1Over)
            {
                game11Button.render(troduceGame1[0]);
                game12Button.render(troduceGame1[1]);

                if (game11Over)
                {
                    game11Button.render(picBorder[1]);
                    game12Button.render(picBorder[0]);
                }
                else
                {
                    game11Button.render(picBorder[0]);
                    game12Button.render(picBorder[1]);
                }

                if (game11Click && picGame)
                {
                    game.push(0);
                    game.push(1);
                    game1Chosen = true;
                    click.playSoundEffect();
                }
                if (game12Click && picGame)
                {
                    game.push(1);
                    game.push(1);
                    game1Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game1Button.render(gameButtonTexture[1]);
        }


        if (!game2Chosen)
        {
            game2Button.render(gameButtonTexture[0]);

            if (game2Over)
            {
                game21Button.render(troduceGame2[0]);
                game22Button.render(troduceGame2[1]);

                if (game21Over)
                {
                    game21Button.render(picBorder[1]);
                    game22Button.render(picBorder[0]);
                }
                else
                {
                    game21Button.render(picBorder[0]);
                    game22Button.render(picBorder[1]);
                }

                if (game21Click && picGame)
                {
                    game.push(0);
                    game.push(2);
                    game2Chosen = true;
                    click.playSoundEffect();
                }
                if (game22Click && picGame)
                {
                    game.push(1);
                    game.push(2);
                    game2Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game2Button.render(gameButtonTexture[1]);
        }

        if (!game3Chosen)
        {
            game3Button.render(gameButtonTexture[0]);

            if (game3Over)
            {
                game31Button.render(troduceGame3[0]);
                game32Button.render(troduceGame3[1]);

                if (game31Over)
                {
                    game31Button.render(picBorder[1]);
                    game32Button.render(picBorder[0]);
                }
                else
                {
                    game31Button.render(picBorder[0]);
                    game32Button.render(picBorder[1]);
                }

                if (game31Click && picGame)
                {
                    game.push(0);
                    game.push(3);
                    game3Chosen = true;
                    click.playSoundEffect();
                }
                if (game32Click && picGame)
                {
                    game.push(1);
                    game.push(3);
                    game3Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game3Button.render(gameButtonTexture[1]);
        }

        if (!game4Chosen)
        {
            game4Button.render(gameButtonTexture[0]);

            if (game4Over)
            {
                game41Button.render(troduceGame4[0]);
                game42Button.render(troduceGame4[1]);

                if (game41Over)
                {
                    game41Button.render(picBorder[1]);
                    game42Button.render(picBorder[0]);
                }
                else
                {
                    game41Button.render(picBorder[0]);
                    game42Button.render(picBorder[1]);
                }

                if (game41Click && picGame)
                {
                    game.push(0);
                    game.push(4);
                    game4Chosen = true;
                    click.playSoundEffect();
                }
                if (game42Click && picGame)
                {
                    game.push(1);
                    game.push(4);
                    game4Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game4Button.render(gameButtonTexture[1]);
        }

        if (!game5Chosen)
        {
            game5Button.render(gameButtonTexture[0]);

            if (game5Over)
            {
                game51Button.render(troduceGame5[0]);
                game52Button.render(troduceGame5[1]);

                if (game51Over)
                {
                    game51Button.render(picBorder[1]);
                    game52Button.render(picBorder[0]);
                }
                else
                {
                    game51Button.render(picBorder[0]);
                    game52Button.render(picBorder[1]);
                }

                if (game51Click && picGame)
                {
                    game.push(0);
                    game.push(5);
                    game5Chosen = true;
                    click.playSoundEffect();
                }
                if (game52Click && picGame)
                {
                    game.push(1);
                    game.push(5);
                    game5Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game5Button.render(gameButtonTexture[1]);
        }

        if (!game6Chosen)
        {
            game6Button.render(gameButtonTexture[0]);

            if (game6Over)
            {
                game61Button.render(troduceGame6[0]);
                game62Button.render(troduceGame6[1]);

                if (game61Over)
                {
                    game61Button.render(picBorder[1]);
                    game62Button.render(picBorder[0]);
                }
                else
                {
                    game61Button.render(picBorder[0]);
                    game62Button.render(picBorder[1]);
                }

                if (game61Click && picGame)
                {
                    game.push(0);
                    game.push(6);
                    game6Chosen = true;
                    click.playSoundEffect();
                }
                if (game62Click && picGame)
                {
                    game.push(1);
                    game.push(6);
                    game6Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game6Button.render(gameButtonTexture[1]);
        }

        if (!game7Chosen)
        {
            game7Button.render(gameButtonTexture[0]);

            if (game7Over)
            {
                game71Button.render(troduceGame7[0]);
                game72Button.render(troduceGame7[1]);

                if (game71Over)
                {
                    game71Button.render(picBorder[1]);
                    game72Button.render(picBorder[0]);
                }
                else
                {
                    game71Button.render(picBorder[0]);
                    game72Button.render(picBorder[1]);
                }

                if (game71Click && picGame)
                {
                    game.push(0);
                    game.push(7);
                    game7Chosen = true;
                    click.playSoundEffect();
                }
                if (game72Click && picGame)
                {
                    game.push(1);
                    game.push(7);
                    game7Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game71Button.render(gameButtonTexture[1]);
        }

        if (!game8Chosen)
        {
            game8Button.render(gameButtonTexture[0]);

            if (game8Over)
            {
                game81Button.render(troduceGame8[0]);
                game82Button.render(troduceGame8[1]);

                if (game81Over)
                {
                    game81Button.render(picBorder[1]);
                    game82Button.render(picBorder[0]);
                }
                else
                {
                    game81Button.render(picBorder[0]);
                    game82Button.render(picBorder[1]);
                }

                if (game81Click && picGame)
                {
                    game.push(0);
                    game.push(8);
                    game8Chosen = true;
                    click.playSoundEffect();
                }
                if (game82Click && picGame)
                {
                    game.push(1);
                    game.push(8);
                    game8Chosen = true;
                    click.playSoundEffect();
                }

            }
        }
        else
        {
            game8Button.render(gameButtonTexture[1]);
        }

        if (!picGame)
        {
            alpha += 2;
            transitionBlack.setAlpha(alpha);
            transitionBlack.render(0, 0);
        }

        if (alpha == 254)
        {
            outLoop = true;
        }


    SDL_RenderPresent(gRenderer);
    }
}
