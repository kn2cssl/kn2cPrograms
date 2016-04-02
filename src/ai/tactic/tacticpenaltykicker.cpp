#include "tacticpenaltykicker.h"

TacticPenaltyKicker::TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent) :
    TacticAttacker(worldmodel,parent)
{
    this->setObjectName("TacticPenaltyKicker");
    targetSelected = false;

    sKick = new SkillKick(wm);
}

RobotCommand TacticPenaltyKicker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed=0.75;
    rc.useNav=false;

    if( wm->cmgs.canKickBall() )
    {
        if( !targetSelected)
        {
            double distance2Left = (Field::oppGoalPost_L - wm->oppRobot[wm->ref_goalie_opp].pos.loc).length();
            double distance2Right = (Field::oppGoalPost_R - wm->oppRobot[wm->ref_goalie_opp].pos.loc).length();

            if( distance2Left < distance2Right )
                target = Vector2D(Field::oppGoalPost_R.x, Field::oppGoalPost_R.y+100);
            else
                target = Vector2D(Field::oppGoalPost_L.x, Field::oppGoalPost_L.y-100);

            targetSelected = true;
        }

        //OperatingPosition kickPoint = BallControl(target, 100, this->id, rc.maxSpeed );
        //rc.fin_pos = kickPoint.pos;
//        if( kickPoint.readyToShoot )
//            rc.kickspeedx = detectKickSpeed(kickType::Shoot,kickPoint.shootSensor);

//        rc.useNav = kickPoint.useNav;
        sKick->setIndex(this->id);
        sKick->setTarget(target);
        sKick->setKickType(true);
        sKick->execute(rc);
    }
    else
    {
        Vector2D penaltyPoint = Field::oppPenaltySpot;
        penaltyPoint.x = penaltyPoint.x -120;
        rc.fin_pos.loc = penaltyPoint;
    }

    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}

void TacticPenaltyKicker::resetEverything()
{
    this->targetSelected = false;
}
