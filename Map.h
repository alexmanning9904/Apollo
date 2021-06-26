#ifndef MAP_H
#define MAP_H

#include <Arduboy2.h>
#include "Parameters.h"

class Map
{

    public:
        void Set(const unsigned short *map, unsigned long map_length);
        void Draw(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y);
        bool Collides(double x, double y);
        bool Collides(double x, double y, double radius);
        double Altitude(double x, double y);

    private:
        const unsigned short *map;
        unsigned long map_length;

};

#endif