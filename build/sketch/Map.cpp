#include "Map.h"

void Map::Set(const unsigned short *map, unsigned long map_length)
{
    this->map = map;
    this->map_length = map_length;
}

void Map::Draw(Arduboy2 arduboy, unsigned short view_width, unsigned short view_height, unsigned short view_x, unsigned short view_y)
{
    for(int i = 2; i < this->map_length; i+=2)  //For every line
    { 
        arduboy.drawLine(
            (map[i-2]-view_x)*((float)SCREEN_WIDTH/view_width), 
            (map[i-1]-view_y)*((float)SCREEN_HEIGHT/view_height), 
            (map[i]-view_x)*((float)SCREEN_WIDTH/view_width), 
            (map[i+1]-view_y)*((float)SCREEN_HEIGHT/view_height)
        );
    }
}

double Map::Altitude(double x, double y)
{
    double altitude = MAP_HEIGHT;  //Initialize to max altitude  
    for(int i = 2; i < this->map_length; i+=2)  //For every line
    { 
        if(map[i-2] < x && map[i] > x)  //If we are over/under the current segment
        {
            double ground_height = (x - map[i-2])*((double)map[i+1] - map[i-1])/((double)map[i] - map[i-2]) + map[i-1];  //Ground height at x
            if((ground_height - y) > 0 && (ground_height - y) < altitude)  //Find the lowest map point that we are actually over (avoid negative altitudes for overhangs)
            {
                altitude = ground_height - y;
            }
        }
    }

    return altitude;
}