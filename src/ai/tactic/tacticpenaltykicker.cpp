#include "tacticpenaltykicker.h"

TacticPenaltyKicker::TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent) :
    TacticAttacker(worldmodel,parent)
{
    this->setObjectName("TacticPenaltyKicker");
}

RobotCommand TacticPenaltyKicker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    if(wm->cmgs.canKickBall())
    {
        Position kickPoint = wm->kn->AdjustKickPoint(wm->ball.pos.loc,Field::oppGoalCenter);
        rc.fin_pos = kickPoint;
        if(wm->kn->CanKick(wm->ourRobot[this->id].pos,wm->ball.pos.loc))
        {
            rc.kickspeedx = detectKickSpeed(Field::oppGoalCenter);
        }
    }
    else
    {
        Vector2D penaltyPoint = Field::oppGoalPenaltySpot;
        penaltyPoint.x = penaltyPoint.x -200;
        rc.fin_pos.loc = penaltyPoint;
    }
    rc.maxSpeed=0.75;
    rc.useNav=false;
    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}
