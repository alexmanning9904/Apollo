#ifndef LANDER_H_
#define LANDER_H_
#include <Arduboy2.h>
#include "Parameters.h"

class Lander
{
    public:
        // State of the Lander.  While using floats is super memory-inefficient, I think I'm going to commit to them for the sake of making the math easier.  If I start to toe against hardware limits, I'll rethink this.
        float x;  //x position, in pixels
        float y;  //y position, in pixels
        float dx;  //x velocity, in pixels/frame
        float dy;  //y velocity, in pixels/frame
        float theta;  //Angle in radians from straight up (positive clockwise)
        unsigned short max_fuel;  //Maximum fuel.  Resettable to support different levels
        unsigned short fuel;  //Remaining Units of Fuel.  Lander is refilled whenever Set is called.

        void Set(float x, float y, float dx, float dy, float theta, float max_fuel);  //Set position of the lander, used for initial positioning
        void Update(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y);  //Update the lander's state and draw it

    private:
        void Draw(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y);  //Draw the lander
};

#endif