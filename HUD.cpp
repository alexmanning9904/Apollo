#include "HUD.h"

void HUD::Update(Arduboy2 arduboy, Lander lander)
{
    //Draw fuel bar
    arduboy.fillRect(FUEL_X, 64 - 64*((float)lander.fuel/lander.max_fuel), FUEL_WIDTH, 64*((float)lander.fuel/lander.max_fuel));

    //Draw the motion indicator
    arduboy.drawRect(INDICATOR_X-INDICATOR_WIDTH, INDICATOR_Y-INDICATOR_WIDTH, 2*INDICATOR_WIDTH, 2*INDICATOR_WIDTH); //Outer Ring
    arduboy.drawLine(
        INDICATOR_X,
        INDICATOR_Y,
        (lander.dx>INDICATOR_MAX) ? (INDICATOR_X+INDICATOR_WIDTH) : ((lander.dx<-INDICATOR_MAX) ? (INDICATOR_X-INDICATOR_WIDTH) : (INDICATOR_X + (INDICATOR_WIDTH*lander.dx/INDICATOR_MAX))),
        (lander.dy>INDICATOR_MAX) ? (INDICATOR_Y+INDICATOR_WIDTH) : ((lander.dy<-INDICATOR_MAX) ? (INDICATOR_Y-INDICATOR_WIDTH) : (INDICATOR_Y + (INDICATOR_WIDTH*lander.dy/INDICATOR_MAX)))
    );


}