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

    QList<int> nearestPlayers2Ball = wm->kn->findNearestTo(wm->ball.pos.loc);
    QList<int> ourRobots_temp = wm->kn->ActiveAgents();

    if( (wm->ball.vel.loc).length() > 0.5 )
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
    switch (activeAgents.length()) {
    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
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
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        }
        break;
    }
    rolesIsInit = true;
}

void PlayGameOn::coach()
{
    QString game_status = wm->kn->gameStatus();
    int ballOwner = findBallOwner();

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
