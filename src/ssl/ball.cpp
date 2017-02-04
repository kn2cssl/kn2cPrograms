#include "ball.h"
#define NO_CAMERA -1

Ball::Ball() :
    MobileObject()
{
}

void Ball::seenAt(vector<PositionTimeCamera> p)
{

    if(p.size() == 0){
        hiddenTime += time;
        if(hiddenTime > 500){
            isValid = false;            
            return;
        }
        else{
            pos.loc.x = pos.loc.x + time*vel.loc.x;
            pos.loc.y = pos.loc.y + time*vel.loc.y;
            debugs->append(pos.loc);
            vel_calc();
            return;
        }
    }
    else{
        mergePoints(p);
        if(p.size() == 0){
            hiddenTime += time;
            return;
        }
        else if(p.size() > 1){
            qDebug() << "vision problem";
            isValid = false;
            return;
        }
    }
    isValid = true;
    time = p[0].time;
    pos.loc = p[0].pos.loc;
//    debugs->append(pos.loc);
    vel_calc();
}
