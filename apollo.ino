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