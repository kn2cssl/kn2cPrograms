#include "playkickoffopp.h"

PlayKickoffOpp::PlayKickoffOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOpp", worldmodel, parent)
{
    tGolie=new TacticGoalie(wm);

    tDefenderMid=new TacticDefender(wm);
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
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
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
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        }
        break;
    }
}

void PlayKickoffOpp::setTactics(int index)
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
}

void PlayKickoffOpp::setPositions(int index)
{
    QList<int> opps = wm->kn->ActiveOppAgents();
    opps.removeOne(wm->ref_goalie_opp);

    QList<int> nearest;
    int i = 0;
    Line2D toCenter(Vector2D(0,0),ALLOW_NEAR_BALL_RANGE);
    Circle2D cir;
    Vector2D first,second;
    int numberOfIntersection;

    switch(wm->ourRobot[index].Role)
    {
    case AgentRole::AttackerMid:
        toCenter.assign(wm->ball.pos.loc , Field::ourGoalCenter);
        cir.assign(wm->ball.pos.loc,ALLOW_NEAR_BALL_RANGE);
        numberOfIntersection = cir.intersection(toCenter,&first,&second);
        if( numberOfIntersection == 2)
        {
            if( wm->kn->IsInsideOurField(first))
                tAttackerMid->setIdlePosition(first);
            else
                tAttackerMid->setIdlePosition(second);
        }
        else if(numberOfIntersection == 1)
            tAttackerMid->setIdlePosition(first);
        else
            tAttackerMid->setIdlePosition(wm->ourRobot[index].pos);

        break;
    case AgentRole::AttackerRight:
        nearest = wm->kn->findNearestOppositeTo(Vector2D(0,Field::MaxY/2));

        while( i<nearest.size() )
        {
            if( wm->kn->IsInsideSecureArea(wm->oppRobot[nearest.at(i)].pos.loc,wm->ball.pos.loc)
                    /*||  (wm->oppRobot[nearest.at(i)].pos.loc -Vector2D(0,Field::MaxY/2)).length()>1000*/)
                nearest.removeAt(i);
            else
                i++;
        }
        if( !nearest.isEmpty() )
        {
            Line2D tmp(wm->oppRobot[nearest.at(0)].pos.loc,Field::ourGoalCenter);
            Line2D fixedLine(Vector2D(-2*ROBOT_RADIUS,Field::MinY), Vector2D(-2*ROBOT_RADIUS,Field::MaxY));
            Vector2D interSection = tmp.intersection(fixedLine);
            if( !wm->kn->IsInsideSecureArea(interSection,wm->ball.pos.loc) )
            {
                Position pos;
                pos.loc = interSection;
                pos.dir = (wm->oppRobot[nearest.at(0)].pos.loc-Field::ourGoalCenter).dir().degree()*AngleDeg::DEG2RAD;
                tAttackerRight->setIdlePosition(pos);
            }
            else
            {
                tAttackerRight->setIdlePosition(wm->ourRobot[index].pos);
            }
        }
        else
        {
            tAttackerRight->setIdlePosition(wm->ourRobot[index].pos);
        }
        break;
    case AgentRole::AttackerLeft:
        nearest = wm->kn->findNearestOppositeTo(Vector2D(0,Field::MinY/2));
        while( i<nearest.size() )
        {
            if( wm->kn->IsInsideSecureArea(wm->oppRobot[nearest.at(i)].pos.loc,wm->ball.pos.loc)
                    /*||  (wm->oppRobot[nearest.at(i)].pos.loc-Vector2D(0,Field::MinY/2)).length()>1000*/)
                nearest.removeAt(i);
            else
                i++;
        }
        if( !nearest.isEmpty() )
        {
            Line2D tmp(wm->oppRobot[nearest.at(0)].pos.loc,Field::ourGoalCenter);
            Line2D fixedLine(Vector2D(-2*ROBOT_RADIUS,Field::MinY), Vector2D(-2*ROBOT_RADIUS,Field::MaxY));
            Vector2D interSection = tmp.intersection(fixedLine);
            if( !wm->kn->IsInsideSecureArea(interSection,wm->ball.pos.loc) )
            {
                Position pos;
                pos.loc = interSection;
                pos.dir = (wm->oppRobot[nearest.at(0)].pos.loc-Field::ourGoalCenter).dir().degree()*AngleDeg::DEG2RAD;
                tAttackerLeft->setIdlePosition(pos);
            }
            else
            {
                tAttackerLeft->setIdlePosition(wm->ourRobot[index].pos);
            }
        }
        else
        {
            tAttackerLeft->setIdlePosition(wm->ourRobot[index].pos);
        }
        break;
    default:
        break;
    }
}

void PlayKickoffOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        setTactics(activeAgents.at(i));
        setPositions(activeAgents.at(i));
    }
}
