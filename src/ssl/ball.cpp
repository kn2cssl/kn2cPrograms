#include "ball.h"
#define NO_CAMERA -1

Ball::Ball() :
    MobileObject()
{
}

void Ball::seenAt(vector<PositionTimeCamera> p)
{

    if(p.size()<1) return;
 //    isValid = true;
     timer_seen.start(timer_seen_interval); //restart

     PositionTimeCamera ans;
     ans.time = p[0].time;
     ans.camera = p[0].camera;

     Vector2D buff;
     int min_i = 0;
     buff = p[min_i].pos.loc - pos_predicted.loc ;
     double min_d = buff.length();
     for(size_t i=0; i < p.size(); i++)
     {
         buff = p[i].pos.loc - pos_predicted.loc ;
         double d = buff.length();
         if(d < min_d)
         {
             min_d = d;
             min_i = i;
         }
     }

     ans.pos.loc = p[min_i].pos.loc;
     ans.pos.dir = p[min_i].pos.dir;

     if (camera_mem == ans.camera  || camera_mem == NO_CAMERA )
     {
         if((pos.loc - ans.pos.loc).length() < 540 || camera_mem == NO_CAMERA)
         {
             camera = ans.camera;
             time = ans.time;
             pos = ans.pos;
             vel_calc();
             isValid = true ;
             camera_mem = camera ;
             camera_timeout = 0;
         }
         else
         {
             camera_timeout++;
             if(camera_timeout >8) camera_mem = NO_CAMERA;
         }
     }
     else
     {
         camera_timeout++;
         if(camera_timeout >8) camera_mem = NO_CAMERA;
     }
}
