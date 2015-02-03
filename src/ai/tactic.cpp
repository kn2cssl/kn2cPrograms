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
            kickSpeed = 3;//Should Changed
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

void Tactic::setPlayerToKeep(int index)
{
    this->playerToKeep = index;
}

Vector2D Tactic::findTarget()
{
    return Field::oppGoalCenter;
}
