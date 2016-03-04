#include "mobileobject.h"
#include "constants.h"
MobileObject::MobileObject() :
    QObject(0)
{
    time = 0;
    camera = 0;
    isValid = false;
    connect(&timer_seen, SIGNAL(timeout()), this, SLOT(timer_seen_timeout()));
    connect(&timer_vel, SIGNAL(timeout()), this, SLOT(timer_vel_timeout()));
    timer_seen_interval = 100;
    timer_vel_interval = 40;
    for(int i=0; i<LAST_COUNT; i++)
        last_postc[i].time = -1;
}
void MobileObject::timer_seen_timeout()
{
    if(isValid==true)
    {
        isValid = false;
        vel.loc = {0, 0};
        vel.dir = 0;
    }
}
void MobileObject::timer_vel_timeout()
{
    //    if(!isValid)
    //    {
    //        vel.loc = {0, 0};
    //        vel.dir = 0;
    //        return;
    //    }
    //    PositionTimeCamera last = vel_postc;
    //    vel.loc = vel.loc + (((pos.loc - last.pos.loc) / (time - last.time)) - vel.loc);// filter!!!!
    //    vel.dir = (pos.dir - last.pos.dir) / (time - last.time);
    //    vel_postc.pos = pos;
    //    vel_postc.time = time;
}


void MobileObject::appendPostc(PositionTimeCamera &postc)
{
    for(int i = LAST_COUNT-1; i>0; i--)
        last_postc[i] = last_postc[i-1];
    last_postc[0] = postc;
}


void MobileObject::vel_calc()
{
    PositionTimeCamera last = vel_postc;

    vel.loc = vel.loc + (((pos.loc - last.pos.loc) / (time - last.time)) - vel.loc)*1;
    float dir_dif = pos.dir - last.pos.dir ;
    if(fabs(dir_dif) > M_PI) dir_dif = dir_dif - dir_dif/fabs(dir_dif)*M_PI*2;
    vel.dir = (dir_dif) / (time - last.time ) *1000 ;

    pos_predicted.loc = pos.loc + vel.loc * (time - last.time);
    pos_predicted.dir = pos.dir + vel.dir * (time - last.time);


    vel_postc.pos = pos;
    vel_postc.time = time;
}
