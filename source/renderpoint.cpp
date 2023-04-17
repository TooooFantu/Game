
#include "renderpoint.h"
#include "externtexture.h"
#include "texture.h"



void renderPoint(int player1Point, int player2Point)
{
    if (player1Point > 0)
    {
        fantuPoint.render(550, 20);
    }
    if (player1Point > 1)
    {
        fantuPoint.render(400, 20);
    }


    if (player2Point > 0)
    {
        fantuPoint.render(1050, 20);
    }
    if (player2Point > 1)
    {
        fantuPoint.render(1200, 20);
    }
}
