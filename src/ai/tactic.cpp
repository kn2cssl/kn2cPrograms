#include "tactic.h"

Tactic::Tactic(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name)
{
    wm = worldmodel;
    id = -1;
}

QString Tactic::getName()
{
    if(param.size() > 0)
        return name + " => " + param;
    else
        return name;
}

float Tactic::detectKickSpeed( Vector2D dest )
{
    float kickSpeed;

    Segment2D goalLine(Field::oppGoalPost_L,Field::oppGoalPost_R);

    if(wm->isSim)
    {
        if( goalLine.contains(dest) )
            kickSpeed = 8; //Should Changed
        else
            kickSpeed = 4;//Should Changed
    }
    else
    {
        if( goalLine.contains(dest) )
            kickSpeed = 255; //Should Changed
        else
            kickSpeed = 100;//Should Changed
    }

    return kickSpeed;
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

    int prob=100;
    int dist_Clearance = 30 ; // 3 cm for opp Robot Reaction displacement
    for(int jj=-10;jj<11;jj++)
    {
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
                if(wm->oppRobot[ii].pos.loc.x > wm->ball.pos.loc.x)
                {
                    Segment2D ball2Point(wm->ball.pos.loc,Point);
                    double dist2R = ball2Point.dist(wm->oppRobot[ii].pos.loc);
                    if (dist2R < (ROBOT_RADIUS + BALL_RADIUS + dist_Clearance) ) prob=0;
                    else if (dist2R < 400 ) prob = dist2R/4;
                    else prob = 100;
                    if(prob < min_prob) min_prob = prob;
                }
            }
            if(abs(jj) > 7) prob = prob*((17-abs(jj))/10);
            if(min_prob == 0) break;
        }
        tp.prob=min_prob;
        wm->TANDPis.push_back(tp);
    }

    out = wm->TANDPis.at(0);
    for(int i=1;i<wm->TANDPis.size();i++)
    {
        if( out.prob < wm->TANDPis.at(i).prob)
            out = wm->TANDPis.at(i);
    }
    return out;
}

void Tactic::setPlayerToKeep(int index)
{
    this->playerToKeep = index;
}
