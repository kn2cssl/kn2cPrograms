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

    vel.loc = vel.loc + (((pos.loc - last.pos.loc) / (time)) - vel.loc)*1;
    float dir_dif = pos.dir - last.pos.dir ;
    if(fabs(dir_dif) > M_PI) dir_dif = dir_dif - dir_dif/fabs(dir_dif)*M_PI*2;
    vel.dir = (dir_dif) / (time) *1000 ;

    pos_predicted.loc = pos.loc + vel.loc * (time);
    pos_predicted.dir = pos.dir + vel.dir * (time);


    vel_postc.pos = pos;
    vel_postc.time = time;
}

void MobileObject::mergePoints(std::vector<PositionTimeCamera>& points){
    for(int i = 0 ; i < points.size() ; i++){
        if(points[i].confidence < MIN_CONFIDENCE){
            qDebug() << "fuuuuuuck" << points[i].confidence;
            points.erase(points.begin() + i);
        }
    }
    //wiegted mean
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            if(points[i].pos.loc.dist(points[j].pos.loc) <= MERGE_DISTANCE){
                points[i].pos.loc.x = ((points[i].pos.loc.x * points[i].confidence) + (points[j].pos.loc.x * points[j].confidence))
                        /(points[i].confidence + points[j].confidence);
                points[i].pos.loc.y = ((points[i].pos.loc.y * points[i].confidence) + (points[j].pos.loc.y * points[j].confidence))
                        /(points[i].confidence + points[j].confidence);
                points[i].confidence = std::max(points[i].confidence,points[j].confidence);
                points.erase(points.begin() + j);
            }
        }
    }
    for(int i = 0 ; i < points.size() ; i++){
        if(points[i].confidence < MIN_CONFIDENCE)
            points.erase(points.begin() + i);
    }
}
