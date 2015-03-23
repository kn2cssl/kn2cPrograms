#include "playstop.h"

PlayStop::PlayStop(WorldModel *worldmodel, QObject *parent) :
    Play("PlayStop", worldmodel, parent)
{
    tGolie=new TacticGoalie(wm);

    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);

    tStopMid=new TacticStop(wm);
    tStopLeft=new TacticStop(wm);
    tStopRight=new TacticStop(wm);

    leftChecker = 0;
    rightChecker = 0;
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

bool PlayStop::collisionwithDefenders(Vector2D center, Vector2D left, Vector2D right)
{
    if(  ((center-wm->ourRobot[tDefenderLeft->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         ||
         ((left-wm->ourRobot[tDefenderLeft->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         ||
         ((right-wm->ourRobot[tDefenderLeft->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         ||
         ((center-wm->ourRobot[tDefenderRight->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         ||
         ((left-wm->ourRobot[tDefenderRight->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         ||
         ((right-wm->ourRobot[tDefenderRight->getID()].pos.loc).length() < 2*ROBOT_RADIUS)
         )
        return true;

    return false;
}

void PlayStop::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (activeAgents.length()) {
    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 3:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    case 5:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
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
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        tDefenderLeft->resetBooleans();
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        tDefenderRight->resetBooleans();
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
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;

    if( (wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft) /*&& (leftChecker < 100)*/ )
        leftID = tDefenderLeft->getID();

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight /*&& (rightChecker < 100)*/ )
        rightID = tDefenderRight->getID();

    if( leftChecker > 100 )
        midID = rightID;

    if( rightChecker > 100 )
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);

    if( leftID != -1)
    {
        if( /*(wm->ourRobot[leftID].Status != AgentStatus::FollowingBall ) &&*/ (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 150 )
            leftChecker++;
        else
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( /*(wm->ourRobot[rightID].Status != AgentStatus::FollowingBall ) &&*/ (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 150 )
            rightChecker++;
        else
            rightChecker = 0;
    }


    tGolie->setIdlePosition(goaliePos);

    if(wm->kn->IsInsideGolieArea(wm->ball.pos.loc) )
    {
        tStopLeft->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalPost_L.y+200));
        tStopRight->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalPost_R.y-200));
        tStopMid->setStopPosition(Vector2D(Field::MinX/2,Field::ourGoalCenter.y));
    }
    else if( wm->kn->IsInsideNearArea(wm->ball.pos.loc) )
    {
        Vector2D candidate60_1, candidate60_2, candidate30_1, candidate30_2, main60, main30;
        Circle2D cir(Field::defenceLineLinear_L,Field::goalCircle_R+ROBOT_RADIUS);
        Line2D sixty(Field::defenceLineLinear_L,AngleDeg(60));
        cir.intersection(sixty,&candidate60_1,&candidate60_2);
        if( wm->kn->IsInsideField(candidate60_1) )
            main60 = candidate60_1;
        else
            main60 = candidate60_2;

        Line2D thirty(Field::defenceLineLinear_L,AngleDeg(30));
        cir.intersection(thirty,&candidate30_1,&candidate30_2);
        if( wm->kn->IsInsideField(candidate30_1) )
            main30 = candidate30_1;
        else
            main30 = candidate30_2;

        tStopLeft->setStopPosition(Vector2D(main30.x,-sign(wm->ball.pos.loc.y)*main30.y));
        tStopMid->setStopPosition(Vector2D(Field::ourPenaltySpot.x+200,Field::ourPenaltySpot.y));
        tStopRight->setStopPosition(Vector2D(main60.x,-sign(wm->ball.pos.loc.y)*main60.y));
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

        if( collisionwithDefenders(finalPos,leftPos,rightPos) )
        {
            if( wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,Field::MaxY),Vector2D(0,0.25*Field::MaxY))
                    ||
                    wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,0.25*Field::MinY),Vector2D(0,Field::MinY)) )
            {
                Vector2D candidate60_1, candidate60_2, candidate30_1, candidate30_2, main60, main30;
                Circle2D cir(Field::defenceLineLinear_L,Field::goalCircle_R+ROBOT_RADIUS);
                Line2D sixty(Field::defenceLineLinear_L,AngleDeg(60));
                cir.intersection(sixty,&candidate60_1,&candidate60_2);
                if( wm->kn->IsInsideField(candidate60_1) )
                    main60 = candidate60_1;
                else
                    main60 = candidate60_2;

                Line2D thirty(Field::defenceLineLinear_L,AngleDeg(30));
                cir.intersection(thirty,&candidate30_1,&candidate30_2);
                if( wm->kn->IsInsideField(candidate30_1) )
                    main30 = candidate30_1;
                else
                    main30 = candidate30_2;

                tStopLeft->setStopPosition(Vector2D(main30.x,-sign(wm->ball.pos.loc.y)*main30.y));
                tStopMid->setStopPosition(Vector2D(Field::ourPenaltySpot.x+200,Field::ourPenaltySpot.y));
                tStopRight->setStopPosition(Vector2D(main60.x,-sign(wm->ball.pos.loc.y)*main60.y));
            }
            else
            {
                //tStopLeft->setStopPosition(Vector2D(wm->ourRobot[tDefenderLeft->getID()].pos.loc.x
                //                         , wm->ourRobot[tDefenderLeft->getID()].pos.loc.y+5*ROBOT_RADIUS));
                finalPos = Vector2D(wm->ourRobot[tDefenderLeft->getID()].pos.loc.x,
                        0.5*(wm->ourRobot[tDefenderLeft->getID()].pos.loc.y+wm->ourRobot[tDefenderRight->getID()].pos.loc.y)
                        );
                tStopLeft->setStopPosition(Vector2D(finalPos.x,finalPos.y+4.5*ROBOT_RADIUS));
                tStopMid->setStopPosition(finalPos);
                tStopRight->setStopPosition(Vector2D(finalPos.x,finalPos.y-4.5*ROBOT_RADIUS));
            }
        }
        else
        {
            tStopLeft->setStopPosition(leftPos);
            tStopMid->setStopPosition(finalPos);
            tStopRight->setStopPosition(rightPos);
        }
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

    while (activeAgents.size() >0)
    {
        setTactics(activeAgents.takeFirst());
    }
    setPositions();
}
