#ifndef PARAMETERS_H
#define PARAMETERS_H

//Control Definitions
#define THRUST_BUTTON A_BUTTON

//Lander Body Definitions
#define BODY_RADIUS 3  //Radius of the circle that comprises the lander body (pixels)
#define LEG_LENGTH 4  //Length of the legs that stick out of the lander body (pixels)
#define LEG_ANGLE 0.5  //Angle that each leg sticks out, as referenced from straight down (radians)
#define FLAME_LENGTH 6  //Length of flame from lander body to tip (pixels)
#define FLAME_WIDTH 0.3  //Half-width of lander flame in radians on the body arc

//Lander Environment Definitions
#define ROTATION_SPEED 0.08  //Rotation of lander in radians per frame
#define GRAVITY_ACCELERATION 0.0005  //Acceleration of gravity in pixels per squared frame.  What a unit
#define THRUST_ACCELERATION 3*GRAVITY_ACCELERATION //Acceleration from thrust in pixels per squared frame.

//HUD Definitions
#define FUEL_WIDTH 2 //Width of the fuel bar (pixels)
#define FUEL_X 127 //X-location of the fuel bar (pixels).  No Y-location, since it takes the whole screen

//Indicator Definitions
#define INDICATOR_WIDTH 10 //Half-width of the indicator square
#define INDICATOR_MAX 0.3 //Velocity used for the outer ring of the motion indicator (pixels per frame)
#define INDICATOR_X 100 //X-location of the center of the indicator
#define INDICATOR_Y 20 //Y-Location of the center of the indicator

//Map Definitions
#define MAP_WIDTH 128*10  //Total Map Width (Pixels)
#define MAP_HEIGHT 64*4  //Total Map Height (Pixels)

//Camera Definitions Definitions
#define SCREEN_WIDTH 128  //Pixels
#define SCREEN_HEIGHT 64  //Pixels

#endif