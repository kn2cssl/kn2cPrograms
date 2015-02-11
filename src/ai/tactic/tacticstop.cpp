#include "tacticstop.h"

TacticStop::TacticStop(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticStop", worldmodel, parent)
{
}

RobotCommand TacticStop::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    Vector2D finalPos,notImportant,leftPos,rightPos;

    bool correctPos = false;
    Circle2D robotCircle(wm->ball.pos.loc,ALLOW_NEAR_BALL_RANGE);
    Segment2D line2Goal(wm->ball.pos.loc,Field::ourGoalCenter);
    robotCircle.intersection(line2Goal,&finalPos,&notImportant);

    do
    {
        Circle2D secondCircle(finalPos,(2.5)*ROBOT_RADIUS);
        robotCircle.intersection(secondCircle,&leftPos,&rightPos);

        if( !wm->kn->IsInsideField(leftPos) )
        {
            finalPos = rightPos;
        }
        else if( !wm->kn->IsInsideField(rightPos) )
        {
            finalPos = leftPos;
        }
        else
            correctPos = true;
    }
    while(!correctPos);

    switch (wm->ourRobot[id].Role) {
    case AgentRole::AttackerMid:

        break;
    case AgentRole::AttackerRight:
        finalPos = rightPos;
        break;
    case AgentRole::AttackerLeft:
        finalPos = leftPos;
        break;
    default:
        break;
    }

    if(wm->kn->IsInsideGolieArea(wm->ball.pos.loc) )
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

    rc.maxSpeed=1;
    rc.useNav=true;
    rc.isBallObs=true;
    rc.isKickObs=true;

    return rc;
}

void TacticStop::setStopPosition(int pos)
{
    this->position=pos;
}
