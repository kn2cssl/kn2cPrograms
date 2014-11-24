#include "tacticpenaltykicker.h"

TacticPenaltyKicker::TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent) :
    TacticAttacker(worldmodel)
{
    this->setObjectName("TacticPenaltyKicker");
}

RobotCommand TacticPenaltyKicker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;



    rc.maxSpeed=0.5;
    rc.useNav=true;
    rc.isBallObs=true;
    rc.isKickObs=true;

    if(wm->cmgs.canKickBall())
    {
        rc=goBehindBall();
        if(canKick)
        {
            rc.maxSpeed=0;
            rc.kickspeedx=3;
        }
    }
    else
    {
        rc.fin_pos.loc = Field::oppGoalPenaltySpot;
    }
    return rc;
}
