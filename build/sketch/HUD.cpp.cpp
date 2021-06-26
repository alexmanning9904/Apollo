#include <Arduino.h>
#line 13 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino"
void setup();
#line 21 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino"
void loop();
#line 0 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino"
#line 1 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\HUD.cpp"
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
#line 1 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino"
#include "Lander.h"
#include "HUD.h"
#include "Map.h"
#include "Levels.h"

Arduboy2 arduboy;
Lander lander;
HUD hud;
Map gamemap;

float theta;

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(30);
    lander.Set(64, 32, 0, 0, 0, 1000);
    gamemap.Set(SUPERFLAT, sizeof(SUPERFLAT)/sizeof(*SUPERFLAT));
}

void loop()
{
    //Wait for a new frame
    if(!arduboy.nextFrame())
        return;

    arduboy.clear();  //Clear the Screen
    arduboy.pollButtons();  //Update the Buttons

    if(gamemap.Altitude(lander.x, lander.y) > SCREEN_HEIGHT*0.75)
    {
        lander.Update(arduboy, MAP_WIDTH, MAP_HEIGHT, 0, 0);
        gamemap.Draw(arduboy, MAP_WIDTH, MAP_HEIGHT, 0, 0);
    }
    else
    {
        lander.Update(arduboy, SCREEN_WIDTH, SCREEN_HEIGHT, lander.x-((float)SCREEN_WIDTH/2), (lander.y + gamemap.Altitude(lander.x, lander.y)) - (SCREEN_HEIGHT*0.75));
        gamemap.Draw(arduboy, SCREEN_WIDTH, SCREEN_HEIGHT, lander.x-((float)SCREEN_WIDTH/2), (lander.y + gamemap.Altitude(lander.x, lander.y)) - (SCREEN_HEIGHT*0.75));
    }

    hud.Update(arduboy, lander);

    arduboy.display();
}
