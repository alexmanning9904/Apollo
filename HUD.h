#ifndef HUD_H
#define HUD_H

#include "Lander.h"
#include <Arduboy2.h>
#include "Parameters.h"

class HUD
{
    public:
        void Update(Arduboy2 arduboy, Lander lander);
};

#endif