#include "playfreekickopp.h"

PlayFreeKickOpp::PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOpp", worldmodel, parent)
{
    numberOfPlayers = 0;

    rolesIsInit = false;
    go2ThePositions = false;

    waitTimer = new QTimer();
    connect(waitTimer,SIGNAL(timeout()),this,SLOT(waitTimer_timout()));

    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayFreeKickOpp::enterCondition()
{
    if(wm->cmgs.theirFreeKick() || wm->cmgs.theirDirectKick())
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
            go2ThePositions = false;

            waitTimer->start(250);
        }
        //        else
        //        {
        //            rolesIsInit = conditionChanged();
        //        }
        return 100;
    }
    else
    {
        return 0;
    }
    //        return 200000;
}

void PlayFreeKickOpp::waitTimer_timout()
{
    waitTimer->stop();
    go2ThePositions = true;
}

void PlayFreeKickOpp::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    numberOfPlayers = activeAgents.size();
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
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    }
    rolesIsInit = true;
}

void PlayFreeKickOpp::pressing()
{
    QList<int> oppPlayers = wm->kn->ActiveOppAgents();
    QList<int> oppInSecure;
    oppPlayers.removeOne(wm->ref_goalie_opp);

    QList<int> ourPlayers = wm->kn->findAttackers();
    int counter = 0;
    while( counter < oppPlayers.size() )
    {
        if( wm->kn->IsInsideSecureArea(wm->oppRobot[oppPlayers.at(counter)].pos.loc,wm->ball.pos.loc))
        {
                oppInSecure.append(oppPlayers.at(counter));
                oppPlayers.removeAt(counter);
        }
        else
            counter++;
    }

    counter = 0;
    while( counter < oppPlayers.size() )
    {
        if( wm->kn->IsInsideFarArea(wm->oppRobot[oppPlayers.at(counter)].pos.loc) )
            oppPlayers.removeAt(counter);
        else
            counter++;
    }

    if( oppInSecure.size() == 1 )
        oppPlayers.append(oppInSecure.first() );

    Marking defence;
    defence.setWorldModel(wm);
    bool isMatched;
    QList<Marking_Struct> m2m = defence.findMarking(ourPlayers,oppPlayers,isMatched);
    if( isMatched )
    {
        for(int i=0;i<m2m.size();i++)
        {
            setPlayer2Keep(m2m.at(i).ourI,m2m.at(i).oppI);
            ourPlayers.removeOne(m2m.at(i).ourI);
        }
    }

    while ( ourPlayers.size() > 0 )
    {
        wm->ourRobot[ourPlayers.takeFirst()].Status = AgentStatus::Idle;
    }

    wm->marking = m2m;

//    if( wm->cmgs.theirDirectKick() )
//    {
//        wm->ourRobot[tDefenderLeft->getID()].Status = AgentStatus::BlockingBall;
//        wm->ourRobot[tDefenderRight->getID()].Status = AgentStatus::BlockingBall;
//    }
}

void PlayFreeKickOpp::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGolie;
        break;
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        break;
    case AgentRole::AttackerMid:
        tactics[index] = tAttackerMid;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    default:
        break;
    }
}

void PlayFreeKickOpp::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool leftNav,rightNav;

    if( wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft )
        leftID = tDefenderLeft->getID();

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight )
        rightID = tDefenderRight->getID();

    if( leftChecker > 100 || leftID == -1 )
        midID = rightID;

    if( rightChecker > 100  || rightID == -1)
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tGolie->setIdlePosition(goaliePos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

    if( leftID != -1)
    {
        if( (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }

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

    QList<Vector2D> pointsForIdle;
    pointsForIdle.append(finalPos);
    pointsForIdle.append(rightPos);
    pointsForIdle.append(leftPos);

    if(tAttackerLeft->getID()!=-1 && wm->ourRobot[tAttackerLeft->getID()].isValid && wm->ourRobot[tAttackerLeft->getID()].Status==AgentStatus::Idle)
    {
        for(int i=0;i<pointsForIdle.size();i++)
        {
            if(!wm->kn->isOccupied(tAttackerLeft->getID(),pointsForIdle.at(i)))
            {
                tAttackerLeft->setIdlePosition(pointsForIdle.at(i));
                break;
            }
        }

    }

    if(tAttackerRight->getID()!=-1 && wm->ourRobot[tAttackerRight->getID()].isValid && wm->ourRobot[tAttackerRight->getID()].Status==AgentStatus::Idle)
    {
        for(int i=0;i<pointsForIdle.size();i++)
        {
            if(!wm->kn->isOccupied(tAttackerRight->getID(),pointsForIdle.at(i)))
            {
                tAttackerRight->setIdlePosition(pointsForIdle.at(i));
                break;
            }
        }

    }

    if(tAttackerMid->getID()!=-1 && wm->ourRobot[tAttackerMid->getID()].isValid && wm->ourRobot[tAttackerMid->getID()].Status==AgentStatus::Idle)
    {
        for(int i=0;i<pointsForIdle.size();i++)
        {
            if(!wm->kn->isOccupied(tAttackerMid->getID(),pointsForIdle.at(i)))
            {
                tAttackerMid->setIdlePosition(pointsForIdle.at(i));
                break;
            }
        }

    }
}

void PlayFreeKickOpp::setPlayer2Keep(int ourR, int oppR)
{
    wm->ourRobot[ourR].Status = AgentStatus::BlockingRobot;

    switch (wm->ourRobot[ourR].Role)
    {
    case AgentRole::AttackerMid:
        tAttackerMid->setPlayerToKeep(oppR);
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setPlayerToKeep(oppR);
        break;
    case AgentRole::AttackerLeft:
        tAttackerLeft->setPlayerToKeep(oppR);
        break;
    default:
        break;
    }
}
void PlayFreeKickOpp::execute()
{
    if(go2ThePositions)
    {
        QList<int> activeAgents=wm->kn->ActiveAgents();

//        if( !rolesIsInit )
            initRole();
//        else
            pressing();

        for(int i=0;i<activeAgents.size();i++)
            setTactics(activeAgents.at(i));

        setPositions();
    }
}
