#include "Lander.h"

void Lander::Set(float x, float y, float dx, float dy, float theta, float max_fuel)
{
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    this->theta = theta;
    this->max_fuel = max_fuel;
    this->fuel = max_fuel;
}

void Lander::Draw(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y)
{
    //Draw the lander.  This avoids the use of sprites in favor of the library shape primitives.  Reason for this is simply that they make the math easier.
    
    //Draw the circular body.  The center of this is the center of the lander, as well as the point of rotation.
    arduboy.drawCircle((this->x-view_x)*((float)SCREEN_WIDTH/view_width), (this->y-view_y)*((float)SCREEN_HEIGHT/view_height), BODY_RADIUS);

    //Draw the left leg
    arduboy.drawLine(
        (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta + LEG_ANGLE)*BODY_RADIUS,
        (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta + LEG_ANGLE)*BODY_RADIUS,
        (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta + LEG_ANGLE)*(LEG_LENGTH + BODY_RADIUS),
        (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta + LEG_ANGLE)*(LEG_LENGTH + BODY_RADIUS)
    );

    //Draw the right leg
    arduboy.drawLine(
        (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta - LEG_ANGLE)*BODY_RADIUS,
        (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta - LEG_ANGLE)*BODY_RADIUS,
        (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta - LEG_ANGLE)*(LEG_LENGTH + BODY_RADIUS),
        (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta - LEG_ANGLE)*(LEG_LENGTH + BODY_RADIUS)
    );

    //Draw the flame, if we are thrusting.  I think this may look better filled in sometime in the future, but a line drawing is easier to create, and has more of that retro atari charm
    if(arduboy.pressed(THRUST_BUTTON) && this->fuel)
    {
        //Draw the left half of the flame
        arduboy.drawLine(
            (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta + FLAME_WIDTH)*BODY_RADIUS,
            (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta + FLAME_WIDTH)*BODY_RADIUS,
            (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta)*(BODY_RADIUS+FLAME_LENGTH),
            (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta)*(BODY_RADIUS+FLAME_LENGTH)
        );

        //Draw the right half of the flame
        arduboy.drawLine(
            (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta - FLAME_WIDTH)*BODY_RADIUS,
            (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta - FLAME_WIDTH)*BODY_RADIUS,
            (this->x-view_x)*((float)SCREEN_WIDTH/view_width) - sin(this->theta)*(BODY_RADIUS+FLAME_LENGTH),
            (this->y-view_y)*((float)SCREEN_HEIGHT/view_height) + cos(this->theta)*(BODY_RADIUS+FLAME_LENGTH)
        );
    }
}

void Lander::Update(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y)
{
    //Update Position
    this->x += dx;
    this->y += dy;

    //Update Velocity
    this->dx += arduboy.pressed(THRUST_BUTTON) && this->fuel ? sin(theta) * THRUST_ACCELERATION : 0;
    this->dy += GRAVITY_ACCELERATION - (arduboy.pressed(THRUST_BUTTON) && this->fuel ? (cos(theta) * THRUST_ACCELERATION) : 0);

    //Update Rotation
    this->theta -= arduboy.pressed(LEFT_BUTTON) ? ROTATION_SPEED : 0;
    this->theta += arduboy.pressed(RIGHT_BUTTON) ? ROTATION_SPEED : 0;

    //Update Fuel
    this->fuel -= arduboy.pressed(THRUST_BUTTON) && this->fuel ? 1 : 0;

    this->Draw(arduboy, view_width, view_height, view_x, view_y);
}