#include "playstop.h"

PlayStop::PlayStop(WorldModel *worldmodel, QObject *parent) :
    Play("PlayStop", worldmodel, parent)
{
    tGoalie = new TacticGoalie(wm);
    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tStopMid = new TacticStop(wm);
    tStopLeft = new TacticStop(wm);
    tStopRight = new TacticStop(wm);
    tAttackerLeft = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);

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

void PlayStop::initRole()
{
    QList <int> actives = wm->kn->ActiveAgents();
    actives.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (actives.length()) {
    case 1:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 2:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        break;
    case 3:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    default:
        break;
    }
}

void PlayStop::setTactics(int index)
{
    wm->ourRobot[index].Status = AgentStatus::Idle;

    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGoalie;
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
    bool leftNav, rightNav;

    if( wm->ourRobot[previousLeftID].Role != AgentRole::DefenderLeft )
        previousLeftID = -1;

    if( wm->ourRobot[previousRightID].Role != AgentRole::DefenderRight )
        previousRightID = -1;

    if( (wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft) && (leftChecker < PresenceCounter) )
    {
        leftID = tDefenderLeft->getID();
        this->previousLeftID = tDefenderLeft->getID();;
    }

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight && (rightChecker < PresenceCounter) )
    {
        rightID = tDefenderRight->getID();
        this->previousRightID = tDefenderRight->getID();;
    }

    if( leftChecker > PresenceCounter || leftID == -1 )
        midID = rightID;

    if( rightChecker > PresenceCounter  || rightID == -1)
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

    if( leftID != -1)
    {
        if( (wm->ourRobot[leftID].Status != AgentStatus::FollowingBall ) && (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousLeftID) )
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->ourRobot[rightID].Status != AgentStatus::FollowingBall ) && (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousRightID) )
            rightChecker = 0;
    }

    tGoalie->setIdlePosition(goaliePos);

    if (wm->kn->IsInsideGolieArea(wm->ball.pos.loc))
    {
        tStopMid->setStopPosition({Field::ourGoalCenter.x + 2250, 0});
        tStopLeft->setStopPosition({Field::ourGoalCenter.x + 2250, 1250});
        tStopRight->setStopPosition({Field::ourGoalCenter.x + 2250, -1250});
    }
    else if (wm->ball.pos.loc.x < Field::ourGoalCenter.x + (Field::MaxX * 2) / 3)
    {
        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);

        Circle2D goalieCir (Field::ourGoalCenter, 1300);
        Line2D linetest (Field::ourGoalCenter, wm->ball.pos.loc);
        if (wm->kn->IsInsideGolieArea(fdot))
        {
            goalieCir.intersection(linetest, &fdot, &sdot);
            if (fdot.x < sdot.x)
                fdot = sdot;
        }

        tStopMid->setStopPosition(fdot);

        tactics[tStopLeft->getID()] = tAttackerLeft;
        tactics[tStopRight->getID()] = tAttackerRight;

        Marking def;
        def.setWorldModel(wm); //??
        bool isMatched;
        QList <int> opp = wm->kn->ActiveOppAgents();
        QList <int> our;
        our.append(tAttackerLeft->getID());
        our.append(tAttackerRight->getID());
        QList <Marking_Struct> m2m = def.findMarking(our , opp, isMatched);
        if (isMatched)
        {
            for (int i = 0; i < m2m.size(); i++)
            {
                wm->ourRobot[m2m.at(i).ourI].Status = AgentStatus::BlockingRobot;

                switch (wm->ourRobot[m2m.at(i).ourI].Role) {
                case AgentRole::DefenderLeft:
                    tDefenderLeft->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::DefenderRight:
                    tDefenderRight->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::AttackerLeft:
                    tAttackerLeft->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::AttackerRight:
                    tAttackerRight->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                default:
                    break;
                }
            }
        }
    }
    else if (wm->ball.pos.loc.x < Field::ourGoalCenter.x + (Field::MaxX * 2)* 2 / 3)
    {
        Vector2D fPosAttMid, fPosAttLeft, fPosAttRight, sec;
        double slope, degree, deltaa;
        slope = (wm->ball.pos.loc.y - Field::ourGoalCenter.y) / (wm->ball.pos.loc.x - Field::ourGoalCenter.x);
        degree = atan(slope);
        deltaa = 2 * asin( ROBOT_RADIUS / ALLOW_NEAR_BALL_RANGE );
        AngleDeg deg(degree * 57.32), delta(deltaa * 57.32);
        AngleDeg leftAttDeg, rightAttDeg;
        leftAttDeg = operator -(deg, delta);
        rightAttDeg = operator +(deg, delta);
        Line2D leftAttLine(wm->ball.pos.loc, leftAttDeg.degree() - 1.5);
        Line2D rightAttLine(wm->ball.pos.loc, rightAttDeg.degree() + 1.5);
        Circle2D cir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        cir.intersection(leftAttLine, &fPosAttLeft, &sec);
        if (sec.x < fPosAttLeft.x)
            fPosAttLeft = sec;
        cir.intersection(rightAttLine, &fPosAttRight, &sec);
        if (sec.x < fPosAttRight.x)
            fPosAttRight = sec;

        tStopLeft->setStopPosition(fPosAttLeft);
        tStopRight->setStopPosition(fPosAttRight);

        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);
        tStopMid->setStopPosition(fdot);
    }
    else if (Field::ourGoalCenter.x + (Field::MaxX * 2)* 2 / 3 < wm->ball.pos.loc.x)
    {
        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);
        tStopMid->setStopPosition(fdot);

        tStopLeft->setStopPosition({wm->ball.pos.loc.x - 2250, 1250});
        tStopRight->setStopPosition({wm->ball.pos.loc.x - 2250, -1250});
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
