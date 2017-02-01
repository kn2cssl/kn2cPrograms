#include "tactic.h"
#define CHIP 3

Tactic::Tactic(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name)
{
    wm = worldmodel;
    id = -1;
    kickPermission=false;
}

QString Tactic::getName()
{
    if(param.size() > 0)
        return name + " => " + param;
    else
        return name;
}

float Tactic::detectChipSpeed(bool shoot_sensor)
{
//    if( shoot_sensor )
//    {
//        if( wm->isSim )
//            return 3;
//        else
//            return 254;
//    }

    return 255;
}

void Tactic::setID(int id)
{
    this->id = id;
}

int Tactic::getID()
{
    return this->id;
}

tANDp Tactic::findTarget()
{
    tANDp out;
    out.prob = 0;
    if (!wm->ball.isValid) return out;
    wm->TANDPis.clear();


    int dist_Clearance = 00 ; // 3 cm for opp Robot Reaction displacement
    for(int jj=-10;jj<11;jj++)
    {
        int prob=100;
        Vector2D Point;
        Point.x = Field::oppGoalCenter.x;
        Point.y = Field::oppGoalCenter.y + jj*(Field::oppGoalPost_L.y/10);
        tANDp tp;
        tp.pos=Point;
        int min_prob = 100;
        for(int ii=0;ii<12;ii++)
        {
            if(wm->oppRobot[ii].isValid)
            {
                if(wm->oppRobot[ii].pos.loc.x > wm->ball.pos.loc.x-500)
                {
                    Segment2D ball2Point(wm->ball.pos.loc,Point);
                    double dist2R = ball2Point.dist(wm->oppRobot[ii].pos.loc);
                    if (dist2R < (ROBOT_RADIUS + BALL_RADIUS + dist_Clearance) ) prob=0;
                    else if (dist2R < 500 )
                    {


                        prob = dist2R/5.0;
//                        qDebug() << " prob : " << prob ;
                    }
                    else prob = 100;
                    if(prob < min_prob) min_prob = prob;
                }
            }
            min_prob=min_prob-fabs(jj/3.0);
            if(fabs(jj)>7) min_prob = min_prob*0.9;
            if(min_prob < 0) min_prob=0;
            if(min_prob == 0) break;
        }
       // qDebug() << " Min : " << min_prob;
        tp.prob=min_prob;
       // qDebug() << "tp.prob : " << tp.prob;
        wm->TANDPis.push_back(tp);
    }

    out = wm->TANDPis.at(0);
    for(int i=1;i<wm->TANDPis.size();i++)
    {
        if( out.prob < wm->TANDPis.at(i).prob)
            out = wm->TANDPis.at(i);
    }
    wm->max_TANDPis = out;
    return out;
}

void Tactic::setPlayerToKeep(int index)
{
    this->playerToKeep = index;
}
