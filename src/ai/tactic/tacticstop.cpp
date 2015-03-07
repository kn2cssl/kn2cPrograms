#include "tacticstop.h"

TacticStop::TacticStop(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticStop", worldmodel, parent)
{
}

RobotCommand TacticStop::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.fin_pos.loc = position;
    rc.fin_pos.dir = (wm->ball.pos.loc - position).dir().radian();

    rc.maxSpeed=1;

    rc.useNav=true;
    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}

void TacticStop::setStopPosition(Vector2D pos)
{
    this->position = pos;
}
