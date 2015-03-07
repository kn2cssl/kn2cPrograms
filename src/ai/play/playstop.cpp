#include "playstop.h"

PlayStop::PlayStop(WorldModel *worldmodel, QObject *parent) :
    Play("PlayStop", worldmodel, parent)
{
    tGolie=new TacticGoalie(wm);

    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);

    tStopMid=new TacticStop(wm);
    tStopLeft=new TacticStop(wm);
    tStopRight=new TacticStop(wm);
}

int PlayStop::enterCondition()
{
    if(wm->gs == STATE_Stop)
        return 100;
    else if(wm->cmgs.canMove() && wm->cmgs.gameOn()==false && wm->cmgs.allowedNearBall()==false)
        return 10;
    else
        return 0;
    //        return 20000;
}

void PlayStop::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (activeAgents.length()) {
    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 3:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            break;
        }
        break;
    case 4:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            break;
        }
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        }
        break;
    }
}

void PlayStop::setTactics(int index)
{
    wm->ourRobot[index].Status = AgentStatus::Idle;

    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGolie;
        break;
    case AgentRole::DefenderMid:
        tactics[index] = tDefenderMid;
        break;
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        break;
    case AgentRole::AttackerMid:
        tactics[index] = tStopMid;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tStopRight;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tStopLeft;
        break;
    default:
        break;
    }
}

void PlayStop::setPositions()
{
    if(wm->kn->IsInsideGolieArea(wm->ball.pos.loc) )
    {
        tStopLeft->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalPost_L.y+200));
        tStopRight->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalPost_R.y-200));
        tStopMid->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalCenter.y));
    }
    else
    {
        Vector2D finalPos,notImportant,leftPos,rightPos;

        Circle2D robotCircle(wm->ball.pos.loc,ALLOW_NEAR_BALL_RANGE);
        Segment2D line2Goal(wm->ball.pos.loc,Field::ourGoalCenter);
        robotCircle.intersection(line2Goal,&finalPos,&notImportant);

        Circle2D secondCircle(finalPos,(2.5)*ROBOT_RADIUS);
        robotCircle.intersection(secondCircle,&leftPos,&rightPos);

        if( !wm->kn->IsInsideField(leftPos) )
        {
            leftPos = finalPos;
            finalPos = rightPos;

            Vector2D leftPos2,rightPos2;
            Circle2D secondCircle(finalPos,(2.5)*ROBOT_RADIUS);
            robotCircle.intersection(secondCircle,&leftPos2,&rightPos2);

            if( leftPos.dist(leftPos2) < leftPos.dist(rightPos2) )
                rightPos = rightPos2;
            else
                rightPos = leftPos2;

        }
        else if( !wm->kn->IsInsideField(rightPos) )
        {
            rightPos = finalPos;
            finalPos = leftPos;

            Vector2D leftPos2,rightPos2;
            Circle2D secondCircle(finalPos,(2.5)*ROBOT_RADIUS);
            robotCircle.intersection(secondCircle,&leftPos2,&rightPos2);

            if( rightPos.dist(leftPos2) < rightPos.dist(rightPos2) )
                leftPos = rightPos2;
            else
                leftPos = leftPos2;
        }

        tStopLeft->setStopPosition(leftPos);
        tStopMid->setStopPosition(finalPos);
        tStopRight->setStopPosition(rightPos);
    }
}

void PlayStop::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    for(int i=0;i<activeAgents.size();i++)
    {
        wm->ourRobot[activeAgents.at(i)].Status = AgentStatus::Idle;
    }

    initRole();
    setPositions();

    while (activeAgents.size() >0)
    {
        setTactics(activeAgents.takeFirst());
    }
}
