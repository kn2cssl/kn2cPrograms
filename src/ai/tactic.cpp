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

float Tactic::detectKickSpeed(Vector2D dest )
{
    float kickSpeed;

    if(wm->isSim)
    {
        if( wm->cmgs.ourDirectKick())
            kickSpeed = 5; //Should Changed
        else if( wm->cmgs.ourIndirectKick() )
            kickSpeed = 3.5;//50; //Should Changed
        else if( wm->cmgs.gameOn() )
            kickSpeed = 5; //Should Changed
        else
            kickSpeed = 7;//Should Changed
    }
    else
    {
        if( wm->cmgs.ourDirectKick())
            kickSpeed = 200; //Should Changed
        else if( wm->cmgs.ourIndirectKick() )
            kickSpeed = 50;//50; //Should Changed
        else if( wm->cmgs.gameOn() )
            kickSpeed = 255; //Should Changed
        else
            kickSpeed = 255;//Should Changed
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

void Tactic::setPlayerToKeep(int index)
{
    this->playerToKeep = index;
}

Vector2D Tactic::findTarget()
{
    return Field::oppGoalCenter;
}
