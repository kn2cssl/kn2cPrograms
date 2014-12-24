#include "tacticstop.h"

TacticStop::TacticStop(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticStop", worldmodel, parent)
{
}

RobotCommand TacticStop::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    Vector2D finalPos,leftPos,rightPos;
    double m;
    double alfa;
    m=-(Field::ourGoalCenter.y-wm->ball.pos.loc.y)/(Field::ourGoalCenter.x-wm->ball.pos.loc.x);
    alfa=atan(m);

    if(alfa>75.0*3.14/180)
    {
        alfa=120.0*3.14/180;
    }

    if(alfa<-75.0*3.14/180)
    {
        alfa=-120.0*3.14/180;
    }

    switch (wm->ourRobot[id].Role) {
    case AgentRole::AttackerMid:

        break;
    case AgentRole::AttackerRight:
        alfa-=DIFF;
        break;
    case AgentRole::AttackerLeft:
        alfa+=DIFF;
        break;
    }
    finalPos.x=wm->ball.pos.loc.x-ALLOW_NEAR_BALL_RANGE*cos(alfa);
    finalPos.y=wm->ball.pos.loc.y+ALLOW_NEAR_BALL_RANGE*sin(alfa);

    if(wm->kn->IsInsideGolieArea(finalPos) )
    {
        if(wm->ourRobot[id].Role == AgentRole::AttackerLeft)
        {
            rc.fin_pos.loc = Vector2D(Field::MinX/2,Field::ourGoalPost_L.y+200);
        }
        else if(wm->ourRobot[id].Role == AgentRole::AttackerRight)
        {
            rc.fin_pos.loc = Vector2D(Field::MinX/2,Field::ourGoalPost_R.y-200);
        }
        else if(wm->ourRobot[id].Role == AgentRole::AttackerMid)
        {
            rc.fin_pos.loc = Vector2D(Field::MinX/2,Field::ourGoalCenter.y);
        }
    }
    else
        rc.fin_pos.loc=finalPos;

    rc.maxSpeed=0.75;

    rc.useNav=true;
    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}

void TacticStop::setStopPosition(int pos)
{
    this->position=pos;
}
