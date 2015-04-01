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

    rc.maxSpeed=0.75;
    rc.useNav=false;

    if( wm->cmgs.canKickBall() )
    {
        tANDp target = findTarget();
        OperatingPosition kickPoint = BallControl(target.pos, target.prob, this->id, rc.maxSpeed );
        rc.fin_pos = kickPoint.pos;
        if( kickPoint.readyToShoot )
            rc.kickspeedx = detectKickSpeed(kickType::Shoot,kickPoint.shootSensor);

        rc.useNav = kickPoint.useNav;
    }
    else
    {
        Vector2D penaltyPoint = Field::oppPenaltySpot;
        penaltyPoint.x = penaltyPoint.x -200;
        rc.fin_pos.loc = penaltyPoint;
    }

    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}
