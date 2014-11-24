#include "tacticfixedpos.h"

TacticFixedPos::TacticFixedPos(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticFixedPos", worldmodel, parent)
{
}

void TacticFixedPos::SetFixedPosition(int p)
{
    this->position = p;
}

RobotCommand TacticFixedPos::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 1;
    switch(position)
    {
    case CENTER:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , 0);
        break;
    case RIGHT:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , 1550);
        break;
    case LEFT:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , -1550);
        break;
    }

    rc.useNav = true;

    return rc;
}

