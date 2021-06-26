# 1 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\HUD.cpp"
# 2 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\HUD.cpp" 2

void HUD::Update(Arduboy2 arduboy, Lander lander)
{
    //Draw fuel bar
    arduboy.fillRect(127 /*X-location of the fuel bar (pixels).  No Y-location, since it takes the whole screen*/, 64 - 64*((float)lander.fuel/lander.max_fuel), 2 /*Width of the fuel bar (pixels)*/, 64*((float)lander.fuel/lander.max_fuel));

    //Draw the motion indicator
    arduboy.drawRect(100 /*X-location of the center of the indicator*/-10 /*Half-width of the indicator square*/, 20 /*Y-Location of the center of the indicator*/-10 /*Half-width of the indicator square*/, 2*10 /*Half-width of the indicator square*/, 2*10 /*Half-width of the indicator square*/); //Outer Ring
    arduboy.drawLine(
        100 /*X-location of the center of the indicator*/,
        20 /*Y-Location of the center of the indicator*/,
        (lander.dx>0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/) ? (100 /*X-location of the center of the indicator*/+10 /*Half-width of the indicator square*/) : ((lander.dx<-0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/) ? (100 /*X-location of the center of the indicator*/-10 /*Half-width of the indicator square*/) : (100 /*X-location of the center of the indicator*/ + (10 /*Half-width of the indicator square*/*lander.dx/0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/))),
        (lander.dy>0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/) ? (20 /*Y-Location of the center of the indicator*/+10 /*Half-width of the indicator square*/) : ((lander.dy<-0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/) ? (20 /*Y-Location of the center of the indicator*/-10 /*Half-width of the indicator square*/) : (20 /*Y-Location of the center of the indicator*/ + (10 /*Half-width of the indicator square*/*lander.dy/0.3 /*Velocity used for the outer ring of the motion indicator (pixels per frame)*/)))
    );


}
# 1 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino"


# 4 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino" 2
# 5 "c:\\Users\\Alex_Manning\\Documents\\Apollo\\apollo.ino" 2

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

    arduboy.clear(); //Clear the Screen
    arduboy.pollButtons(); //Update the Buttons

    if(gamemap.Altitude(lander.x, lander.y) > 64 /*Pixels*/*0.75)
    {
        lander.Update(arduboy, 128*10 /*Total Map Width (Pixels)*/, 64*4 /*Total Map Height (Pixels)*/, 0, 0);
        gamemap.Draw(arduboy, 128*10 /*Total Map Width (Pixels)*/, 64*4 /*Total Map Height (Pixels)*/, 0, 0);
    }
    else
    {
        lander.Update(arduboy, 128 /*Pixels*/, 64 /*Pixels*/, lander.x-((float)128 /*Pixels*//2), (lander.y + gamemap.Altitude(lander.x, lander.y)) - (64 /*Pixels*/*0.75));
        gamemap.Draw(arduboy, 128 /*Pixels*/, 64 /*Pixels*/, lander.x-((float)128 /*Pixels*//2), (lander.y + gamemap.Altitude(lander.x, lander.y)) - (64 /*Pixels*/*0.75));
    }

    hud.Update(arduboy, lander);

    arduboy.display();
}
