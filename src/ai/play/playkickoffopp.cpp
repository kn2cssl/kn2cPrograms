#include "playkickoffopp.h"

PlayKickoffOpp::PlayKickoffOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOpp", worldmodel, parent)
{
    tGolie=new TacticGoalie(wm);

    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayKickoffOpp::enterCondition()
{
    if(wm->cmgs.theirKickoff())
        return 100;
    else
        return 0;
}

void PlayKickoffOpp::initRole()
{
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
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    }
}

void PlayKickoffOpp::setTactics(int index)
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

void PlayKickoffOpp::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool leftNav, rightNav;

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

    QList<int> opps = wm->kn->ActiveOppAgents();
    opps.removeOne(wm->ref_goalie_opp);
    QList<int> nearest2Ball = wm->kn->findNearestOppositeTo(wm->ball.pos.loc);
    if( nearest2Ball.size() != 0)
        opps.removeOne(nearest2Ball.at(0));

    QList<int> nearest;
    int i = 0;
    Line2D toCenter(Vector2D(0,0),ALLOW_NEAR_BALL_RANGE);
    Circle2D cir;
    Vector2D first,second,main;
    Position leftPos,rightPos;
    int numberOfIntersection;

    toCenter.assign(wm->ball.pos.loc , Field::ourGoalCenter);
    cir.assign(wm->ball.pos.loc,ALLOW_NEAR_BALL_RANGE);
    numberOfIntersection = cir.intersection(toCenter,&first,&second);
    if( numberOfIntersection == 2)
    {
        if( wm->kn->IsInsideOurField(first))
            main = first;
        else
            main = second;
    }
    else if(numberOfIntersection == 1)
        main = first;

    tAttackerMid->setIdlePosition(main);

    Circle2D secondCircle(main,(2.5)*ROBOT_RADIUS);
    cir.intersection(secondCircle,&leftPos.loc,&rightPos.loc);

    if( tAttackerLeft->getID() != -1)
    {
        nearest.clear();
        i = 0;
        nearest = wm->kn->findNearestOppositeTo(opps,Vector2D(0,Field::MinY/2));
        while( i<nearest.size() )
        {
            if( wm->kn->IsInsideSecureArea(wm->oppRobot[nearest.at(i)].pos.loc,wm->ball.pos.loc)
                    /*||  (wm->oppRobot[nearest.at(i)].pos.loc-Vector2D(0,Field::MinY/2)).length()>1000*/)
                nearest.removeAt(i);
            else
                i++;
        }
        while( !nearest.isEmpty() )
        {
            int indexOfOpp = nearest.takeFirst();
            Line2D tmp(wm->oppRobot[indexOfOpp].pos.loc,Field::ourGoalCenter);
            Line2D fixedLine(Vector2D(-2*ROBOT_RADIUS,Field::MinY), Vector2D(-2*ROBOT_RADIUS,Field::MaxY));
            Vector2D interSection = tmp.intersection(fixedLine);
            if( !wm->kn->IsInsideSecureArea(interSection,wm->ball.pos.loc) )
            {
                Position pos;
                pos.loc = interSection;
                pos.dir = (wm->oppRobot[indexOfOpp].pos.loc-Field::ourGoalCenter).dir().degree()*AngleDeg::DEG2RAD;
                if( !wm->kn->isOccupied(tAttackerLeft->getID(), pos.loc) )
                {
                    rightPos = pos;
                    opps.removeOne(indexOfOpp);
                    break;
                }
            }
        }
        tAttackerLeft->setIdlePosition(rightPos);
    }

    if( tAttackerRight->getID() != -1)
    {
        nearest.clear();
        nearest = wm->kn->findNearestOppositeTo(opps,Vector2D(0,Field::MaxY/2));
        i = 0;
        while( i<nearest.size() )
        {
            if( wm->kn->IsInsideSecureArea(wm->oppRobot[nearest.at(i)].pos.loc,wm->ball.pos.loc)
                    /*||  (wm->oppRobot[nearest.at(i)].pos.loc -Vector2D(0,Field::MaxY/2)).length()>1000*/)
                nearest.removeAt(i);
            else
                i++;
        }
        while( !nearest.isEmpty() )
        {
            int indexOfOpp = nearest.takeFirst();
            Line2D tmp(wm->oppRobot[indexOfOpp].pos.loc,Field::ourGoalCenter);
            Line2D fixedLine(Vector2D(-2*ROBOT_RADIUS,Field::MinY), Vector2D(-2*ROBOT_RADIUS,Field::MaxY));
            Vector2D interSection = tmp.intersection(fixedLine);
            if( !wm->kn->IsInsideSecureArea(interSection,wm->ball.pos.loc) )
            {
                Position pos;
                pos.loc = interSection;
                pos.dir = (wm->oppRobot[indexOfOpp].pos.loc-Field::ourGoalCenter).dir().degree()*AngleDeg::DEG2RAD;
                if( !wm->kn->isOccupied(tAttackerRight->getID(), pos.loc) )
                {
                    leftPos = pos;
                    opps.removeOne(indexOfOpp);
                    break;
                }
            }
        }
        tAttackerRight->setIdlePosition(leftPos);
    }
}

void PlayKickoffOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        setTactics(activeAgents.at(i));
    }

    setPositions();
}
