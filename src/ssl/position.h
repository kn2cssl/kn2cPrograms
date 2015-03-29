#ifndef POSITION_H
#define POSITION_H

#include "geom.h"

struct Position
{
    Vector2D loc;   // Location
    float dir;      // Direction
    Position()
    {
        loc=Vector2D(0,0);
        dir=0;
    }
};

struct OperatingPosition
{
    Position pos;
    bool useNav;
    bool ballIsObstacle;
    bool readyToShoot;
    float kickSpeed;
    OperatingPosition()
    {
        useNav=true;
        readyToShoot = false;
    }
};

#endif // POSITION_H
