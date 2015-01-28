#include "tacticfixedpos.h"

TacticFixedPos::TacticFixedPos(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticFixedPos", worldmodel, parent)
{
}

RobotCommand TacticFixedPos::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 1;
    switch(wm->ourRobot[this->id].Role)
    {
    case AgentRole::AttackerMid:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , 0);
        break;
    case AgentRole::AttackerRight:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , 1550);
        break;
    case AgentRole::AttackerLeft:
        rc.fin_pos.loc = Vector2D(wm->ball.pos.loc.x - 500 , -1550);
        break;
    default:
        break;
    }

    rc.useNav = true;

    return rc;
}

