#include "robot.h"
#define NO_CAMERA -1

Robot::Robot() :
    MobileObject()
{
}

void Robot::seenAt(vector<PositionTimeCamera> p)
{
    if(p.size() == 0){
        isValid = false;
        return;
    }
    else{
        mergePoints(p);
        if(p.size() == 0){
            isValid = false;
            return;
        }
        else if(p.size() > 1){
            qDebug() << "vision problem";
            isValid = false;
            return;
        }
    }
    isValid = true;
    qDebug() << "bande khoda" << p[0].time << p[0].pos.loc.x;
    time = p[0].time;
    pos.loc = p[0].pos.loc;
    pos.dir = p[0].pos.dir;
    vel_calc();
}
