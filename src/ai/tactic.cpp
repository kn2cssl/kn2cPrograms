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
        switch (wm->gs ) {
        case STATE_Free_kick_Our:
            kickSpeed = 5; //Should Changed
            break;
        case STATE_Indirect_Free_kick_Our:
            kickSpeed = 3.5; //Should Changed
            break;
        case STATE_Start:
            kickSpeed = 5; //Should Changed
            break;
        default:
            kickSpeed = 7;
            break;
        }
    }
    else
    {
        switch (wm->gs ) {
        case STATE_Free_kick_Our:
            kickSpeed = 200; //Should Changed
            break;
        case STATE_Indirect_Free_kick_Our:
            kickSpeed = 25;//50; //Should Changed
            break;
        case STATE_Start:
            kickSpeed = 150; //Should Changed
            break;
        default:
            kickSpeed = 255;//Should Changed
            break;
        }
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
