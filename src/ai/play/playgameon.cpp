#include "playgameon.h"

PlayGameOn::PlayGameOn(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOn", worldmodel, parent)
{
    rolesIsInit = false;

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
    {
        if(rolesIsInit)
            rolesIsInit = conditionChanged();
        return 100;
    }
    else
        return 0;
    return 0;
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

void PlayGameOn::pressing(int ballOwner)
{
    QList<int> oppPlayers = wm->kn->findNearestOppositeTo(wm->ball.pos.loc);
    oppPlayers.removeFirst();
    oppPlayers.removeOne(wm->ref_goalie_opp);

    QList<int> ourPlayers = wm->kn->findAttackers();
    ourPlayers.removeOne(ballOwner);
    ourPlayers.removeOne(wm->ref_goalie_our);

    Marking defence;
    defence.setWorldModel(wm);
    bool isMatched;
    QList<Marking_Struct> m2m = defence.findMarking(ourPlayers,oppPlayers,isMatched);
    if( isMatched )
    {
        for(int i=0;i<m2m.size();i++)
            setPlayer2Keep(m2m.at(i).ourI,m2m.at(i).oppI);
    }

    wm->marking = m2m;
}

int PlayGameOn::findBallOwner()
{
    int ownerIndex;

    QList<int> ours = wm->kn->ActiveAgents();
    ours.removeOne(wm->ref_goalie_our);

    QList<double> distance2Prediction;

    if( wm->ball.isValid)
    {
        for(int i=0;i<ours.size();i++)
        {
            Vector2D predictedPos;
            if( (wm->ourRobot[ours.at(i)].Role == AgentRole::AttackerMid)
                    ||
                    (wm->ourRobot[ours.at(i)].Role == AgentRole::AttackerLeft)
                    ||
                    (wm->ourRobot[ours.at(i)].Role == AgentRole::AttackerRight)  )
            {
                predictedPos = wm->kn->PredictDestination(wm->ourRobot[ours.at(i)].pos.loc, wm->ball.pos.loc,2,wm->ball.vel.loc);
                double distance = (predictedPos - wm->ourRobot[ours.at(i)].pos.loc).length();
                distance2Prediction.append(distance);
            }
            else
            {
                predictedPos = wm->kn->PredictDestination(wm->ourRobot[ours.at(i)].pos.loc, wm->ball.pos.loc,1,wm->ball.vel.loc);
                double distance = (predictedPos - wm->ourRobot[ours.at(i)].pos.loc).length();
                distance2Prediction.append(distance);
            }
        }

        int min_i = -1;
        double min_d = 35000000;

        for(int i=0;i<distance2Prediction.size();i++)
        {
            if( distance2Prediction.at(i) <= min_d )
            {
                min_d = distance2Prediction.at(i);
                min_i = ours.at(i);
            }
        }

        if(min_i != -1)
        {
            wm->ourRobot[min_i].Status = AgentStatus::FollowingBall;
            ownerIndex = min_i;
            ours.removeOne(min_i);
        }
        while( !ours.isEmpty() )
            wm->ourRobot[ours.takeFirst()].Status = AgentStatus::Idle;

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
    wm->marking.clear();

    QList<int> activeAgents=wm->kn->ActiveAgents();
    numberOfPlayers = activeAgents.size();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;

    QList<AgentRole> roles;
    roles.append(AgentRole::DefenderLeft);
    roles.append(AgentRole::DefenderRight);
    roles.append(AgentRole::AttackerLeft);
    roles.append(AgentRole::AttackerRight);
    roles.append(AgentRole::AttackerMid);

    for(int i=0;i<activeAgents.size();i++)
    {
        if( roleIsValid(wm->ourRobot[activeAgents.at(i)].Role) )
        {
            roles.removeOne(wm->ourRobot[activeAgents.at(i)].Role);
            activeAgents.removeAt(i);
        }
    }

    for(int i=0;i<activeAgents.size();i++)
    {
        wm->ourRobot[activeAgents.at(i)].Role = roles.takeFirst();
    }

    rolesIsInit = true;
}

void PlayGameOn::coach()
{
    QString game_status = wm->kn->gameStatus();
    int ballOwner = findBallOwner();

    Position goaliePos,leftDefPos,rightDefPos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);
    tGolie->setIdlePosition(goaliePos);

    if( game_status == "Defending" )
    {
        pressing(ballOwner);
    }
    else if( game_status == "Attacking" )
    {
        Positioning pos_calc;
        pos_calc.setWorldModel(wm);

        bool isMatched;

        QList<int> ourAttackers = wm->kn->findAttackers();
        ourAttackers.removeOne(ballOwner);
        QList<Positioning_Struct> positions = pos_calc.find_positions(ourAttackers,isMatched);

        for(int i=0;i<positions.size();i++)
        {
            setGameOnPos(positions.at(i).ourI,positions.at(i).loc);
        }
    }
    else
    {
        //findBallOwner();
    }
}

void PlayGameOn::setGameOnPos(int ourR, Vector2D loc)
{
    switch (wm->ourRobot[ourR].Role)
    {
    case AgentRole::AttackerMid:
        tAttackerMid->setGameOnPositions(loc);
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setGameOnPositions(loc);
        break;
    case AgentRole::AttackerLeft:
        tAttackerLeft->setGameOnPositions(loc);
        break;
    default:
        break;
    }
}

bool PlayGameOn::roleIsValid(AgentRole role)
{
    if( role == AgentRole::NoRole)
        return false;

    return true;
}

void PlayGameOn::execute()
{
    QList<int> activeAgents = wm->kn->ActiveAgents();

    if( !rolesIsInit )
        initRole();

    coach();

    while( activeAgents.size() > 0 )
    {
        setTactics(activeAgents.takeFirst());
    }
}
