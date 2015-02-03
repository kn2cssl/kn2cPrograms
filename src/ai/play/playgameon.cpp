#include "playgameon.h"

PlayGameOn::PlayGameOn(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOn", worldmodel, parent)
{
    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tDefenderMid = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayGameOn::enterCondition()
{
    if( wm->cmgs.gameOn() )
        return 100;
    else
        return 0;
    return 0;
    //        return 20000;
}

void PlayGameOn::setTactics(int index)
{
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

    if(wm->ourRobot[index].Status == AgentStatus::RecievingPass)
    {
        wm->ourRobot[index].Status = AgentStatus::FollowingBall;
    }
    else if(wm->ourRobot[index].Status == AgentStatus::Kicking)
    {
        wm->ourRobot[index].Status = AgentStatus::Idle;
    }
    else if(wm->ourRobot[index].Status == AgentStatus::BlockingBall)
    {
        wm->ourRobot[index].Status = AgentStatus::BlockingBall;
    }
}

void PlayGameOn::pressing()
{
    QList<int> oppPlayers = wm->kn->findNearestOppositeTo(Field::ourGoalCenter);
    QList<int> oppNearestPlayerToBall = wm->kn->findNearestOppositeTo(wm->ball.pos.loc);
    oppPlayers.removeOne(oppNearestPlayerToBall.at(0));
    oppPlayers.removeOne(wm->ref_goalie_opp);

    oppPlayers.insert(0,oppNearestPlayerToBall.at(0));

//    int index = 0;
//    while( index < oppPlayers.size() )
//    {
//        if( !wm->kn->IsInsideOurField(wm->oppRobot[oppPlayers.at(index)].pos.loc) )
//            oppPlayers.removeAt(index);
//        else
//            index++;
//    }

    QList<int> ourPlayers = findAttackers();

    while( ourPlayers.size() > 0 )
    {
        int min_j;
        double min_d = 10000;
        for(int j=0;j<ourPlayers.size();j++)
        {
            double distance = (wm->oppRobot[oppPlayers.at(0)].pos.loc - wm->ourRobot[ourPlayers.at(j)].pos.loc).length();

            if( distance < min_d )
            {
                min_d = distance;
                min_j = ourPlayers.at(j);
            }
        }
        ourPlayers.removeOne(min_j);
        setPlayer2Keep(min_j,oppPlayers.at(0));
        oppPlayers.removeFirst();
    }
}

int PlayGameOn::findBallOwner()
{
    int ownerIndex;

    QList<int> nearestPlayers2Ball = wm->kn->findNearestTo(wm->ball.pos.loc);
    QList<int> ourRobots_temp = wm->kn->ActiveAgents();

    if( (wm->ball.vel.loc).length() > 0.25)
    {
        Ray2D ballRay(wm->ball.pos.loc,wm->ball.vel.loc.dir());

        QList<int> ourRobots;

        for(int i=0;i<ourRobots_temp.size();i++)
        {
            if(ballRay.inRightDir(wm->ourRobot[ourRobots_temp.at(i)].pos.loc,90))
            {
                ourRobots.append(ourRobots_temp.at(i));
            }
            else
            {
                wm->ourRobot[ourRobots_temp.at(i)].Status = AgentStatus::Idle;
            }
        }

        int min_i = -1;
        double min_p = 5000;
        for(int i=0;i<ourRobots.size();i++)
        {
            if( ballRay.line().dist(wm->ourRobot[ourRobots.at(i)].pos.loc) < min_p)
            {
                min_i = ourRobots.at(i);
                min_p = ballRay.line().dist(wm->ourRobot[ourRobots.at(i)].pos.loc);
            }
        }

        if(min_i != -1)
        {
            wm->ourRobot[min_i].Status = AgentStatus::FollowingBall;
            ownerIndex = min_i;
            ourRobots.removeOne(min_i);
        }

        while( !ourRobots.isEmpty() )
            wm->ourRobot[ourRobots.takeFirst()].Status = AgentStatus::Idle;
    }
    else
    {
        wm->ourRobot[nearestPlayers2Ball.at(0)].Status = AgentStatus::FollowingBall;
        ownerIndex = nearestPlayers2Ball.at(0);
        ourRobots_temp.removeOne(nearestPlayers2Ball.takeFirst());
        while( !ourRobots_temp.isEmpty() )
        {
            wm->ourRobot[ourRobots_temp.takeFirst()].Status = AgentStatus::Idle;
        }
    }

    return ownerIndex;
}

void PlayGameOn::setPlayer2Keep(int ourR, int oppR)
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

QList<int> PlayGameOn::findAttackers()
{
    QList<int> output;
    QList<int> ourAgents = wm->kn->ActiveAgents();

    for(int i=0;i<ourAgents.size();i++)
    {
        switch (wm->ourRobot[ourAgents.at(i)].Role)
        {
        case AgentRole::AttackerMid:
            output.append(ourAgents.at(i));
            break;
        case AgentRole::AttackerLeft:
            output.append(ourAgents.at(i));
            break;
        case AgentRole::AttackerRight:
            output.append(ourAgents.at(i));
            break;
        default:
            break;
        }
    }
    return output;
}

QList<AgentRegion> PlayGameOn::freeRegions()
{
    QList<AgentRegion> regions;
    regions.append(AgentRegion::Center);
    regions.append(AgentRegion::Left);
    regions.append(AgentRegion::Right);

    if( !wm->kn->IsInsideOurField(wm->ball.pos.loc ) )
    {
        if( wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,Field::MaxY),Vector2D(Field::MaxX,0.334*Field::MaxY)) )
            regions.removeOne(AgentRegion::Left);
        else if( wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,0.334*Field::MaxY),Vector2D(Field::MaxX,0.334*Field::MinY)) )
            regions.removeOne(AgentRegion::Center);
        else if( wm->kn->IsInsideRect(wm->ball.pos.loc,Vector2D(Field::MinX,0.334*Field::MinY),Vector2D(Field::MaxX,Field::MinY)) )
            regions.removeOne(AgentRegion::Right);
    }

    return regions;
}

void PlayGameOn::initRole()
{
    if( wm->gs_last == STATE_Free_kick_Our || wm->gs_last == STATE_Indirect_Free_kick_Our )
    {
        //return ;
    }
    else if( wm->gs_last == STATE_Free_kick_Opp || wm->gs_last == STATE_Indirect_Free_kick_Opp )
    {
        pressing();
    }
    else if(wm->gs_last == STATE_Penalty_Opp || wm->gs_last == STATE_Penalty_Our)
    {
        QList<int> activeAgents= wm->kn->ActiveAgents();
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
    else
    {
        QString game_status = wm->kn->gameStatus();

        if( game_status == "Defending" )
        {
            pressing();
        }
        else if( game_status == "Attacking" )
        {
            int ballOwner = findBallOwner();

            if( wm->ball.isValid )
            {
                QList<int> attackers = findAttackers();

                for(int i=0;i<attackers.size();i++)
                {
                    switch (wm->ourRobot[attackers.at(i)].Role)
                    {
                    case AgentRole::AttackerMid:
                        wm->ourRobot[attackers.at(i)].Region = AgentRegion::Center;
                        break;
                    case AgentRole::AttackerLeft:
                        wm->ourRobot[attackers.at(i)].Region = AgentRegion::Left;
                        break;
                    case AgentRole::AttackerRight:
                        wm->ourRobot[attackers.at(i)].Region = AgentRegion::Right;
                        break;
                    default:
                        break;
                    }
                }

                attackers.removeOne(ballOwner);

                Segment2D toRightCorner(wm->ball.pos.loc,Vector2D(Field::MaxX,Field::MinY));
                Segment2D toLeftCorner(wm->ball.pos.loc,Vector2D(Field::MaxX,Field::MaxY));

                Vector2D centerPos , leftPos , rightPos;

                leftPos = toLeftCorner.intersection(Field::attackerLeftLine);
                if( leftPos == Vector2D::INVALIDATED )
                    leftPos = Vector2D(0,0);
                rightPos = toRightCorner.intersection(Field::attackerRightLine);
                if( rightPos == Vector2D::INVALIDATED )
                    rightPos = Vector2D(0,0);

                if( toLeftCorner.existIntersection(Field::attackerMidLine) )
                    centerPos = toLeftCorner.intersection(Field::attackerMidLine);
                else if( toRightCorner.existIntersection(Field::attackerMidLine) )
                    centerPos = toRightCorner.intersection(Field::attackerMidLine);

                if( centerPos == Vector2D::INVALIDATED)
                    centerPos = Vector2D(0,0);

                QList<AgentRegion> free_regions = freeRegions();

                int attackerIndex = 0 , regionIndex = 0;
                while( attackerIndex < attackers.size() )
                {
                    int attacker = attackers.at(attackerIndex);

                    while( regionIndex < free_regions.size() )
                    {
                        if(wm->ourRobot[attackers.at(attackerIndex)].Region == free_regions.at(regionIndex) )
                        {
                            switch (wm->ourRobot[attackers.at(attackerIndex)].Region) {
                            case AgentRegion::Center:
                                tAttackerMid->setGameOnPositions(centerPos);
                                break;
                            case AgentRegion::Left:
                                tAttackerLeft->setGameOnPositions(leftPos);
                                break;
                            case AgentRegion::Right:
                                tAttackerRight->setGameOnPositions(rightPos);
                                break;
                            default:
                                break;
                            }
                            attackers.removeAt(attackerIndex);
                            free_regions.removeAt(regionIndex);
                            break;
                        }
                        else
                        {
                            regionIndex++;
                        }
                    }
                    regionIndex = 0;
                    if( attackers.contains(attacker))
                        attackerIndex++;
                }

                while ( !attackers.isEmpty() )
                {
                    int i = attackers.takeFirst();
                    if( !free_regions.isEmpty() )
                    {
                        switch ( free_regions.takeFirst() )
                        {
                        case AgentRegion::Center:
                            setGameOnPos(i,centerPos);
                            break;
                        case AgentRegion::Left:
                            setGameOnPos(i,leftPos);
                            break;
                        case AgentRegion::Right:
                            setGameOnPos(i,rightPos);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                        setGameOnPos(i,wm->ourRobot[i].pos.loc);
                }
            }
        }
        else
        {
            findBallOwner();
        }
    }
}

void PlayGameOn::setGameOnPos(int ourR, Vector2D oppR)
{
    switch (wm->ourRobot[ourR].Role)
    {
    case AgentRole::AttackerMid:
        tAttackerMid->setGameOnPositions(oppR);
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setGameOnPositions(oppR);
        break;
    case AgentRole::AttackerLeft:
        tAttackerLeft->setGameOnPositions(oppR);
        break;
    default:
        break;
    }
}

void PlayGameOn::execute()
{
    QList<int> activeAgents = wm->kn->ActiveAgents();

    initRole();

    while( activeAgents.size() > 0 )
    {
        setTactics(activeAgents.takeFirst());
    }
}
