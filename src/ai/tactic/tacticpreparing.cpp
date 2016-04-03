#include "tacticpreparing.h"


TacticPreparing::TacticPreparing(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticPreparing", worldmodel, parent)
{
    kickPermision = false;
    kickIt = false;

    sKick = new SkillKick(wm);
}

RobotCommand TacticPreparing::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 4;
    if( kickPermision )
    {
        rc.fin_pos.loc = Vector2D(0,0);
        rc.fin_pos.dir = 0;

        if(wm->ball.pos.loc.x > 0 && wm->ball.pos.loc.x < Field::MaxX/2)
        {
            tANDp target = findTarget();
//            OperatingPosition kick = BallControl(target.pos, target.prob, this->id, rc.maxSpeed);
//            rc.fin_pos = kick.pos;
//            rc.useNav = kick.useNav;

//            if( kick.readyToShoot )
//            {
//                rc.kickspeedx = detectKickSpeed(kickType::Shoot, kick.shootSensor);
//                kickIt = true;
//            }

            sKick->setIndex(this->id);
            sKick->setTarget(target.pos);
            sKick->setKickType(true);
            sKick->execute(rc);

            if( rc.kickspeedx > 0 )
               kickIt = true;
        }
    }
    else
    {
        rc.fin_pos = queuePos;
    }

    rc.isBallObs = true;
    rc.isKickObs = true;

    return rc;
}
